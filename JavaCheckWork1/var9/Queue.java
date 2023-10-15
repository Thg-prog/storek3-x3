package var9;

import var8.Elem;

public class Queue extends Stack{
    public Elem tail; // Поле tail для конца очереди

    // Конструктор класса Queue
    public Queue() {
        super(); // Вызываем конструктор родительского класса Stack
        this.tail = null;
    }

    // Метод для добавления элемента в конец очереди
    @Override
    public void push(Elem element){
        if (tail == null) {
            head = element;
            tail = element;
        } else {
            tail.next = element;
            tail = element;
        }
    }

    public void pushHead(Elem element){
        if (head == null) {
            head = element;
            tail = element;
        } else {
            element.next = head;
            head = element;
        }
    }
}
