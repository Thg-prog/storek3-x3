package var6;

public class Queue extends Spis {
    public Elem tail; // Поле, указывающее на хвост очереди

    // Конструктор по умолчанию
    public Queue() {
        super();
        tail = null;
    }

    // Метод для добавления элемента в конец очереди
    public void push(Elem el) {
        if (el != null) {
            if (head == null) {
                head = el;
                tail = el;
            } else {
                tail.next = el;
                tail = el;
            }
        }
    }

    // Метод для удаления и возврата элемента из начала очереди
    public Elem pop() {
        return super.pop();
    }

    // Метод для добавления элемента в начало очереди
    public void pushHead(Elem el) {
        if (el != null) {
            super.push(el);
        }
    }
}
