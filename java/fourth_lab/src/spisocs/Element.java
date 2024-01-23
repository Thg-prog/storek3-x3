package spisocs;

public class Element {
	Node node;
	Element next;
	Element(Node _node) {
		node = _node;
		next = null;
	}

	void print() {
		node.print();
	}
}
