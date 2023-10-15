package var3;

public class Deck extends Stack {
    Elem tail; // Хвостовой элемент дека

    // Метод для добавления элемента в конец дека
    public void pushTail(Elem el) {
        if (el != null) {
            if (tail == null) {
                // Если дек пуст, устанавливаем голову и хвост на новый элемент
                head = el;
                tail = el;
            } else {
                // Иначе, добавляем элемент к хвосту
                tail.next = el;
                tail = el;
            }
        }
    }

    // Метод для удаления и возврата верхнего элемента дека
    @Override
    public Elem pop() {
        // Переопределяем метод pop из класса Stack
        return super.pop();
    }

    // Метод для добавления элемента в начало дека (переопределяем метод из класса Stack)
    @Override
    public void push(Elem el) {
        super.push(el);
    }

    // Метод для удаления и возврата хвостового элемента дека
    public Elem popTail() {
        if (head == null || tail == null) {
            return null; // Дек пуст
        }

        if (head == tail) {
            // Если в деке всего один элемент, то удаляем его
            Elem popped = head;
            head = null;
            tail = null;
            return popped;
        } else {
            // Иначе, находим предпоследний элемент и удаляем хвост
            Elem current = head;
            while (current.next != tail) {
                current = current.next;
            }
            Elem popped = tail;
            current.next = null;
            tail = current;
            return popped;
        }
    }
}
