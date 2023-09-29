import java.lang.Math;

class Elem { 
	Node inf;
	Elem next;

	Elem( Node n ) { 
		inf = n;
	}

	public void print( ) { 
		inf.print( );
		if ( next != null ) {
			System.out.print( " -> " );
			next.print( );
		}
	}
}

class Node { 
	int inf;

	Node( int n ) { 
		this.inf = n;
	}

	public void print( ) { 
		System.out.print( inf );
	}
}

class Spis2 {
	Elem head;
	
	Spis2( ) {}

	public void push( Elem value ) { 
		if ( head == null ) { 
			head = value;
		} else {
			Elem n = head;
			
			//value.next = head;
			//head = value;

			while ( n.next != null ) { 
				n = n.next;
			}

			n.next = value;
		}
	};

	public void print( ) {
		if ( head != null ) {
			head.print( );
		}
	}

	public static void main( String[ ] args ) { 
		Spis2 v = new Spis2( );
		
		for ( int i = 0; i<2; i++ ) { 
			Node a = new Node( ( int )( Math.random( ) * 100 ) );
			Elem newval = new Elem( a );
			v.push( newval );
		}

		v.print( );
		System.out.println( );
	}
}
