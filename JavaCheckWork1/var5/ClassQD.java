package var5;

public class ClassQD extends Spis {
    public Elem tail; // Поле tail для хранения хвоста стека

    // Метод для добавления элемента в конец стека
    public void pushTail(Elem el) {
        if (el != null) {
            if (head == null) {
                // Если стек пуст, устанавливаем и голову, и хвост на новый элемент
                head = el;
                tail = el;
            } else {
                tail.next = el; // Связываем текущий хвост с новым элементом
                tail = el; // Новый элемент становится хвостом
            }
        }
    }

    // Переопределение метода pop для извлечения верхнего элемента
    @Override
    public Elem pop() {
        if (head != null) {
            Elem popped = super.pop(); // Вызываем метод pop из родительского класса
            if (head == null) {
                // Если стек после извлечения пуст, обнуляем хвост
                tail = null;
            }
            return popped;
        } else {
            return null; // Стек пуст
        }
    }
}
