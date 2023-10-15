package var4;

public class ClassQD {
    public Elem tail; // Хвостовой элемент (tail) очереди

    // Конструктор для создания пустой очереди
    public ClassQD() {
        this.tail = null;
    }

    // Метод для добавления элемента в конец очереди
    public void pushTail(Elem el) {
        if (el != null) {
            if (tail == null) {
                // Если очередь пуста, устанавливаем и голову, и хвост на новый элемент
                tail = el;
                tail.next = null;
            } else {
                // Иначе, добавляем новый элемент после хвостового элемента
                Elem current = tail;
                while (current.next != null) {
                    current = current.next;
                }
                current.next = el;
                el.next = null;
            }
        }
    }

    // Метод для извлечения и удаления элемента из начала очереди
    public Elem pop() {
        if (tail == null) {
            // Очередь пуста, нельзя выполнить pop
            return null;
        } else {
            Elem head = tail;
            tail = tail.next; // Обновляем хвост очереди
            head.next = null;
            return head;
        }
    }

    // Дополнительный метод для проверки, пуста ли очередь
    public boolean isEmpty() {
        return tail == null;
    }
}
