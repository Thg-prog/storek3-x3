package var0;

public class Stack {
    Elem head;

    public void push(Elem element) {
        if (head == null) {
            head = element;
        } else {
            element.setNext(head);
            head = element;
        }
    }

    public Elem pop() {
        if (head == null) {
            System.out.println("Стек пуст");
            return null;
        } else {
            Elem poppedElement = head;
            head = head.getNext();
            return poppedElement;
        }
    }
}
