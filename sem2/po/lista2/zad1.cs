//Maciej Styś lista2 zad1

using System;

namespace zad1
{
    class Program{
        static void Main(string[] args){    //przykladowe dzialanie obiektu typu RandomWordStream
            RandomWordStream rws = new RandomWordStream();
            int x = 5;
            while(x > 0){
                Console.WriteLine(rws.next());
                x--;
            }
            rws.reset();
            Console.WriteLine(rws.next());
        }
    }

    class IntStream{
        public int num = 0;

        public virtual int next() => num++;

        public virtual bool eos() => num == int.MaxValue;

        public virtual void reset() => num = 0;
    }

    class PrimeStream : IntStream{

        int Prime(int i){
            if(i < 2) return 0;
            if(i == 2) return 1;

            for(int x = 2; x <= Math.Sqrt(i); x++){
                if(i%x == 0) return 0;
            }

            return 1;
        }

        override public int next(){
            num++;
            while(Prime(num) != 1){
                base.next();
            }

            return num;
        }
    }

    class RandomStream : IntStream{

        override public int next() => new Random().Next();

        override public bool eos() => false;

    }

    class RandomWordStream : PrimeStream{
        private RandomStream rs = new RandomStream();

        new public string next(){
            string word = "";
            int len = base.next();
            for(int x = 0; x < len; x++){
                word += ((char)(rs.next() % 26 + 65));
            }

            return word;
        }
    }

}