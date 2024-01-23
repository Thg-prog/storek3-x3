package spisocs;

import java.util.Scanner;
import java.io.File;
import java.io.FileNotFoundException;

class List {
	Element head;
	public List() {
		head = null;
	}
	
	public void push(Element el) {
		if (head != null) {
			Element el1 = head;
			Element el2 = head;
			Boolean isAdded = false;
			int c = 0;
			while (el1 != null) {
				if (el.node.name.compareTo(el1.node.name) < 0) {
					if (c == 0) {
						el.next = head;
						head = el;
					} else {
						el.next = el2.next;
						el2.next = el;
					}
					isAdded = true;
					break;
				} else {
					el2 = el1;
					el1 = el1.next;
				}
				c++;
			}
			if (!isAdded) {
				Element el3 = head;
				while (el3 != null) {
					if (el.node.name.compareTo(el3.node.name) >= 0 && el3.next != null) {
						el3 = el3.next;
					} else {
						el3.next = el;
						break;
					}
				}
			}
		} else {
			el.next = head;
			head = el;
		}
	}
	
//	public void init(int count) {
//		for (int i = 0; i < count; i++) {
//			int value = (int)(Math.random() * 100);
//			push(value);
//		}
//	}
	
	public void print() {
		Element el = head;
		while (el != null) {
			el.print();
			el = el.next;
		}
	}
	
//	public int get_length() {
//		int count = 0;
//		Element element = head;
//		while (element != null) {
//			element = element.next;
//			count++;
//		}
//		return count;
//	}
//	
//	public boolean isEmpty() {
//		return head == null;
//	}
	
	
	public static void main(String[] args) {
		List list = new List();
		try {
			File file = new File("src/spisocs/stud.txt");
			Scanner scanner = new Scanner(file);
			while (scanner.hasNext()) {
				String name = scanner.next();
				int year = Integer.parseInt(scanner.next());
				float mark = Float.parseFloat(scanner.next());
				Node node = new Node(name, year, mark);
				Element el = new Element(node);
				list.push(el);
			}
			scanner.close();
			list.print();
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
	}
}
