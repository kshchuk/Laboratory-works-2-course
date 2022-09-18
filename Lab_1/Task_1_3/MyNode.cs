using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    /// <summary>
    /// Base class for all nodes
    /// </summary>
    /// <typeparam name="T"></typeparam>
    public abstract class MyNode<T>
    {
        protected MyNode<T> next;
        protected T item;

        public MyNode(T value)
        {
            this.item = value;
        }

        public abstract T Value { get; set; }

        /// <summary>
        /// Destructor
        /// </summary>
        public abstract void Invalidate();
    }
}
