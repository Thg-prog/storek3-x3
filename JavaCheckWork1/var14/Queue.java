package var14;

import var8.Elem;

public class Queue extends Spis{
    public Elem tail;
    public void pushTail(Elem element){
        if (tail == null) {
            head = element;
            tail = element;
        } else {
            tail.next = element;
            tail = element;
        }
    }
    protected void pushHead(Elem element){
        if (head == null) {
            head = element;
            tail = element;
        } else {
            element.next = head;
            head = element;
        }
    }
}
