package var2;

public class Deck extends Queue {
    // Добавляем метод для удаления и возврата элемента из хвоста дека
    public Elem popTail() {
        if (head != null) {
            Elem current = head;
            Elem previous = null;

            while (current.next != null) {
                previous = current;
                current = current.next;
            }

            if (previous == null) {
                // Если у нас есть только один элемент в очереди
                head = null;
                tail = null;
            } else {
                // Иначе, обновляем хвост
                previous.next = null;
                tail = previous;
            }

            return current;
        } else {
            return null; // Дек пуст
        }
    }
}
