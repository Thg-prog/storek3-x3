package var0;

public class Queue extends Deck {
    @Override
    public void push(Elem element) {
        super.pushTail(element); // Добавляем элемент в конец очереди
    }
}
