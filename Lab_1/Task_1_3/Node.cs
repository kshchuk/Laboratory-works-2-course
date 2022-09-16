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
        internal MyLinkedList<T> list;
        internal Node<T> next;
        internal Node<T> prev;
        internal T item;

        public Node(T value)
        {
            this.item = value;
        }
        internal Node(MyLinkedList<T> list, T value)
        {
            this.list = list;
            this.item = value;
        }

        public MyLinkedList<T> List => list;
        public Node<T> Next => next == null || next == list.head ? null : next;
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
