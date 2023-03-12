//Maciej Styś lista3 zad2 środowisko: Visual Studio

using System;
using MyDictionary;

class Program
{
    static void Main()
    {
        MyDictionary<string, int> intSlownik = new();
        Console.Write(intSlownik.Find("dwa"));
        intSlownik.Add("jeden", 1);
        intSlownik.Add("dwa", 2);
        intSlownik.Add("dwa", 3);
        Console.WriteLine(intSlownik.Find("dwa"));
        intSlownik.Remove("dwa");
        intSlownik.Remove("dwa");

        Console.WriteLine();

        MyDictionary<int, string> stringSlownik = new();
        stringSlownik.Add(0, "hello");
        stringSlownik.Remove(1);
        Console.WriteLine(stringSlownik.Find(1));
        stringSlownik.Add(1, "world");
        Console.WriteLine($"{stringSlownik.Find(0)} {stringSlownik.Find(1)}");
        stringSlownik.Remove(0);
    }
}