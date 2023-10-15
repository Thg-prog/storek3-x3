package var4;

class Stack {
    public Elem head; // Головной элемент стека

    // Конструктор для создания пустого стека
    public Stack() {
        this.head = null;
    }

    // Метод для добавления элемента на вершину стека
    public void push(Elem el) {
        if (el != null) {
            el.next = head; // Устанавливаем ссылку на текущий верхний элемент
            head = el; // Обновляем головной элемент
        }
    }

    // Метод для извлечения и удаления элемента с вершины стека
    public Elem pop() {
        if (head == null) {
            // Стек пуст, нельзя выполнить pop
            return null;
        } else {
            Elem top = head; // Запоминаем верхний элемент
            head = head.next; // Обновляем головной элемент
            top.next = null; // Отсоединяем верхний элемент от стека
            return top; // Возвращаем извлеченный элемент
        }
    }
}
