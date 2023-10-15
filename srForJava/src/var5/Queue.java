package var5;

public class Queue extends ClassQD {
    // Метод для добавления элемента в очередь
    public void push(Elem el) {
        super.pushTail(el); // Добавляем элемент в конец стека (используя метод из ClassQD)
    }
}
