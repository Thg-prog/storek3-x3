package third_lab;
import java.util.Scanner;


public class One_N {
	private int n;
	private int count;
	
	One_N(int n) {
		this.n = n;
		count = 0;
	}
	
	private boolean yes_no(int number) {
		int buf = number;
		while (buf > 0) {
			int digit = buf % 10;
			if (digit == 0 || number % digit != 0) {
				return false;
			}
			buf /= 10;
		}
		return true;
	}
	
	private int get_number_len(int number) {
		int len = 0;
		int buf = number;
		while (buf > 0) {
			len++;
			buf /= 10;
		}
		return len;
	}
	
	void run() {
		int len_of_n = get_number_len(n);
		for (int i = 1; i <= n; i++) {
			if (yes_no(i)) {
				count++;
				int len_of_number = get_number_len(i);
				if (count % 8 == 1) {
					len_of_number++;
				}
				for (int j = 0; j < len_of_n - len_of_number + 1; j++) {
					System.out.print(" ");
				}
				System.out.print(i);
				if (count % 8 == 0) {
					System.out.println();
				}
			}
		}
		System.out.println();
		System.out.print("Количество найденых чисел: " + count);
	}
	
	public static void main(String args[]) {
		System.out.print("Введите число: ");
		Scanner in = new Scanner(System.in);
		int n = in.nextInt();
		One_N obj = new One_N(n);
		obj.run();
	}
}
