using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    interface INode<T>
    {
        T Value { get; set; }

        /// <summary>
        /// Destructor
        /// </summary>
        public abstract void Invalidate();
    }
}
