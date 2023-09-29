#include<math.h>
#include<iostream>
#include "p2.h"

using namespace std;
// 16

Model::Model( double _x, double _y ) {
    c.x = _x;
    c.y = _y;
}

double Model::getX() const {
    return c.x;
}

double Model::getY() const {
    return c.y;
}

void Model::setX( double _x ) {
    c.x = _x;
}

void Model::setY( double _y ) {
    c.y = _y;
}

double Rect::getW() const {
    return w;
}

double Rect::getH() const {
    return h;
}

void Rect::setW( double _w ) {
    w = _w;
}
void Rect::setH( double _h ) {
    h = _h;
}

double Circle::getR() const {
    return r;
}

void Circle::setR( double _r ) {
    r = ( _r <= 0 ? 1 : _r );
}

coord_t2 Circle::intersection( Rect a ) const {
    coord_t2 a4;
    double dx = max( a.getX(), min( getX(), a.getW() + a.getX() ) );
    double dy = max( a.getY(), min( getY(), a.getH() + a.getY() ) );

    if ( ( dx * dx + dy * dy ) <= ( r * r ) ) {
        double d = sqrt( r * r - dy * dy );
        a4.x1 = getX() - d;
        a4.x2 = getX() + d;
        a4.y1 = getY() - dy;
        a4.y2 = getY() + dy;
    } else {
        a4.x1 = a4.x2 = a4.y1 = a4.y2 = 0;
    }

    return a4;
}

coord_t2 Circle::intersection( Circle a ) const {
    double x1 = getX();
    double y1 = getY();

    double x2 = a.getX();
    double y2 = a.getY();

    double r1 = getR();
    double r2 = a.getR();
    
    double d = sqrt( pow( x2-x1, 2 ) + pow( y2-y1, 2 ) );

    if ( d > r1 + r2 ) {
        return coord_t2( 0, 0, 0, 0 );
    } else if ( d < abs( r1 - r2 ) ) {
        return coord_t2( 0, 0, 0, 0 );
    } else if ( d == 0 && r1 == r2 ) {
        return coord_t2( 0, 0, 0, 0 ); 
    } else {
        double q = ( pow( r1, 2 ) - pow( r2, 2 ) + pow( d, 2 ) ) / ( 2 * d );
        double h = sqrt( pow( r1, 2 ) - pow( q, 2 ) );

        coord_t a2;
        a2.x = x1 + q * ( x2 - x1 ) / d;
        a2.y = y2 + q * ( y2 - y1 ) / d;

        coord_t a3;
        a3.x = a2.x + h * ( y2 - y1 ) / d;
        a3.y = a2.y - h * ( x2 - x1 ) / d;

        coord_t2 a4;

        a4.x1 = a3.x;
        a4.y1 = a3.y;

        a4.x2 = a2.x - h * ( y2 - y1 ) / d;
        a4.y2 = a2.y + h * ( x2 - x1 ) / d;

        return a4;
    }
}



int main() {
    Circle a;
    Circle b = Circle( 1, 1, 2 );

    coord_t2 c = a.intersection( b );
    cout << c.x1 << " " << c.y1 << endl;
    cout << c.x2 << " " << c.y2 << endl;

    Rect v = Rect( 0, 0.5, 0.5, 1.9 );
    coord_t2 d = b.intersection( v );
    cout << d.x1 << " " << d.y1 << endl;
    cout << d.x2 << " " << d.y2 << endl;

    return 0;
}