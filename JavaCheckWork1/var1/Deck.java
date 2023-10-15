package var1;

public class Deck extends Queue {
    // Конструктор класса Deck
    public Deck() {
        super(); // Вызываем конструктор родительского класса Queue
    }

    // Метод для извлечения элемента из конца очереди (дека)
    public Elem popTail() {
        if (tail == null) {
            return null; // Дек пуст, возвращаем null
        } else {
            Elem last = tail; // Сохраняем последний элемент дека
            if (head == tail) {
                // Если в деке всего один элемент
                head = null;
                tail = null;
            } else {
                // Иначе находим предпоследний элемент
                Elem current = head;
                while (current.next != tail) {
                    current = current.next;
                }
                tail = current; // Предпоследний элемент становится конечным
                tail.next = null; // Удаляем связь последнего элемента
            }
            return last; // Возвращаем извлеченный элемент
        }
    }
}
