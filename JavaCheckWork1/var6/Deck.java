package var6;

public class Deck extends Queue {
    // Конструктор по умолчанию
    public Deck() {
        super();
    }

    // Метод для удаления и возврата элемента из конца дека
    public Elem popTail() {
        if (head == null) {
            return null; // Дек пуст
        }
        if (head == tail) {
            Elem removedElement = head;
            head = null;
            tail = null;
            return removedElement;
        }

        Elem current = head;
        while (current.next != tail) {
            current = current.next;
        }

        Elem removedElement = tail;
        tail = current;
        tail.next = null;
        return removedElement;
    }
}
