using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    interface IStack<T>
    {
        int Count { get; set; }

        /// <summary>
        /// Deletes all elements
        /// </summary>
        void Clear();
        /// <summary>
        /// Checks whether there is no elemets in the stack
        /// </summary>
        /// <returns></returns>
        bool isEmppy();
        /// <summary>
        /// Inserts an object as the top element of the stack
        /// </summary>
        /// <param name="item"></param>
        void Push(T item);
        /// <summary>
        /// Gets top element and removes him
        /// </summary>
        T Pop();
        /// <summary>
        /// Gets top element without removing him
        /// </summary>
        T Peek();
    }
}
