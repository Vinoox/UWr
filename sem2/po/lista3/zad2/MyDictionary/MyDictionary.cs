using System;

namespace MyDictionary 
{
    public class MyDictionary<K, V>
    {
        public class Node
        {
            public K key;
            public V value;
            public Node? next;

            public Node(K key, V value){
                this.key = key;
                this.value = value;
                next = null;
            }
        }

        public Node? start;

        public V? Find(K key){
        
            Node? current = start;

            while(current != null){
                if(current.key!.Equals(key)) return current.value;
                current = current.next;
            }

            Console.WriteLine($"PODANY KLUCZ NIE ISTNIEJE: {key}");
            return default;
        }

        public void Add(K key, V value){
            if (start == null){
                start = new(key, value);
                Console.WriteLine($"DODANO WARTOSC: {value}");
            }
            else
            {
                Node current = start;
                while (current.next != null)
                {
                    if (current.key!.Equals(key))
                    {
                        Console.WriteLine($"PODANY KLUCZ JUZ ISTNIEJE: {key}");
                        return;
                    }
                    current = current.next;
                }
                if (current.key!.Equals(key))
                {
                    Console.WriteLine($"PODANY KLUCZ JUZ ISTNIEJE: {key}");
                    return;
                }
                current.next = new(key, value);
                Console.WriteLine($"DODANO WARTOSC: {value}");
            }
        }

        public void Remove(K key){

            if (start == null){
                Console.WriteLine($"BRAK PODANEGO KLUCZA: {key}");
                return;
            }

            if(start.key!.Equals(key)){
                Console.WriteLine($"USUNIETO WARTOSC: {start.value}");
                start = start.next;
                return;
            }

            Node previous = start;
            Node? current = start.next;
            while(current != null){
                if(current.key!.Equals(key)){
                    previous.next = current.next;
                    Console.WriteLine($"USUNIETO WARTOSC: {current.value}");
                    return;
                }
            }
            Console.WriteLine($"BRAK PODANEGO KLUCZA {key}");
            return;
        }


        public void Show(){
            Node? current = start;

            while (current != null)
            {
                Console.WriteLine($"{current.key} {current.value}");
                current = current.next;
            }
        }
    }
}