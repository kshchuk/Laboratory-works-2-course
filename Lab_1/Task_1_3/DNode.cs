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
    public class DNode<T> : MyNode<T>
    {
        private DNode<T> next;
        private DNode<T> prev;

        public DNode(T value) : base(value)
        {
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
        public override T Value
        {
            get { return item; }
            set { item = value; }
        }

        public override void Invalidate()
        {
            next = null;
            prev = null;
        }
    }
}
