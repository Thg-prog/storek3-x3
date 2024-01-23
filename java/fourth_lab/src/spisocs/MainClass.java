package spisocs;
import java.util.Scanner;

public class MainClass {
	public static void main(String[] args) {
		List[] mas = new List[12];
		for (int i = 0; i < mas.length; i++) {
			if (i % 3 == 0) mas[i] = new Stack();
			else if (i % 3 == 1) mas[i] = new Deque();
			else mas[i] = new Queue();
		}
		for (int j = 0; j < 20; j++) {
			for (int i = 0; i < mas.length; i++) {
				int value = j;//(int)(Math.random()*100);
				if (mas[i].getClass().getName().equals("spisocs.Deque") && j % 2 == 0) ((Deque)mas[i]).push_start(value);
				else mas[i].push(value);
			}
		}
		for (int i = 0; i < mas.length; i++) {
			System.out.print(mas[i].getClass().getName() + ": ");
			mas[i].print();
			System.out.println();
		}
	}
}
