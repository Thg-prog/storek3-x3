import java.util.Scanner;

class Spis {
	int[ ] Node;
	Spis Elem;
	
	Spis( ) {}

	Spis( int[ ] value ) { 
		this.Node = value;
		this.Elem = new Spis();
	};

	public void push( int[ ] value ) { 
		if ( this.Elem == null ) {
			this.Node = value;
			this.Elem = new Spis();
		} else { 
			this.Elem.push( value );	
		}
	};

	public void print( ) {
		System.out.print( "{ " );
		if ( this.Node != null ) {
			for ( int i = 0; i < this.Node.length; i++ ) {
				System.out.print( this.Node[ i ] + " " );
			}
		}
		System.out.print( "}" );

		if ( this.Elem != null ) {
			System.out.print( " -> " );
			this.Elem.print( );
		}
	}

	public static int[ ] addm( int n ) { 
		int[ ] arr = new int[ n ];
		Scanner in = new Scanner( System.in );
		for ( int i = 0; i<n; i++ ) { 
			arr[ i ] = in.nextInt( );
		}

		return arr;
	}
	
	public static void main( String[ ] args ) { 
		Scanner in = new Scanner( System.in );
		Spis a = new Spis( );
		String n = "";
		while ( !n.equals( "q" ) ) {
			n = in.nextLine( );
			a.push( addm( Integer.parseInt( n ) ) );
			a.print( );
			System.out.println( );
		}
	}
}
