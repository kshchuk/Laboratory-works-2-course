using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    /// <summary>
    /// Node for double linked lists
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class DNode<T> : INode<T>
    {
        private DNode<T> next;
        private DNode<T> prev;
        private T value;

        public DNode(T value)
        {
            this.value = value;
            next = null;
            prev = null;
        }

        public DNode<T> Next
        {
            get { return next; }
            set { next = value; }
        }
        public DNode<T> Prev
        {
            get { return prev; }
            set { prev = value; }
        }
        public T Value
        {
            get { return value; }
            set { this.value = value; }
        }

        public void Invalidate()
        {
            next = null;
            prev = null;
        }
    }
}
