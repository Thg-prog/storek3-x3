package var5;

public class Spis {
    public Elem head;

    // Метод для добавления элемента в вверх
    public void push(Elem el) {
        if (el != null) {
            el.next = head; // Новый элемент указывает на текущий головной элемент
            head = el; // Головной элемент становится новым элементом
        }
    }

    // Метод для удаления и возврата верхнего элемента
    public Elem pop() {
        if (head != null) {
            Elem popped = head; // Запоминаем верхний элемент
            head = head.next; // Головной элемент изменяется на следующий элемент
            popped.next = null; // Удаляем связь с остальными элементами
            return popped; // Возвращаем удаленный элемент
        } else {
            return null;
        }
    }
}
