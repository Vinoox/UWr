//Maciej Styś lista4 zad1
//srodowisko: visual studio

namespace Interfejs
{
    interface IListCollection<T>
    {
        void Remove(T value);
        void Show();
        bool IsEmpty();
    }
}