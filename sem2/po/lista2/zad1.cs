//Maciej Styś lista2 zad1

using System;

namespace zad1
{
    class Program{
        static void Main(string[] args){
            RandomWordStream rws = new RandomWordStream();
            PrimeStream ps = new PrimeStream();
            int x = 5;
            while(x > 0){
                Console.WriteLine(rws.next());
                x--;
            }
        }
    }

    class IntStream{
        private int num = 0;

        public virtual int next(){
            return num++;
        }

        public virtual bool eos(){
            return num == int.MaxValue;
        }

        public virtual void reset(){
            num = 0;
        }
    }

    class PrimeStream : IntStream{
        private int x;

        int Prime(int i){
            if(i < 2) return 0;
            if(i == 2) return 1;

            for(int x = 2; x <= Math.Sqrt(i); x++){
                if(i%x == 0) return 0;
            }

            return 1;
        }

        override public int next(){
            while(Prime(x = base.next()) != 1){
                if(x == int.MaxValue){
                    break;
                }
            }

            return x;
        }

        public override bool eos(){
            return x == int.MaxValue;
        }

        public override void reset(){
            base.reset();
        }

    }

    class RandomStream : IntStream{

        override public int next(){
            return new Random().Next();
        }
    
        override public bool eos(){
            return false;
        }
    
    }

    class RandomWordStream{
        private RandomStream rs = new RandomStream();
        private PrimeStream ps = new PrimeStream();

        public string next(){
            string word = "";
            int len = ps.next();
            for(int x = 0; x < len; x++){
                char letter = (char)(rs.next() % 26 + 65);
                word += letter.ToString();
            }

            return word;
        }

        public void reset(){
            ps.reset();
        }

    }

}