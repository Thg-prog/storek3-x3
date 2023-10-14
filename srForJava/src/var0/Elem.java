package var0;

public class Elem {
    private int value;
    private Elem next;

    public Elem(int value) {
        this.value = value;
        this.next = null;
    }

    public int getValue() {
        return value;
    }

    public Elem getNext() {
        return next;
    }

    public void setNext(Elem next) {
        this.next = next;
    }
}
