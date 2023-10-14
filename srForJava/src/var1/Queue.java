package var1;

public class Queue extends Stack {
    public Elem tail; // Поле tail для конца очереди

    // Конструктор класса Queue
    public Queue() {
        super(); // Вызываем конструктор родительского класса Stack
        this.tail = null;
    }

    // Метод для добавления элемента в конец очереди
    @Override
    public void push(Elem el) {
        super.push(el); // Используем метод push родительского класса Stack для добавления в конец
        if (tail == null) {
            tail = el; // Если очередь пуста, tail устанавливается на новый элемент
        }
    }

    // Метод для добавления элемента в начало очереди
    public void pushHead(Elem el) {
        if (el != null) {
            el.next = null; // Новый элемент становится последним
            if (head == null) {
                head = el;
                tail = el;
            } else {
                el.next = head; // Новый элемент указывает на текущий головной элемент
                head = el; // Новый элемент становится головным
            }
        }
    }

    // Метод для извлечения элемента из начала очереди
    @Override
    public Elem pop() {
        if (head == null) {
            return null; // Очередь пуста, возвращаем null
        } else {
            Elem front = head; // Сохраняем передний элемент очереди
            head = front.next; // Головной элемент становится следующим элементом
            front.next = null; // Удаляем связь переднего элемента
            if (head == null) {
                tail = null; // Если удалили последний элемент, обнуляем tail
            }
            return front; // Возвращаем извлеченный элемент
        }
    }
}

