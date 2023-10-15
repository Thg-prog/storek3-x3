package var10;

import var8.Elem;

public class Queue extends Stack{
    public Elem tail;

    public Queue() {
        super();
        this.tail = null;
    }

    @Override
    public void push(Elem element){
        if (tail == null) {
            head = element;
            tail = element;
        } else {
            tail.next = element;
            tail = element;
        }
    }

    public void pushHead(Elem element){
        if (head == null) {
            head = element;
            tail = element;
        } else {
            element.next = head;
            head = element;
        }
    }
}
