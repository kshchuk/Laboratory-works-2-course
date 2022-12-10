#pragma once

#include <vector>
#include <string>
#include <stdlib.h>
#include <zstd.h>  

#include "common.h"


class ArchiverLogic
{
typedef struct {
    void* fBuffer;
    void* cBuffer;
    size_t fBufferSize;
    size_t cBufferSize;
    ZSTD_CCtx* cctx;
} resources;

public:
    void set_files(std::vector<std::string> files);
    void set_destination(std::string dest);

    void ZSTDCompress();
    void ZSTDDecompress();

private:
    std::vector<std::string> files;
    std::string dest;
    resources res;

    void CreateResources();
    void FreeResources();
};

