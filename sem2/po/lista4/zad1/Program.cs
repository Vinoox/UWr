//Maciej Styś lista4 zad1
//srodowisko: visual studio

using Lista;
using Slownik;

class Program   //przykladowe wykorzystanie zaprogramowanych kolekcji
{
    static void Main()
    {
        MyDictionary<string, int> intSlowanik = new();
        Lista<int> intLista = new();

        for (int x = 0; x < 5; x++) intLista.Add(x); //uzupelnienie listy

        Console.WriteLine(intLista); //wypisuje zawartosc listy (wykorzystanie metody ToString)
       
        //uzupelnienie slownika
        intSlowanik.Add("siedem", 7);
        intSlowanik.Add("jeden", 1);
        intSlowanik.Add("dycha", 10);

        //wykorzystanie zaimplementowanych metod z interfejsu IListCollection<T>
        intSlowanik.Remove("jeden");
        intLista.Remove(1);
        
        Console.WriteLine($"Zawartosc slownika: ");
        intSlowanik.Show();

        for (int i = 0; i < intLista.Length; i++) Console.WriteLine(intLista[i]);

        foreach(int x in intLista)
        {
            Console.Write(x);
        }
    }
}