#include<math.h>
#include<iostream>
using namespace std;

struct coord_t {
    double x;
    double y;
};

struct coord_t2 {
    double x1;
    double y1;
    double x2;
    double y2;
};

class Model {
    private:
        coord_t c;
    public:
        Model();
        Model( double _x, double _y );

        double getX() const;
        double getY() const;
        
        void setX( double _x );
        void setY( double _y );
};

class Rect : public Model {
    private:
        double w;
        double h;
    public:
        Rect( double _x, double _y, double _w, double _h ) : Model( _x, _y ), w( _w <= 0 ? 1 : _w ), h( _h <= 0 ? 1 : _h ) {};
        Rect() : Rect( 0, 0, 1, 1 ) {};

        double getW() const;
        double getH() const;
        
        void setW( double _w );
        void setH( double _h ); 
};

class Circle : public Model {
    private:
        double r;
    public:
        Circle( double _x, double _y, double _r ) : Model( _x, _y ), r( _r <= 0 ? 1 : _r ) {};
        Circle() : Circle( 0, 0, 1 ) {};

        double getR() const; 

        void setR( double r );

        coord_t2 intersection( Circle a ) const;
        coord_t2 intersection( Rect a ) const;
};