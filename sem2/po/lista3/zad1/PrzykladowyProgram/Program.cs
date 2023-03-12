//Maciej Styś lista3 zad1 środowisko: Visual Studio

using System;
using Lista;

class Program
{
    static void Main()
    {
        Lista<int> intLista = new();
        Console.WriteLine(intLista.IsEmpty());
        intLista.PushFront(5);
        Console.WriteLine(intLista.IsEmpty());
        intLista.PushBack(10);
        intLista.PushFront(21);
        intLista.PushFront(37);
        Console.WriteLine(intLista.PopFront());
        Console.WriteLine(intLista.PopBack());
        Console.WriteLine(intLista.PopBack());

        Console.WriteLine();
        Lista<string> stringLista = new();
        Console.WriteLine(stringLista.IsEmpty());
        stringLista.PushBack("world");
        Console.WriteLine(stringLista.IsEmpty());
        stringLista.PushFront("hello");
        stringLista.PushFront("test1");
        stringLista.PushFront("test2");
        Console.WriteLine(stringLista.PopFront());
        Console.WriteLine(stringLista.PopBack());
        Console.WriteLine(stringLista.PopBack());
    }
}