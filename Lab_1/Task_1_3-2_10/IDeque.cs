using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    interface IDeque<T>
    {
        void PushBack(T item);
        T PopBack();
        void PushFront(T item);
        T PopFront();
        T PeekBack();
        T PeekFront();
        bool isEmpty();
    }
}
