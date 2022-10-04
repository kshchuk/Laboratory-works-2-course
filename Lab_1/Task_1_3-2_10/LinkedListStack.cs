using System.Collections;

namespace Task_1_3
{
    public class LinkedListStack<T> : IStack<T>
    {
        private SNode<T> top;

        public int Count { get; private set; } = 0;

        public LinkedListStack()
        {
            top = null;
        }

        public void Clear()
        {
            SNode<T> current = top;
            while (current != null)
            {
                SNode<T> temp = current;
                current = current.Next;
                temp.Invalidate();
            }
            Count = 0;
        }
        public T Peek()
        {
            if (this.isEmpty())
                throw new InvalidOperationException("The stack is empty");
            else
            {
                return top.Value;
            }
        }
        public T Pop()
        {
            if (this.isEmpty())
                throw new InvalidOperationException("The stack is empty");
            else
            {
                SNode<T> topNod = top;
                top = top.Next;
                T elem = topNod.Value;
                topNod.Invalidate();
                Count--;
                return elem;
            }
        }
        public bool isEmpty() => Count == 0;
        public void Push(T item)
        {
            SNode<T> node = new SNode<T>(item);
            node.Next = top;
            top = node;
            Count++;
        }
    }
}
