using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


namespace list_2
{
    /// <summary>
    /// The character's level of involvement in the book
    /// </summary>
    public enum InvolvementLevel
    {
        Main,
        Secondary,
        Episodic
    }

    public class Character
    {
        List<string> Nicknames { get; set; }
        /// <summary>
        /// The character's role and book in which it exists
        /// </summary>
        public Tuple<Book, InvolvementLevel> UsedInBook { get; set; }
    }
}
