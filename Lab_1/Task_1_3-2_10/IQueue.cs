using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    interface IQueue<T>
    {
        /// <summary>
        /// Check whether the queue is empty
        /// </summary>
        /// <returns></returns>
        bool isEmpty();
        /// <summary>
        /// Adds a new element to the end of the queue
        /// </summary>
        /// <param name="item"> Element to add</param>
        void Enqueue(T item);
        /// <summary>
        /// Removes and returns the object at the beginning of the queue
        /// </summary>
        /// <exception cref="InvalidOperationException"> Thrown when the queue is empty </exception>
        /// <returns></returns>
        T Dequeue();
        /// <summary>
        /// Returns the object at the beginning of the queue without removing it.
        /// </summary>
        /// <returns></returns>
        T Peek();
    }
}
