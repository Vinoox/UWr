using System.Collections;


interface ListCollection<T>
{
    void Remove(T value);
    void Show();
    bool IsEmpty();
}

public class Lista<T> : ListCollection<T>
    {
        public class Node
        {
            public T content;
            public Node? next;

            public Node(T content)
            {
                this.content = content;
                next = null;
            }
        }

        public Node? head;
        public Node? tail;

        public bool IsEmpty() => head == null;

        public void Add(T value){
            Node newNode = new(value);
            if(IsEmpty() == true) head = tail = newNode;
            else{
                tail.next = newNode;
                tail = newNode;
            }
        }

        public void Remove(T value){
            Node current = head;
            Node previous = null;
            while(current != null){
                if(current.content.Equals(value)){
                    if(previous == null){ 
                        head = current.next;
                        return;   
                    }
                    previous.next = current.next;
                    return;
                }
                previous = current;
                current = current.next;
            }
        }

        public void Show(){
            Node current = head;
            while(current != null){
                Console.WriteLine(current.content);
                current = current.next;
            }
        }

    }

public class MyDictionary<K, V> : ListCollection<K>
    {
        public class Node
        {
            public K key;
            public V content;
            public Node? next;

            public Node(K key, V content){
                this.key = key;
                this.content = content;
                next = null;
            }
        }

        public Node? start;

        public bool IsEmpty() => start == null;

        public V? Find(K key){
        
            Node? current = start;

            while(current != null){
                if(current.key!.Equals(key)) return current.content;
                current = current.next;
            }

            Console.WriteLine($"PODANY KLUCZ NIE ISTNIEJE: {key}");
            return default;
        }

        public void Add(K key, V content){
            if (IsEmpty() == true){
                start = new(key, content);
                Console.WriteLine($"DODANO WARTOSC: {content}");
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
                current.next = new(key, content);
                Console.WriteLine($"DODANO WARTOSC: {content}");
            }
        }

        public void Remove(K key){

            if (start == null){
                Console.WriteLine($"BRAK PODANEGO KLUCZA: {key}");
                return;
            }

            if(start.key!.Equals(key)){
                Console.WriteLine($"USUNIETO WARTOSC: {start.content}");
                start = start.next;
                return;
            }

            Node previous = start;
            Node? current = start.next;
            while(current != null){
                if(current.key!.Equals(key)){
                    previous.next = current.next;
                    Console.WriteLine($"USUNIETO WARTOSC: {current.content}");
                    return;
                }
            }
            Console.WriteLine($"BRAK PODANEGO KLUCZA {key}");
            return;
        }

        public void Show(){
            Node current = start;
            while(current != null){
                Console.WriteLine($"{current.key} : {current.content}");
                current = current.next;
            }
        }
    }

class Program
{
    static void Main()
    {
        MyDictionary<string, int> intSlowanik = new();
        Lista<int> intLista = new();

        intLista.Add(2);
        intLista.Add(1);
        intLista.Add(3);
        intSlowanik.Add("siedem", 7);
        intSlowanik.Add("jeden", 1);
        intSlowanik.Add("dycha", 10);

        intSlowanik.Remove("jeden");
        intLista.Remove(5);
        Console.WriteLine($"{intLista.IsEmpty()} {intSlowanik.IsEmpty()}");

        intLista.Show();
        intSlowanik.Show();

    }
}