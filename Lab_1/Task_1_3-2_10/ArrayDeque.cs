using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    public class ArrayDeque<T> : IDeque<T>
    {
        private int front, back;
        private int Front
        {
            get { return front; }
            set
            {
                front = value % size;
            }
        }
        private int Back
        {
            get { return back; }
            set
            {
                back = value % size;
            }
        }
        private readonly int size;
        private T[] deque;

        public int Count { get; private set; } = 0;

        public ArrayDeque(int size)
        {
            this.size = size;
            this.deque = new T[size];
            front = -1;
            back = -1;
        }

        public bool isEmpty() => front == back;

        public T PeekBack()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                return deque[back];
            }
        }
        public T PeekFront()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
                return deque[front];
        }
        public T PopBack()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                T data = deque[back--];
                Count--;
                return data;
            }
        }
        public T PopFront()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                T data = deque[front++];
                Count--;
                return data;
            }
        }
        public void PushBack(T item)
        {
            if (Count >= size)
                throw new OverflowException("Deque is full");
            else
            {
                deque[++back] = item;
                Count++;
            }
        }
        public void PushFront(T item)
        {
            if (Count >= size)
                throw new OverflowException("Deque is full");
            else
            {
                deque[--front] = item;
                Count++;
            }
        }
    }
}
