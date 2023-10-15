package var12;

import var8.Elem;

public class Stack {
    Elem head;


    public Stack() {
        this.head = null;
    }

 
    public void push(Elem el) {
        if (el != null) {
            el.next = head;
            head = el;
        }
    }

    public Elem pop() {
        if (head == null) {
            return null;
        } else {
            Elem top = head;
            head = top.next;
            top.next = null;
            return top;
        }
    }

    public String toString()
    {
        StringBuilder value = new StringBuilder();
        Elem tmp = this.head;
        while (tmp != null) {
            value.append(tmp.value).append(" ");
            tmp = tmp.next;
        }
        return value.toString();
    }
}
