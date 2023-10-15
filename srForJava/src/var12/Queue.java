package var12;

import var8.Elem;

public class Queue extends ClassOD{
    @Override
    public void push(Elem element){
        super.pushTail(element);
    }
}
