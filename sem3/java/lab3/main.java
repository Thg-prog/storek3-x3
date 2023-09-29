import java.util.Scanner;

class One_n {
    int n;
    One_n( int n ) {
        this.n = n;
    }

    int run() {
        int count = 0;
        for ( int i = 1; i<n; i++ ) {
            if ( yes_no( i ) ) {
                count++;      

                System.out.print( String.format( "%6s", i ) );
                if ( count % 8 == 0 ) {      
                    System.out.println();   
                }
            }
        }

        System.out.println();

        return count;
    }

    boolean yes_no( int a ) {
        int d = a;
        if ( d > 9 ) {
            if ( d % 10 == 0 ) {
                return false;
            }

            while ( d > 0 ) {
                if ( d % 10 == 0 || a % ( d % 10 ) != 0 ) {
                    return false;
                }
                
                d /= 10;
            }

            return true;
        } else {
            return true;
        }
    }

    public static void main( String[] args ) {
        int n;
        Scanner in = new Scanner( System.in );
        n = in.nextInt();
        One_n obj = new One_n( n );
        int count = obj.run();
        System.out.println( "count = " + count );
    }
}
