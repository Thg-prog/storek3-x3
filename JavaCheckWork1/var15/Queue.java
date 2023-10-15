package var15;

import var8.Elem;

public class Queue extends Deck{
    @Override
    public void push(Elem element){
        super.pushTail(element);
    }
}
