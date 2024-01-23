package spisocs;

public class Node {
	String name;
	int year;
	float mark;
	Node(String name, int year, float mark) {
		this.name = name;
		this.year = year;
		this.mark = mark;
	}
	void print() {
		System.out.print(name + " " + year + " " + mark + "\n");
	}
}
