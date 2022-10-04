namespace list_2
{
    public class Book
    {
        public string Title { get; set; }
        public List<string> Authors { get; set; }
        public DateTime ReleaseDate { get; set; }
        public int PagesNumber { get; set; }
        public string BriefSummary { get; set; }
    }
}