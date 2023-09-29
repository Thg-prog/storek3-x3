#include <iostream>
using namespace std;
#include "p1.h"

// 18

Cell::Cell( coord_t c ) : Cell( c.x, c.y ) {};

Cell::Cell( int x, int y ) {
    Pos.x = x;
    Pos.y = y;
}; 

Cell::Cell( const Cell& cell ) = default;
Cell::Cell( Cell&& cell ) = default;

int Cell::getX() const {
    return Pos.x;
}

int Cell::getY() const {
    return Pos.y;
} 

void Cell::setX( int _x ) {
    Pos.x = _x;
}

void Cell::setY( int _y ) {
    Pos.y = _y;
}

bool Cell::isAlive() const {
    return Alive;
}

void Cell::setAlive( bool _alive ) {
    Alive = _alive;
}

void Cell::setGen( int _gen ) {
    Gen = _gen;
}

int Cell::getGen() const {
    return Gen;
}

Cell& Cell::operator= ( const Cell& cell ) {
    if ( this != &cell ) {
        setX( cell.getX() );
        setY( cell.getY() );
        setAlive( cell.isAlive() );
        setGen( cell.getGen() );
    }

    return *this;
}

Universe::Universe() : Universe( 0, 0, 0 ) {};

Universe::Universe( int _M, int _N, int _P ) : M( _M ), N( _N ), P( _P ) {
    cells = new Cell[ _P ];
}

Universe::Universe( int _M, int _N, int _P, coord_t* XY ) : Universe( _M, _N, _P ) {
    for ( int i = 0; i<P; i++ ) {
        cells[ i ].setX( XY[ i ].x );
        cells[ i ].setY( XY[ i ].y );
    }
}

Universe::Universe( const Universe& univ ) : M( univ.getM() ), N( univ.getN() ), P( univ.getP() ) {
    cells = new Cell[ P ];
    Cell* unc = univ.cells;
    copy( unc, unc+univ.P, cells );
}

Universe::Universe( Universe&& univ ) : M( univ.getM() ), N( univ.getN() ), P( univ.getP() ) {
    Cell* _cells = univ.cells;
    copy( _cells, _cells+P, cells );
}

Universe::~Universe() {
    delete[] cells;
}

int Universe::getM() const {
    return M;
}

int Universe::getN() const {
    return N;
}

int Universe::getP() const {
    return P;
} 

void Universe::dist_cells() {
    for ( int i = 0; i<P; i++ ) {
        cout << "[" << i << "] X & Y: ";
        int x = -1;
        int y = -1;
        while ( x < 0 || x > M && y < 0 || y > N ) {
            cin >> x >> y;
        }

        cells[ i ].setX( x );
        cells[ i ].setY( y );
    }
}

std::ostream& operator<< ( std::ostream &out, const Universe &univ ) {
    for ( int i = 0; i<univ.M; i++ ) {
        for ( int j = 0; j<univ.N; j++ ) {
            Cell* tmp_cell = univ.getcell( i, j );
            if ( tmp_cell != NULL ) {
                out << ( tmp_cell->isAlive() ? "[*]" : "[.]" );   
            } else {
                out << "[ ]";
            }
        }
        
        out << endl;
    }

    return out;
};

void Universe::new_generation() {
    for ( int i = 0; i<P; i++ ) {
        Cell* tmp_cell = &cells[ i ];
        if ( tmp_cell != NULL ) {
            int n_cells = find_in_circle( tmp_cell );
            if ( ( n_cells < 2 || n_cells > 3 ) && G != tmp_cell->getGen() ) {
                tmp_cell->setAlive( false );
            } else if ( n_cells == 3 ) {
                if ( !tmp_cell->isAlive() ) {
                    tmp_cell->setAlive( true );
                    // tmp_cell->setGen( G );
                } else {
                    Cell newCell = Cell( nearest_coord_cell( tmp_cell ) );
                    newCell.setGen( G );
                    new_generation_mem();
                    cells[ P - 1 ] = newCell;
                }
            }
        }
    }

    G++;
}

Universe Universe::new_generation() const {
    Universe C;
    C = *this;
    C.new_generation();

    return C;
}

void Universe::new_generation_mem() {
    Cell* new_gen = new Cell[ P + 1 ];
    copy( cells, cells+P, new_gen );

    delete[] cells;
    cells = new_gen;
    P = P + 1;
}

Cell* Universe::getcell( int X, int Y ) const {
    for ( int k = 0; k<P; k++ ) {
        if ( cells[ k ].getX() == X && cells[ k ].getY() == Y ) {
            return &cells[ k ];
        }  
    }

    return NULL;
}

int Universe::find_in_circle( Cell* cell ) const {
    int num = 0;
    
    int x = cell->getX();
    int y = cell->getY();

    for ( int i = x - 1; i<x + 2; i++ ) {
        for ( int j = y - 1; j<y + 2; j++ ) {
            Cell* tmp_cell = getcell( i, j );
            if ( tmp_cell != NULL && tmp_cell != cell && tmp_cell->isAlive() ) {
                num++;
            }
        }
    }

    return num;
}

Cell Universe::newgenCell( coord_t xy ){
    Cell newCell( xy.x, xy.y );
    newCell.setGen( G );
    return newCell;
}

coord_t Universe::nearest_coord_cell( Cell* cell ) const {
    coord_t new_coord;
    int x = cell->getX();
    int y = cell->getY();

    while ( getcell( x, y ) != NULL ) {
        x++;

        if ( x == M ) {
            if ( y == N ) {
                break;
            }

            x = 0;
            y++;
        }

    }
    
    new_coord.x = x;
    new_coord.y = y;

    return new_coord;
}

Universe& Universe::operator= ( const Universe& other ) {
    if ( this != &other ) {
        M = other.getM();
        N = other.getN();
        P = other.getP();

        delete[] cells;
        cells = new Cell[ P ];
        copy( other.cells, other.cells+other.P, cells );
    }
    
    return *this;
}

int main() {
    int M, N, P, G;
    cin >> M >> N >> P;
    coord_t* XY = new coord_t[ P ];

    for ( int i = 0; i<P; i++ ) {
        cout << "[" << i << "] X & Y: ";
        int x = -1;
        int y = -1;
        while ( x < 0 || x > M && y < 0 || y > N ) {
            cin >> x >> y;
            cout << "X" << endl;
        }

        XY[ i ].x = x;
        XY[ i ].y = y;
    }

    Universe a( M, N, P, XY );
    cout << a;

    Universe b = a;

    for ( int i = 0; i<5; i++ ) {
        cout << endl;
        b.new_generation();
        cout << b;
    }

    cout << endl;
    cout << a;

    return 0;
}