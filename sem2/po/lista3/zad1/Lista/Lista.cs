using System;

namespace Lista
{
    public class Lista<T>
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

        public void PushFront(T content)
        {
            Node newNode = new(content);

            if (head == null) head = tail = newNode;
            else
            {
                newNode.next = head;
                head = newNode;
            }
        }

        public void PushBack(T content)
        {
            Node newNode = new(content);

            if (tail == null) head = tail = newNode;
            else
            {
                tail.next = newNode;
                tail = newNode;
            }
        }

        public T PopFront()
        {
            if (head == null) throw new NullReferenceException("Brak elementow do usuniecia");

            T content = head.content;
            head = head.next;

            if (head == null) tail = null;

            return content;
        }

        public T PopBack()
        {
            if (tail == null) throw new NullReferenceException("Brak elementow do usuniecia");

            T content = tail.content;
            if (head == tail) head = tail = null;
            else
            {
                Node current = head!;
                while (current.next != tail)
                {
                    current = current.next!;
                }
                current.next = null;
                tail = current;
            }

            return content;
        }
    }
}