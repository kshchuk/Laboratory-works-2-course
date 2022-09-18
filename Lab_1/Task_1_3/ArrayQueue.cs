using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    public class ArrayQueue<T> : IQueue<T>
    {
        private int front, end;
        private readonly int size;
        private T[] queue;

        public ArrayQueue(int size)
        {
            this.size = size;
            queue = new T[size];
            front = 0;
            end = 0;
        }
        public T Dequeue()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            {
                T data = queue[front];
                for (int i = 0; i < end - 1; i++)
                {
                    queue[i] = queue[i + 1];
                }

                if (end < size)
                    queue[end] = default(T);

                end--;
                return data;
            }   
        }
        public void Enqueue(T item)
        {
            if (size == end)
            {
                throw new OverflowException("Queue is full");
            }
            else
            {
                queue[end] = item;
                end++;
            }
            return;
        }
        public bool isEmpty() => front == end;
        public T Peek()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
                return queue[front];
        }
    }
}
