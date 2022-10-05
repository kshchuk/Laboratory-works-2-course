using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace list_1
{
    public class LinkedListQueue<T> : IQueue<T>
    {
        private SNode<T> front;
        private SNode<T> end;

        public LinkedListQueue()
        {
            this.front = null;
            this.end = null;
        }


        public T Dequeue()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else
            if (front == end)
            {
                var temp = front;
                front = null;
                end = null;
                return temp.Value;
            }
            else
            {
                var temp = front;
                front = front.Next;
                return temp.Value;
            }         
        }
        public void Enqueue(T item)
        {
            if (isEmpty())
            {
                front = new SNode<T>(item);
                end = front;
            }
            else 
            {
                SNode<T> node = new SNode<T>(item);
                end.Next = node;
                end = node;
            }
        }
        public bool isEmpty() => front == null;
        public T Peek()
        {
            if (isEmpty())
                throw new InvalidOperationException("Queue is empty");
            else 
                return front.Value;
        }
    }
}
