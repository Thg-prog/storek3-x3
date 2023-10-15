package var5;

public class Deck extends ClassQD {
    // Метод для извлечения элемента из конца дека
    public Elem popTail() {
        if (tail != null) {
            if (head == tail) {
                // Если в деке только один элемент, обнуляем head и tail
                head = null;
                tail = null;
            } else {
                Elem current = head;
                while (current.next != tail) {
                    current = current.next;
                }
                current.next = null; // Отсоединяем tail
                tail = current; // Обновляем tail
            }
            return tail;
        } else {
            return null; // Дек пуст
        }
    }

    // Метод для добавления элемента в начало дека
    public void push(Elem el) {
        if (el != null) {
            if (head == null) {
                // Если дек пуст, устанавливаем и голову, и хвост на новый элемент
                head = el;
                tail = el;
            } else {
                el.next = head; // Новый элемент указывает на текущий головной элемент
                head = el; // Головной элемент становится новым элементом
            }
        }
    }
}
