using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    interface IDeque<T>
    {

        /// <summary>
        /// Adds a new element at the end of the queue
        /// </summary>
        /// <param name="item"> Element to add</param>
        /// <exception cref="OverflowException"> Thrown when the dequeue is full </exception>
        void PushBack(T item);
        /// <summary>
        /// Removes and returns the object at the end of the queue.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="InvalidOperationException"> Thrown when the dequeue is empty </exception>
        T PopBack();
        /// <summary>
        /// Adds a new element at the beginning of the queue
        /// </summary>
        /// <param name="item"> Element to add</param>
        void PushFront(T item);
        /// <summary>
        /// Removes and returns the object at the beginning of the queue.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="InvalidOperationException"> Thrown when the dequeue is empty </exception>
        T PopFront();
        /// <summary>
        /// Returns the object at the end of the queue without removing it.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="InvalidOperationException"> Thrown when the dequeue is empty </exception>
        T PeekBack();
        /// <summary>
        /// Returns the object at the beginning of the queue without removing it.
        /// </summary>
        /// <returns></returns>
        /// <exception cref="InvalidOperationException"> Thrown when the dequeue is empty </exception>
        T PeekFront();

        bool isEmpty();
    }
}
