#include<iostream>
using namespace std;


struct mem {
    int key;
    int inf;
};

int N = 3;

struct analyze_t {
    int C = 0; // сравнения
    int P = 0; // перестановки
};

void print_massive( int* a, size_t n ) {
    for ( int i = 0; i<n; i++ ){
        cout << a[ i ] << " ";
    }
    cout << endl;
}

analyze_t sort_include( int* a, size_t n ) {
    analyze_t ret;

    int j;
    int x;

    for ( int i = 2; i <= n; i++ ) {
        x = a[ i ];
        a[ 0 ] = x;
        
        ret.P++;

        j = i - 1;
        while ( x < a[ j ] ) {
            a[ j + 1 ] = a[ j ];
            j = j - 1;

            ret.P++;
            ret.C++;
        }
        
        a[ j + 1 ] = x;
        ret.P++;
    }

    return ret;
}

void sort_haora( int* a, int left, int right, analyze_t& n2 ) {
    int x, w;
    int i = left;
    int j = right;
    x = a[ ( left + right ) / 2 ];

    do {
        while( a[ i ] < x ) {
            i++;
            n2.C++;
        }

        while( x < a[ j ] ) { 
            j--;
            n2.C++;
        }

        if ( i <= j ) {
            n2.C++;
            n2.P++;
            n2.P++;
            
            w = a[ i ];
            a[ i ] = a[ j ];
            a[ j ] = w;
            i++;
            j--;
        }
    } while ( i < j );
    if ( left < j ) {
        n2.C++;
        sort_haora( a, left, j, n2 );
    }

    if ( i < right ) {
        n2.C++;
        sort_haora( a, i, right, n2 );
    }
}

int main() {
    int* a = new int[ 11 ];
    int ind = 0;

    // 0 индекс барьер
    for ( auto i : { 0, -2, 2, 5, 3, -2, -1, 7, 8, 2, 6 } ) {
        a[ ind++ ] = i;
    }

    print_massive( a, 11 ); 
    analyze_t n = sort_include( a, 11 );
    cout << n.C << " " << n.P << endl;
    print_massive( a, 11 );

    ind = 0;
    for ( auto i : { 0, -2, 2, 5, 3, -2, -1, 7, 8, 2, 6 } ) {
        a[ ind++ ] = i;
    }

    print_massive( a, 11 );
    analyze_t n2;
    sort_haora( a, 0, 11, n2 );
    cout << n2.C << " " << n2.P << endl;
    print_massive( a, 11 );


    return 0;
}