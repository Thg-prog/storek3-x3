#include<iostream>
#include<string>
#include<array>

template<typename ...Args> // левая свертка
bool left_s( Args... args ) {
    return ( ... && args );
}

template<typename ...Args> // правая с вертка
bool right_s( Args... args ) {
    return ( args || ... );
}

template<typename ...Args> // левая свертка с инициализатором
int left_s_init( Args... args ) {
    return ( 0 + ... + args );
}

template<typename ...Args> // правая свертка с инициализатором
int right_s_init( Args... args ) {
    return ( args * ... * 1 );
}

template<typename ...Args> // // разворот в инициализации
auto initarr( Args... args ) {
    return std::array{ args... };
}

void processV() {}

template<typename T, typename ...Args> // разворот рекурсией
void processV( T f, Args... args ) {
    std::cout << f; 
    processV( args... );
}

template<typename T, std::size_t N>
void printArr( std::array<T, N> a ) {
    for ( int i = 0; i<a.size(); i++ ) {
        std::cout << a[ i ];
    }
}

template<typename... Ts, int... N>
void g(Ts (&...arr)[N]) {

}


template<typename T>
void Print( T a, T b ) {
    std::cout << a << " " << b << " ";
}

template<typename T1, typename T2, typename ...Us, typename ...Ts>
void Print( T1 f1, T2 f2, Us... a, Ts... b ) {
    std::cout << std::endl;
    std::cout << "A" << std::endl;
    Print( f1, f2 );
    Print( a..., );
}


using namespace std;
int main() {
    Print( 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 );
}