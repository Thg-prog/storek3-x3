package lab2;
public class cl {
    public static int i = 0;
    public static double sum = 1;

    public static double mul( double sum2 ) {
        sum = sum * sum2;
        return sum;
    }

    public static void main( String[] args ) {
        if ( i < 4 ) {
            System.out.println( "cl started: " );
            i = i + 1;
            cl2 a = new cl2();
            System.out.println( a.mul( sum ) );
            a.main( args );
        }
    }
}
