using Task_1_3;


MyLinkedList<int> list = new MyLinkedList<int> { 1, 2, 3 };


Console.WriteLine(list.Count);
Console.WriteLine(list.Contains(3));
Console.WriteLine(list.Contains(4));

list.AddFirst(0);
list.AddBefore(-1, 0);
list.AddAfter(4, 2);
list.AddBefore(4343, 4);


foreach (int i in list)
    Console.WriteLine(i);
Console.WriteLine();
