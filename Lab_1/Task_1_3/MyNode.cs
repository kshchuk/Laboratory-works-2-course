using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    interface MyNode<T>
    {
        T Value { get; set; }

        /// <summary>
        /// Destructor
        /// </summary>
        public abstract void Invalidate();
    }
}
