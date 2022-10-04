using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    interface IList<T>
    {
        void AddFirst(T item);
        void AddLast(T item);
        void AddBefore(T newItem, T item);
        void AddAfter(T newItem, T item);
    }
}
