#include "bitset.cpp"

int main() {
    // bitSet a( 1 );
    bitSet b( 10 );
    bitSet c( 100 );
    bitSet d( 0b101010 );

    cout << b << " " << c << endl;

    // b = c << 2;

    // cout << (bitSet<8>)d << " " << c << endl;
    // cout << ( a | b ) << endl;
    // cout << a.size() << " " << b.size() << endl;
    
    /*
    bitSet<4> a1( "0011" );
    cout << a1 << endl;

    bitSet<4> a2( "1100" );
    cout << a2 << endl;

    cout << a1.size() << endl;
    cout << a1.all() << " " << a1.any() << " " << a1.nope() << endl;
    cout << ( a1 << 1 ) << endl;
    cout << ( a1 & a2 ) << " " << ( a1 | a2 ) << " " << ( a1 ^ a2 ) << endl;
    cout << ( a1 == a2 ) << endl;
    cout << ( ~a1 == a2 ) << endl;
*/
    return 0;
}