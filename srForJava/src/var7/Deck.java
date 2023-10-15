package var7;

public class Deck extends Spis {
    public Elem tail; // Поле для указания на хвост стека

    // Метод для добавления элемента в конец стека (хвост)
    public void pushTail(Elem el) {
        if (el != null) {
            if (head == null) {
                // Если стек пуст, устанавливаем голову и хвост на новый элемент
                head = el;
                tail = el;
            } else {
                // Иначе, добавляем элемент в конец и обновляем хвост
                tail.next = el;
                tail = el;
            }
        }
    }

    // Метод для удаления и возврата верхнего элемента стека (как и унаследованный метод pop)
    @Override
    public Elem pop() {
        return super.pop();
    }

    // Метод для добавления элемента в стек (как и унаследованный метод push)
    @Override
    public void push(Elem el) {
        super.push(el);
    }

    // Метод для удаления и возврата элемента из конца стека (хвоста)
    public Elem popTail() {
        if (tail != null) {
            Elem current = head;
            Elem prev = null;

            while (current.next != null) {
                prev = current;
                current = current.next;
            }

            if (prev != null) {
                prev.next = null;
                tail = prev; // Обновляем хвост
            } else {
                // Если хвостом был головной элемент, то стек оказывается пустым
                head = null;
                tail = null;
            }

            return current;
        } else {
            return null; // Стек пуст
        }
    }
}
