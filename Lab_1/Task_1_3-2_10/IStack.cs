using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    public interface IStack<T>
    {
        /// <summary>
        /// Deletes all elements
        /// </summary>
        void Clear();
        /// <summary>
        /// Checks whether there is no elemets in the stack
        /// </summary>
        /// <returns></returns>
        bool isEmpty();
        /// <summary>
        /// Inserts an object as the top element of the stack
        /// </summary>
        /// <exception cref="OverflowException"> Thrown when the stack is full </exception>
        /// <param name="item"></param>
        void Push(T item);
        /// <summary>
        /// Gets top element and removes him
        /// <exception cref="InvalidOperationException"> Thrown when the stack is empty </exception>
        /// </summary>
        T Pop();
        /// <summary>
        /// Gets top element without removing him
        /// <exception cref="InvalidOperationException"> Thrown when the stack is empty </exception>
        /// </summary>
        T Peek();
    }
}
