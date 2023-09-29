#include <iostream>
#include <cmath>


const double pi = 3.1415926535;
const double eps = 1e-6;
//const double bern[21] = {1,(-1./2.), (1./6.), 0, -1./30., 0, 1./42., 0, -1./30., 0, 5./66., 0, -691./2730., 0 , 7./6., 0, -3617./510., 0, 43867./798., 0, -174611./330.};


std::pair<double, int> sinus(double x){

    /*while (fabs(x) >= 2 * pi) {
        x -= znak(x) * 2 * pi;
    }*/

    x = fmod(x, 2*pi);

    
    if(x > pi){
        x -= pi;
        x *= -1;
    }
    //x = -(x - pi); // if x > pi x -= pi; x*=-1
    if(x > pi/2)x = pi - x;

    int itter = 0;
    
    double t = x, s = x;

    for(int n = 1; fabs(t) > eps; n++){
        itter ++;
        t = -t * pow(x, 2)/(2*n*(2*n+1));
        s += t;
    }
    
    return std::pair<double, int>(s, itter);
}


std::pair<double, int> cosinus(double x){
    /*while (fabs(x) >= 2 * pi) {
        x -= znak(x) * 2 * pi;
    }*/

    x = fmod(x, 2*pi);

    if(x > pi){
        x -= pi;
    }

    if(x > pi/2)x = pi - x;

    //if(x > 3*pi / 2){
    //    x -= 2*pi;
    //}

    int itter = 0;

    double t = 1, s = 1;

    for (int n = 1; fabs(t) > eps; n++) {
        itter++;
        t = -t * pow(x, 2)/(2*n*(2*n-1));
        s += t;
    }
    return std::pair<double, int>(round(s*1000000)/1000000, itter);
}

/*std::pair<double, int> arctg(double x){
    //while (fabs(x) >= pi / 2) {
    //    x -= znak(x) * pi / 2;
    //}
    //x = fmod(x, pi);

    int itter = 0;

    double t = x, s = x;

    for (int n = 1; fabs(t) > eps; n++) {
        itter++;
        t = -t * ((pow(x,2)*(2 * n - 1))/(2 * n + 1));
        s += t;
    }
    return std::pair<double, int>(s, itter);
}*/

/*double tangens(double x){
    while (fabs(x) >= pi) {
        x -= znak(x) * pi;
    }
    std::cout << x << std::endl;
    double t = x, s = x;
    for(int n = 2; fabs(t) > eps; n++){
        t *= -(bern[2*n]*4*(1-pow(4, n)) * pow(x, 2))/(bern[2*n-2]*(1-pow(4, n-1))*(2*n-1)*(2*n));
        s += t;
    }
    return s;
    //return sinus(x)/cosinus(x);
}*/


std::pair<double, int> expn(double x){
    double s = 1 + x, t = 1 + x;
    int count = 0;
    for(int i = 2; fabs(t) > eps; i++){
        t *= t * (x / i);
        s += t;
        count++;
    }
    return std::pair<double, int>(s, count);
}


int main(int argc, char** argv){//sin(x)(x^2*20)-(10/x)(e^(cos(x)))
    double x = 0;
    std::cout << "X input" << std::endl;
    std::cin >> x;
    /*int maxsin = 0;
    int maxcos = 0;
    int maxexp = 0;
    int countsin, countcos, countexp;
    for(double x = 0; x < 100000000; x+=1){
        std::pair<double, int> sinuss = sinus(x);
        std::pair<double, int> cossinus = cosinus(x);
        std::pair<double, int> exxpn = expn(cossinus.first);
        double answer = sinuss.first*pow(x, 2)*20.0 - (10.0/x)*(exxpn.first);
        std::cout << cossinus.first << " " << x << std::endl;
        if(sinuss.second > maxsin)maxsin = sinuss.second;
        if(cossinus.second > maxcos)maxcos = cossinus.second;
        if(cossinus.second > 10)std::cout << x << " " << cossinus.second << std::endl;
        if(exxpn.second > maxexp)maxexp = exxpn.second;
    }*/
    
    std::pair<double, int> sinuss = sinus(x);
    std::pair<double, int> cossinus = cosinus(x);
    std::pair<double, int> exxpn = expn(cossinus.first);
    double answer = sinuss.first*pow(x, 2)*20.0 - (10.0/x)*(exxpn.first);

    //std::cout << "Maxsin " << maxsin << " Maxcos" << maxcos << " " << maxexp;
    std::cout << "Sinus itteration " << sinuss.second << std::endl;
    std::cout << "Cosinus itteration " << cossinus.second << std::endl;
    std::cout << "Exp itterations " << exxpn.second << std::endl;
    std::cout << "Answer " << answer << std::endl;
}




/*
 double t = x, s = x;

    for(int n = 3; fabs(t) > eps; n += 2)
        s += t = -t*pow(x,2)/n/(n-1);
*/