package var12;

import var8.Elem;

public class ClassOD extends Stack {
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
}
