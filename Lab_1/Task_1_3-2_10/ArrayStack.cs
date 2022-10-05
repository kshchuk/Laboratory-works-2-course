using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace list_1
{
    public class ArrayStack<T> : IStack<T>
    {
        /// <summary>
        /// Location of the top element in the array
        /// </summary>
        private int top;
        private int Top 
        {
            get
            {
                return top;
            }
            set
            {
                if (value < 0)
                    value = size - 1;
                top = value;
            }
        }
        /// <summary>
        /// Max size of the stack
        /// </summary>
        private readonly int size;
        private T[] stack;

        public int Count { get; private set; } = 0;

        public ArrayStack(int size)
        {
            this.size = size;
            this.stack = new T[size];
            top = -1;
        }

        public void Clear()
        {
            Count = 0;
        }
        public bool isEmpty() => Count == 0;
        public T Peek()
        {
            if (isEmpty())
                throw new InvalidOperationException("Stack is empty");
            else
            {
                return stack[Top];
            }
        }
        public T Pop()
        {
            if (isEmpty())
                throw new InvalidOperationException("Stack is empty");
            else
            {
                Count--;
                return stack[Top--];
            }
        }
        public void Push(T item)
        {
            if (Count >= size)
                throw new OverflowException("Stack overflow");
            stack[++Top % size] = item;
            //Top++;
            Count++;
        }
    }
}
