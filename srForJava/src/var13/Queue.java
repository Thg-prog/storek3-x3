package var13;

import var8.Elem;

public class Queue extends ClassOD{
    @Override
    public void push(Elem element){
        super.pushTail(head);
    }
}
