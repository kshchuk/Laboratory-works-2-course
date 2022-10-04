using System;
using System.Collections;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata.Ecma335;
using System.Text;
using System.Threading.Tasks;
using System.Xml.Linq;


namespace list_1
{
    public class MyLinkedList<T> : IList<T>, ICollection<T>, IEnumerable<T>, IEnumerator<T>, ICollection
    {
        protected SNode<T> head;

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
                head = new SNode<T>(item);
            else
            {
                SNode<T> current = head;
                while (current.Next != null) current = current.Next;
                current.Next = new SNode<T>(item);
            }
            Count++;
        }
        public void Clear()
        {
            SNode<T> current = head;
            while(current != null)
            {
                SNode<T> temp = current;
                current = current.Next;
                temp.Invalidate();
            }
            Count = 0;
        }
        public bool Remove(T item)
        {
            SNode<T> current = head;
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
                        SNode<T> temp = current.Next;
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
            SNode<T> current = head;
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
            SNode<T> current = head;
            while (current != null)
            {
                array[arrayIndex++] = current.Value;
                current = current.Next;
            }
        }
        public void CopyTo(Array array, int index)
        {
            SNode<T> current = head;
            while (current != null)
            { 
                array.SetValue(current.Value, index++);
            }
        }

        // Implementing MyList interface
        public void AddFirst(T item)
        {
            if (head == null)
                head = new SNode<T>(item);
            else
            {
                SNode<T> node = new SNode<T>(item);
                node.Next = head;
                head = node;
            }
            Count++;
        }
        public void AddLast(T item)
        {
            if (head == null)
                head = new SNode<T>(item);
            else
            {
                SNode<T> current = head;
                while (current.Next != null) current = current.Next;
                current.Next = new SNode<T>(item);
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
                SNode<T> current = head.Next;
                while (current.Next != null)
                {
                    if (current.Next.Value.Equals(item))
                    {
                        SNode<T> node = new SNode<T>(newItem);
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
                SNode<T> current = head;
                while (current != null)
                {
                    if (current.Value.Equals(item))
                    {
                        SNode<T> node = new SNode<T>(newItem);
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
        private SNode<T> current;
        public T Current => current.Value;
        object IEnumerator.Current => current.Value;
        public IEnumerator<T> GetEnumerator()
        {
            SNode<T> current = head;
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
