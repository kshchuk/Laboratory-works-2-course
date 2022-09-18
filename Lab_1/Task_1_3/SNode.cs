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
    public class SNode<T> : MyNode<T>
    {
        private new SNode<T> next;

        public SNode(T value)
            : base(value) { }
        public SNode<T> Next
        {
            get { return next; }
            set { next = value; }
        }
        public override T Value
        {
            get { return item; }
            set { item = value; }
        }
        public override void Invalidate()
        {
            next = null;
        }
    }
}
