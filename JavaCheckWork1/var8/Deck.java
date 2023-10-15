package var8;
public class Deck extends Stack {
    private Elem tail;

    @Override
    public void push(Elem element){
        if (head == null) {
            head = element;
            tail = element;
        } else {
            element.next = head;
            head = element;
        }
    }

    public void pushTail(Elem element) {
        if (tail == null) {
            head = element;
            tail = element;
        } else {
            tail.next = element;
            tail = element;
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
                while (current.next != tail) {
                    current = current.next;
                }
                tail = current;
                tail.next = null;
            }
            return poppedElement;
        }
    }

}
