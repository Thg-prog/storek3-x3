import var9.Deck;
import var9.Queue;
import var9.Stack;
import var8.Elem;

public class Main {
    public static void main(String[] args){
        Stack stack = new Stack();

        
        stack.push(new Elem(2));
        stack.push(new Elem(3));
        stack.push(new Elem(4));
        stack.push(new Elem(5));
        System.out.println(stack);

        stack.pop();
        stack.pop();
        System.out.println(stack);

        System.out.println();


        Queue queue = new Queue();

        queue.push(new Elem(1));
        queue.push(new Elem(2));
        queue.push(new Elem(3));
        queue.push(new Elem(4));
        queue.push(new Elem(5));
        System.out.println(queue);

        queue.pop();
        queue.pop();
        System.out.println(queue);

        System.out.println();


        Deck dack = new Deck();

        dack.push(new Elem(1));
        dack.push(new Elem(2));
        //dack.pushTail(new Elem(3));
        //dack.pushTail(new Elem(4));
        System.out.println(dack);

        dack.pop();
        dack.popTail();
        System.out.println(dack);
    }
}
