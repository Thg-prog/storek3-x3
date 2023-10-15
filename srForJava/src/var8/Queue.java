package var8;

public class Queue extends Deck {
    public Elem tail; // Поле tail для конца очереди

    // Конструктор класса Queue
    public Queue() {
        super(); // Вызываем конструктор родительского класса Stack
        this.tail = null;
    }

    // Метод для добавления элемента в конец очереди
    @Override
    public void push(Elem element){
        super.pushTail(element);
    }
}