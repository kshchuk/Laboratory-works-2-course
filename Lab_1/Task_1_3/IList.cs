using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    interface IList<T>
    {
        void AddFirst(T item);
        void AddLast(T item);
        void AddBefore(T newItem, T item);
        void AddAfter(T newItem, T item);
    }
}
