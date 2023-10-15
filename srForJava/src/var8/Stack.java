package var8;

public class Stack {
    Elem head; // Головной элемент стека

    // Конструктор класса Stack
    public Stack() {
        this.head = null;
    }

    // Метод для добавления элемента в стек
    public void push(Elem el) {
        if (el != null) {
            el.next = head; // Новый элемент указывает на текущий головной элемент
            head = el; // Головной элемент становится новым элементом
        }
    }

    // Метод для извлечения элемента из стека
    public Elem pop() {
        if (head == null) {
            return null; // Стек пуст, возвращаем null
        } else {
            Elem top = head; // Сохраняем верхний элемент стека
            head = top.next; // Головной элемент становится следующим элементом
            top.next = null; // Удаляем связь верхнего элемента
            return top; // Возвращаем извлеченный элемент
        }
    }
    public String toString()
    {
        StringBuilder value = new StringBuilder();
        Elem tmp = this.head;
        while (tmp != null) {
            value.append(tmp.value).append(" ");
            tmp = tmp.next;
        }
        return value.toString();
    }
}