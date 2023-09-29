package lab2;
public class cl2 {
    public static int i = 0;
    public static double sum = 2;

    public static double mul( double sum2 ) {
        sum = sum * sum2;
        return sum;
    }

    public static void main( String[] args ) {
        if ( i < 4 ) {
            System.out.println( "cl2 started:" );
            i = i + 1;
            cl a = new cl();
            System.out.println( a.mul( sum ) );
            a.main( args );
        }
    }
}
