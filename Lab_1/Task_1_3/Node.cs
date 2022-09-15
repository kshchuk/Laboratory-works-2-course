using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    internal sealed class Node<T>
    {
        public T data;
        public Node<T>? next, prev;

        Node(T data)
        {
            this.data = data;
            this.next = null;
            this.prev = null;
        }
    }
}
