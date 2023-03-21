//Maciej Styś lista 4 zad 2
//srodowisko: visual studio

using System.Collections;

namespace Fibonacci
{
    public class SlowaFibonacciego : IEnumerable
    {
        public string[] slowaArray;

        public string GenerujSlowo(int n)
        {
            if (n == 1) return "b";
            if (n == 2) return "a";
            return GenerujSlowo(n - 1) + GenerujSlowo(n - 2);
        }

        public SlowaFibonacciego(int n)
        {
            slowaArray = new string[n];
            
            for(int x = 0; x < n; x++) slowaArray[x] = GenerujSlowo(x + 1);
        }

        public IEnumerator GetEnumerator()
        {
            return slowaArray.GetEnumerator();
        }
    }
}