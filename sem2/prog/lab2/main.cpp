#include "time_lib.cpp"

int main( int argc, char *argv[] ) {
    DateTime a;
    a.addSecs( 1000000000 );
    DateTime b = DateTime( 1900, 10, 3, 3, 3, 20 );

    DateTime c;

    DateTime d = c.fromString( "2022 22 32 12", "Y H M S" );
    std::cout << d.format( "Y H M S" ) << std::endl;
    
    return 0;
}