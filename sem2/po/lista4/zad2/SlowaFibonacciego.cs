using System;
using System.Collections;

namespace Fibonacci
{
    class SlowaFibonacciego : IEnumerable
    {
        public string slowo(int n){
            if(n == 1) return "b";
            if(n == 2) return "a";
            return slowo(n -1) + slowo(n - 2);
        }

        public IEnumerator GetEnumerator(){
            return new ListEnum<T>(lista);
        }

    }

    class Program
    {
        static void Main() => System.Console.WriteLine(new SlowaFibonacciego().slowo(6));
    }
}