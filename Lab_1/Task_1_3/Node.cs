using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    /// <summary>
    /// Node for Single Linked List
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public sealed class Node<T>
    {
        private Node<T> next;
        private T item;

        public Node(T value)
        {
            this.item = value;
        }

        internal Node<T> Next {
            get { return next; }
            set { next = value; }
        }
        public T Value
        {
            get { return item; }
            set { item = value; }
        }

        /// <summary>
        /// Destructor
        /// </summary>
        internal void Invalidate()
        {
            list = null;
            next = null;
            prev = null;
        }
    }
}
