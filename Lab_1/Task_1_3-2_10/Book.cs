using System.Collections;

namespace list_2
{
    public class Book : IComparable<Book>
    {
        public string Title { get; init; }
        public List<string> Authors { get; init; }
        public DateTime ReleaseDate { get; init; }
        public int PagesNumber { get; init; }
        public string BriefSummary { get; set; }

        Book(string title, List<string> authors, DateTime releaseDate, int pagesNumber, string briefSummary)
        {
            Title = title;
            Authors = authors;
            ReleaseDate = releaseDate;
            PagesNumber = pagesNumber;
            BriefSummary = briefSummary;
        }

        public int CompareTo(Book? other)
        {
            return this.ReleaseDate.CompareTo(other.ReleaseDate);
        }

        public override string ToString()
        {
            return "Title: " + Title + "\n" +
                "Authors: " + String.Join(", ", Authors.ToArray()) + '\n' +
                "Release date: " + ReleaseDate.ToString() + "\n" +
                "Pages number: " + PagesNumber + "\n" +
                "Brief summary:\n" + BriefSummary + '\n';
        }

        public static Book GetBook()
        {
            Console.WriteLine("Enter book data:");
            string title;
            {
                Console.WriteLine("Type title: ");
                title = Console.ReadLine();
            }

            List<string> authors;
            {
                authors = new List<string>();
                Console.WriteLine("Type autors count: ");
                int cout = Convert.ToInt32(Console.ReadLine());
                Console.WriteLine("Type names of the authors (one per line):");
                for (int i = 0; i < cout; i++)
                {
                    authors.Add(Console.ReadLine());
                }
            }

            DateTime releaseDate;
            {
                Console.WriteLine("Type release date (mm/dd/yyyy hh:mm:ss [AM/PM]");
                releaseDate = Convert.ToDateTime(Console.ReadLine());
            }

            int pagesNumber;
            {
                Console.WriteLine("Type pages number: ");
                pagesNumber = Convert.ToInt32(Console.ReadLine());
            }

            string briefSummary;
            {
                Console.WriteLine("Enter brief summary: ");
                briefSummary = Console.ReadLine();
            }

            return new Book(title, authors, releaseDate, pagesNumber, briefSummary);
        }
    }
}