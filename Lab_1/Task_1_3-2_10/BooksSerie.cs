using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_2
{
    public class BooksSerie
    {
        public List<Book> Serie { get; private set; }
        public void AddToSerie(Book book)
        {
            Serie.Add(book);
            Serie.Sort();
        }
    }
}
