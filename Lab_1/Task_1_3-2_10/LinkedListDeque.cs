using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    public class LinkedListDeque<T> : IDeque<T> //: IQueue, IStack ???
    {
        private DNode<T> front;
        private DNode<T> back;

        public int Count { get; private set; } = 0;

        public bool isEmpty() => Count == 0;

        public T PeekBack()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                return back.Value;
            }

        }
        public T PeekFront()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                return front.Value;
            }
        }
        public T PopBack()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                var temp = back;
                back = back.Prev;
                back.Next = null;
                Count--;
                return temp.Value;
            }
        }
        public T PopFront()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                var temp = front;
                front = front.Next;
                front.Prev = null;
                Count--;
                return temp.Value;
            }
        }
        public void PushBack(T item)
        {
            back.Next = new DNode<T>(item);
            back.Next.Prev = back;
            back = back.Next;
            Count++;
        }
        public void PushFront(T item)
        {
            front.Prev = new DNode<T>(item);
            front.Prev.Next = front;
            front = front.Prev;
            Count++;
        }
    }
}
