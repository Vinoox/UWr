//Maciej Styś lista2 zad4

using System;
using System.Collections.Generic;
using System.Linq;

namespace zad4
{
    class Program{
        static void Main(string[] args){
            LazyIntList list = new LazyIntList();
            Console.WriteLine(list.size());
            Console.WriteLine(list.element(40));
            Console.WriteLine(list.size());
            Console.WriteLine(list.element(38));
            Console.WriteLine(list.size());

            LazyPrimeList primeList = new LazyPrimeList();   //2 3 5 7 11 13 17 19 23 29
            Console.WriteLine(primeList.size());             //1 2 3 4  5  6  7  8  9 10   
            Console.WriteLine(primeList.element(5)); 
            Console.WriteLine(primeList.element(1));
            Console.WriteLine(primeList.size());
            Console.WriteLine(primeList.element(10));
        }
    }

    class LazyIntList{
        public List<int> list = new List<int>();

        public int size(){
            return list.Count();
        }

        virtual public int element(int i){
            int size = list.Count();

            if(size < i){
                for(int x = size + 1; x <= i; x++){
                    list.Add(x);
                }
            }

            return list[i - 1];
        }
    }

    class LazyPrimeList : LazyIntList{
        int Prime(int i){
            if(i < 2) return 0;
            if(i == 2) return 1;

            for(int x = 2; x <= Math.Sqrt(i); x++){
                if(i%x == 0) return 0;
            }

            return 1;
        }

        override public int element(int i){
            int size = list.Count();

            if(size < i){
                int x = list.LastOrDefault(1) + 1;
                
                while(size < i){
                    if(Prime(x) == 1){
                        size++;
                        list.Add(x);
                    }
                    x++;
                }
            }

            return list[i - 1];
        }
    }

}