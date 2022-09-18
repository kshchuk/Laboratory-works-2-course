using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    /// <summary>
    /// Base for all lists
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public abstract class MyList<T>
    {
        protected MyNode<T> head;
        public abstract void AddFirst(T item);
        public abstract void AddLast(T item);
        public abstract void AddBefore(T newItem, T item);
        public abstract void AddAfter(T newItem, T item);
    }
}
