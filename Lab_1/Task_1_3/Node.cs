using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3
{
    internal sealed class Node<T>
    {
        public T Data { get; set; }
        public Node<T> next, prev;

        public Node(T data)
        {
            this.Data = data;
            this.next = null;
            this.prev = null;
        }

        public static Node<T> operator ++(Node<T> node)
        {
            node = node.next;
            return node;
        }
        public static Node<T> operator --(Node<T> node)
        {
            node = node.prev;
            return node;
        }
    }
}
