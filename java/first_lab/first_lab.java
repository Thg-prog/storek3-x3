class Test {
    public static void main(String args[]) {
    	System.out.println("Привет!");
    	Test test = new Test();
    	if (args.length != 0) {
            test.print(args);
        }
    }
    void print(String args[]) {
    	for (int i = 0; i < args.length; i++) {
    	    System.out.print(args[i] + " ");
    	}
    	System.out.println();
    }
}vim 
