package var2;

public class Queue extends Stack {
    Elem tail; // Поле tail для хранения конца очереди

    // Переопределяем метод push, чтобы добавление элемента в очередь осуществлялось с учетом tail
    @Override
    public void push(Elem el) {
        if (el != null) {
            if (head == null) {
                // Если очередь пуста, устанавливаем и голову, и хвост на новый элемент
                head = el;
                tail = el;
            } else {
                // Иначе добавляем элемент в конец очереди (хвост)
                tail.next = el;
                tail = el;
            }
        }
    }

    // Метод для добавления элемента в начало очереди (переопределенный метод)
    public void pushHead(Elem el) {
        if (el != null) {
            el.next = head;
            head = el;
            if (tail == null) {
                // Если очередь была пуста, устанавливаем хвост на новый элемент
                tail = el;
            }
        }
    }

    // Переопределенный метод pop для удаления и возврата элемента из начала очереди
    @Override
    public Elem pop() {
        if (head != null) {
            Elem popped = head; // Запоминаем элемент в начале очереди
            head = head.next; // Изменяем голову на следующий элемент
            if (head == null) {
                // Если очередь пуста, устанавливаем хвост в null
                tail = null;
            }
            popped.next = null; // Удаляем связь с остальными элементами
            return popped;
        } else {
            return null; // Очередь пуста
        }
    }
}
