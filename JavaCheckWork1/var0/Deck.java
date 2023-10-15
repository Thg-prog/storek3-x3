package var0;

public class Deck extends Stack {
    private Elem tail;

    @Override
    public void push(Elem element) {
        if (head == null) {
            head = element;
            tail = element;
        } else {
            element.setNext(head);
            head = element;
        }
    }

    public void pushTail(Elem element) {
        if (tail == null) {
            head = element;
            tail = element;
        } else {
            tail.setNext(element);
            tail = element;
        }
    }

    @Override
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

    public Elem popTail() {
        if (tail == null) {
            System.out.println("Хвост пуст");
            return null;
        } else {
            Elem poppedElement = tail;
            if (head == tail) {
                head = null;
                tail = null;
            } else {
                Elem current = head;
                while (current.getNext() != tail) {
                    current = current.getNext();
                }
                tail = current;
                tail.setNext(null);
            }
            return poppedElement;
        }
    }
}

