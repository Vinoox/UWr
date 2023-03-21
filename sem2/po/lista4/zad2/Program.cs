//Maciej Styś lista 4 zad 2
//srodowisko: visual studio

using Fibonacci;

class Program
{
    public static void Wypisz(SlowaFibonacciego slowa)
    {
        foreach (string slowo in slowa) Console.WriteLine(slowo);
    }

    static void Main()
    {
        SlowaFibonacciego slowa = new(6);
        Wypisz(slowa);
    }
}