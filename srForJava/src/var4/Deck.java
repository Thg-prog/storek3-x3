package var4;

public class Deck extends ClassQD {
    // Метод для извлечения и удаления элемента из конца очереди (хвоста)
    public Elem popTail() {
        if (isEmpty()) {
            // Очередь (или дек) пуста, нельзя выполнить извлечение с хвоста
            return null;
        } else {
            Elem current = tail;
            Elem previous = null;

            while (current.next != null) {
                previous = current;
                current = current.next;
            }

            if (previous != null) {
                previous.next = null; // Обновляем связь предыдущего элемента
            } else {
                // Если удаляем хвостовой элемент, обновляем tail
                tail = null;
            }

            return current;
        }
    }
}
