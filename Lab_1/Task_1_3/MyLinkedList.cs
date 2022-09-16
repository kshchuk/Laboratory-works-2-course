using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;

namespace Task_1_3
{
    public class MyLinkedList<T> : ICollection<T>, IEnumerable<T>, IEnumerator<T>, ICollection
    {   
        protected Node<T> head;

        public MyLinkedList()
        {
            head = null;
        }

        // Implementing ICollection<T>, ICollection interfaces
        public int Count { get; private set; } = 0;
        public bool IsReadOnly => false;
        public bool IsSynchronized => false;
        public object SyncRoot { get; } = new object();
        public void Add(T item)
        {
            if (head == null)
                head = new Node<T>(item);
            else
            {
                Node<T> current = head;
                while (current.Next != null) current = current.Next;
                current.Next = new Node<T>(item);
            }
            Count++;
        }
        public void Clear()
        {
            Node<T> current = head;
            while(current != null)
            {
                Node<T> temp = current;
                current = current.Next;
                temp.Invalidate();
            }
            Count = 0;
        }
        public bool Remove(T item)
        {
            Node<T> current = head;
            if (current != null)
            {
                if (current.Value.Equals(item))
                {
                    head = head.Next;
                    current.Invalidate();
                    return true;
                }
                while (current.Next != null)
                {
                    if (current.Next.Value.Equals(item))
                    {
                        Node<T> temp = current.Next;
                        current.Next = current.Next.Next;
                        temp.Invalidate();
                        return true;
                    }
                }
            }
            return false;
        }
        public bool Contains(T item)
        {
            Node<T> current = head;
            while (current != null)
            {
                if (current.Value.Equals(item))
                    return true;
                current = current.Next;
            }
            return false;                       
        }
        public void CopyTo(T[] array, int arrayIndex)
        {
            Node<T> current = head;
            while (current != null)
            {
                array[arrayIndex++] = current.Value;
                current = current.Next;
            }
        }
        public void CopyTo(Array array, int index)
        {
            Node<T> current = head;
            while (current != null)
            { 
                array.SetValue(current.Value, index++);
            }
        }

        public void AddFirst(T item)
        {
            if (head == null)
                head = new Node<T>(item);
            else
            {
                Node<T> node = new Node<T>(item);
                node.Next = head;
                head = node;
            }
            Count++;
        }
        public void AddLast(T item)
        {
            if (head == null)
                head = new Node<T>(item);
            else
            {
                Node<T> current = head;
                while (current.Next != null) current = current.Next;
                current.Next = new Node<T>(item);
            }
            Count++;
        }
        public void AddBefore(T newItem, T item)
        {
            if (head == null)
                throw new ArgumentException("Item does not exist in the list");
            else 
            if (head.Value.Equals(item))
            {
                AddFirst(newItem);
            }
            else
            {
                Node<T> current = head.Next;
                while (current.Next != null)
                {
                    if (current.Next.Value.Equals(item))
                    {
                        Node<T> node = new Node<T>(newItem);
                        node.Next = current.Next;
                        current.Next = node;
                        Count++;
                        return;
                    }
                    current = current.Next;
                }
                // Item did not find
                throw new ArgumentException("Item does not exist in the list");
            }
        }
        public void AddAfter(T newItem, T item)
        {
            if (head == null)
                throw new ArgumentException("Item does not exist in the list");
            else
            {
                Node<T> current = head;
                while (current != null)
                {
                    if (current.Value.Equals(item))
                    {
                        Node<T> node = new Node<T>(newItem);
                        node.Next = current.Next;
                        current.Next = node;
                        Count++;
                        return;
                    }
                    current = current.Next;
                }
                // Item did not find
                throw new ArgumentException("Item does not exist in the list");
            }
        }

        // Implementing IEnumerable<T>, IEnumerator<T> interfaces
        private Node<T> current;
        public T Current => current.Value;
        object IEnumerator.Current => current.Value;
        public IEnumerator<T> GetEnumerator()
        {
            Node<T> current = head;
            while (current!=null)
            {
                yield return current.Value;
                current = current.Next;
            }
        }
        IEnumerator IEnumerable.GetEnumerator()
        {
            return this as IEnumerator;
        }
        public bool MoveNext()
        {
            if (current.Next != null)
            {
                current = current.Next;
                return true;
            }
            else
                return false;
        }
        public void Reset()
        {
            current = head;
        }

        // Implementing IDisposible interface
        public void Dispose()
        {
        }
    }
}
