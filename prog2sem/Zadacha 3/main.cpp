//№16
#include <iostream>
#include <math.h>
#include <fstream>

class Circle{
    private:
        int x, y, R;
    public:
        void setX(int x){this->x = x;}
        void setY(int y){this->y = y;}
        void setR(int R){this->R = abs(R);}
        Circle(int x, int y, int R);
        friend int checkPoints(Circle c1, Circle c2);    
};


Circle::Circle(int x, int y, int R){
    this->x = x;
    this->y = y;
    this->R = R;
}

int checkPoints(Circle c1, Circle c2){
    if(c1.R == c2.R && c2.x == c1.x && c1.y == c2.y)return -1;
    int d = sqrt(pow(c1.x - c2.x, 2) + pow(c1.y - c2.y,2));
    if((d == c1.R + c2.R) || (d == abs(c1.R-c2.R)))return 1;
    else if(d < c1.R + c2.R) return 2;
    else return 0;
}

int main(){
    std::fstream in;
    std::ofstream out;
    in.open("./CIRCLES.IN");
    out.open("./CIRCLES.OUT");
    int x, y, R;
    in >> x >> y >> R;
    Circle c1(x, y, R);
    in >> x >> y >> R;
    Circle c2(x, y, R);
    out << checkPoints(c1, c2);
    in.close();
    out.close();
}