using list_2;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Task_1_3_2_10
{
    internal class Menu
    {
        private enum ContainerType
        {
            Stack = 1,
            Queue,
            Dequeu
        };

        private enum ContainerSubType
        {
            Array = 1,
            LinkedList,
            Library
        }

        private enum StackCommand
        {
            Push = 1,
            Pop,
            Peek,
            isEmpty
        }

        private enum QueueCommand
        {
            Enqueue = 1,
            Dequeue,
            Peek,
            IsEmpty
        }

        private enum DequeCommand
        {
            PushBack = 1,
            PushFront,
            PeekBack,
            PeekFront,
            PopBack,
            PopFront,
            IsEmpty
        }

        public void MainMenu()
        {
            while (true)
            {
                Console.Write("Choose container: \n" +
                    "    1 - Stack\n" +
                    "    2 - Queue\n" +
                    "    3 - Dequeu\n" +
                    "    0 - Exit\n\n");

                ContainerType containerType =
                    (ContainerType)Convert.ToInt32(Console.ReadLine());


                switch (containerType)
                {
                    case ContainerType.Stack:
                        StackMenu();
                        break;
                    case ContainerType.Queue:
                        QueueMenu();
                        break;
                    case ContainerType.Dequeu:
                        DequeueMenu();
                        break;
                    case 0:
                        return;
                    default:
                        continue;
                }
            }
        }

        void StackMenu()
        {
            Console.Write("Choose stack type: \n" +
                "    1 - Array\n" +
                "    2 - Linked list\n" +
                "    0 - Exit\n\n");

            ContainerSubType containerSubType =
                (ContainerSubType)Convert.ToInt32(Console.ReadLine());

            list_1.IStack<Book> stack;

            switch (containerSubType)
            {
                default:
                case ContainerSubType.Array:
                    Console.Write("Type stack size: ");
                    int size = Convert.ToInt32(Console.ReadLine());
                    stack = new list_1.ArrayStack<Book>(size);
                    break;
                case ContainerSubType.LinkedList:
                    stack = new list_1.LinkedListStack<Book>();
                    break;
                case 0:
                    return;
            }


            while (true)
            {
                Console.Write("\n    1 - Push\n" +
                    "    2 - Pop\n" +
                    "    3 - Peek\n" +
                    "    0 - Exit\n\n");

                StackCommand stackCommand =
                    (StackCommand)Convert.ToInt32(Console.ReadLine());

                switch (stackCommand)
                {
                    case StackCommand.Push:
                        try
                        {
                            stack.Push(Book.GetBook());
                        }
                        catch (OverflowException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case StackCommand.Pop:
                        try
                        {
                            Console.WriteLine(stack.Pop().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case StackCommand.Peek:
                        try
                        {
                            Console.WriteLine(stack.Peek().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case StackCommand.isEmpty:
                        Console.WriteLine($"Stack empty? {0}", stack.isEmpty());
                        break;
                    case 0:
                        return;
                    default:
                        continue;
                }
            }
        }

        void QueueMenu()
        {
            Console.Write("Choose queue type: \n" +
                "    1 - Array\n" +
                "    2 - Linked list\n" +
                "    0 - Exit\n\n");

            ContainerSubType containerSubType =
                (ContainerSubType)Convert.ToInt32(Console.ReadLine());

            list_1.IQueue<Book> queue;

            switch (containerSubType)
            {
                default:
                case ContainerSubType.Array:
                    Console.Write("Type queue size: ");
                    int size = Convert.ToInt32(Console.ReadLine());
                    queue = new list_1.ArrayQueue<Book>(size);
                    break;
                case ContainerSubType.LinkedList:
                    queue = new list_1.LinkedListQueue<Book>();
                    break;
                case 0:
                    return;
            }


            while (true)
            {
                Console.Write("\n    1 - Enqueue\n" +
                    "    2 - Dequeue\n" +
                    "    3 - Peek\n" +
                    "    4 - IsEmpty\n" +
                    "    0 - Exit\n\n");

                QueueCommand dequeCommand =
                    (QueueCommand)Convert.ToInt32(Console.ReadLine());

                switch (dequeCommand)
                {
                    case QueueCommand.Enqueue:
                        try
                        {
                            queue.Enqueue(Book.GetBook());
                        }
                        catch (OverflowException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case QueueCommand.Dequeue:
                        try
                        {
                            Console.WriteLine(queue.Dequeue().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case QueueCommand.Peek:
                        try
                        {
                            Console.WriteLine(queue.Peek().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case QueueCommand.IsEmpty:
                        Console.WriteLine($"Queue empty? {0}", queue.isEmpty());
                        break;
                    case 0:
                        return;
                    default:
                        continue;
                }
            }
        }

        void DequeueMenu()
        {
            Console.Write("Choose deque type: \n" +
                "    1 - Array\n" +
                "    2 - Linked list\n" +
                "    0 - Exit\n\n");

            ContainerSubType containerSubType =
                (ContainerSubType)Convert.ToInt32(Console.ReadLine());

            list_1.IDeque<Book> deque;

            switch (containerSubType)
            {
                default:
                case ContainerSubType.Array:
                    Console.Write("Type deque size: ");
                    int size = Convert.ToInt32(Console.ReadLine());
                    deque = new list_1.ArrayDeque<Book>(size);
                    break;
                case ContainerSubType.LinkedList:
                    deque = new list_1.LinkedListDeque<Book>();
                    break;
                case 0:
                    return;
            }

            while (true)
            {
                Console.Write("\n    1 - Push Back\n" +
                    "    2 - Push Front\n" +
                    "    3 - Peek Back\n" +
                    "    4 - Peek Front\n" +
                    "    5 - Pop Back\n" +
                    "    6 - Pop Front\n" +
                    "    7 - Is empty?\n" +
                    "    0 - Exit\n\n");

                DequeCommand dequeuCommand =
                    (DequeCommand)Convert.ToInt32(Console.ReadLine());

                switch (dequeuCommand)
                {
                    case DequeCommand.PushBack:
                        try
                        {
                            deque.PushBack(Book.GetBook());
                        }
                        catch (OverflowException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case DequeCommand.PushFront:
                        try
                        {
                            deque.PushFront(Book.GetBook());
                        }
                        catch (OverflowException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case DequeCommand.PeekBack:
                        try
                        {
                            Console.WriteLine(deque.PeekBack().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case DequeCommand.PeekFront:
                        try
                        {
                            Console.WriteLine(deque.PeekFront().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case DequeCommand.PopBack:
                        try
                        {
                            Console.WriteLine(deque.PopBack().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case DequeCommand.PopFront:
                        try
                        {
                            Console.WriteLine(deque.PopFront().ToString());
                        }
                        catch (InvalidOperationException e)
                        {
                            Console.WriteLine(e.Message);
                        }
                        break;
                    case DequeCommand.IsEmpty:
                        Console.WriteLine($"Queue empty? {0}", deque.isEmpty());
                        break;
                    default:
                        break;
                }

            }
        }
    }
}
