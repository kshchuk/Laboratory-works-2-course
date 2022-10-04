using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    /// <summary>
    /// Node for Single Linked List
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public class SNode<T> : INode<T>
    {
        private SNode<T> next;
        private T value;

        public SNode(T value)
        {
            this.value = value;
            next = null;
        }
        public SNode<T> Next
        {
            get { return next; }
            set { next = value; }
        }
        public T Value
        {
            get { return value; }
            set { this.value = value; }
        }
        public void Invalidate()
        {
            next = null;
        }
    }
}
