#include "ArchiverLogic.h"

#include <stdexcept>


void ArchiverLogic::set_files(std::vector<std::string> files)
{
	this->files = files;
}

void ArchiverLogic::set_destination(std::string dest)
{
    this->dest = dest;
}

void ArchiverLogic::ZSTDCompress()
{
    CreateResources();

    if (!files.empty()) {

        for (auto file : files) {
            size_t fSize = arh::loadFile_orDie(file.c_str(), res.fBuffer, res.fBufferSize);

            size_t const cSize = ZSTD_compressCCtx(res.cctx, res.cBuffer, res.cBufferSize, res.fBuffer, fSize, 1);
            CHECK_ZSTD(cSize);

            std::string fil; 
            for (auto biter = file.rbegin(); biter != file.rend() && *biter != '/' && *biter != '\\'; biter++) fil += *biter;
            std::reverse(fil.begin(), fil.end());

            arh::saveFile_orDie(((!dest.empty() ? dest + '/' + fil : file) + ".zst").c_str(), res.cBuffer, cSize);
        }
    }

    FreeResources();
}

void ArchiverLogic::ZSTDDecompress()
{
    for (auto ar : files) {

        size_t cSize;
        void* const cBuff = arh::mallocAndLoadFile_orDie(ar.c_str(), &cSize);
        unsigned long long const rSize = ZSTD_getFrameContentSize(cBuff, cSize);
/*        if (rSize != ZSTD_CONTENTSIZE_ERROR) throw std::runtime_error(ar + ": not compressed by zstd!");
        if (rSize != ZSTD_CONTENTSIZE_UNKNOWN) throw std::runtime_error(ar + ": not compressed by zstd!")*/;

        void* const rBuff = arh::malloc_orDie((size_t)rSize);

        size_t const dSize = ZSTD_decompress(rBuff, rSize, cBuff, cSize);
        CHECK_ZSTD(dSize);
        CHECK(dSize == rSize, "Impossible because zstd will check this condition!");

        ar.erase(ar.end() - 4, ar.end());

        std::string fil;
        for (auto biter = ar.rbegin(); biter != ar.rend() && *biter != '/' && *biter != '\\'; biter++) fil += *biter;
        std::reverse(fil.begin(), fil.end());

        arh::saveFile_orDie((!dest.empty() ? dest + fil : ar).c_str(), rBuff, rSize);

        free(rBuff);
        free(cBuff);
    }
}

void ArchiverLogic::CreateResources()
{
    size_t maxFilenameLength = 0;
    size_t maxFileSize = 0;

    int argNb;
    for (argNb = 0; argNb < files.size(); argNb++) {
        const char* const filename = files[argNb].c_str();
        size_t const filenameLength = strlen(filename);
        size_t const fileSize = arh::fsize_orDie(filename);

        if (filenameLength > maxFilenameLength) maxFilenameLength = filenameLength;
        if (fileSize > maxFileSize) maxFileSize = fileSize;
    }
        
    resources ress;
    ress.fBufferSize = maxFileSize;
    ress.cBufferSize = ZSTD_compressBound(maxFileSize);

    //*ofnBufferLen = maxFilenameLength + 5;
    //*ofn = (char*)malloc_orDie(*ofnBufferLen);
    ress.fBuffer = arh::malloc_orDie(ress.fBufferSize);
    ress.cBuffer = arh::malloc_orDie(ress.cBufferSize);
    ress.cctx = ZSTD_createCCtx();
    CHECK(ress.cctx != NULL, "ZSTD_createCCtx() failed!");
    res = ress;
}

void ArchiverLogic::FreeResources()
{
    free(res.fBuffer);
    free(res.cBuffer);
    ZSTD_freeCCtx(res.cctx);   /* never fails */
    // free(outFilename);
}
