package second_lab;

public class Class1 {
	static int count;
	
	public static void main(String args[]) {
		System.out.println(count + ": ");
		System.out.println("I am main() from Class1");
		for (int i = 0; i < args.length; i++) {
			System.out.println(args[i] + " ");
		}
		System.out.println('\n');
		if (count < 5) {
			count++;
			Class2.main(args);
		}
	}
}
