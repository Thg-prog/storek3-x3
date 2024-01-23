package spisocs;

import java.util.Scanner;

public class Deque extends List {
	public Element tail;
	public Deque() {
		tail = null;
	}
	
	public void push(Element value) {
		int len = get_length();
		super.push(value);
		if (len == 0) {
			Element el = head;
			tail = el;
		}
	}
	
	public void push_start(Element el) {
		if (head == null) {
            el.next = head;
            head = el;
			tail = el;
		} else {
			Element el1 = tail;
			el1.next = el;
			tail = el1.next;
		}
	}
	
//	private Element get_predlast_el() {
//		Element el = head;
//		Element el1 = head;
//		Element el2 = head;
//		while (el != null) {
//			el2 = el1;
//			el1 = el;
//			el = el.next;
//		}
//		return el2;
//	}
//	
//	public Element pop_start() {
//		Element el1 = tail;
//		if (get_length() == 1) {
//			tail = null;
//			head = null;
//		} else {
//			Element el2 = get_predlast_el();
//			el2.next = null;
//			tail = el2;
//		}
//		return el1;
//	}
//	
//	public Element check_pop_start() {
//		return tail;
//	}
	
}