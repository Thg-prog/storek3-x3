#include "userint.cpp"
#include<iostream>
#include<iomanip>
#include<vector>

using namespace std;

struct Elem {
    int inf;
    Elem* left;
    Elem* right;
};

void add( int x, Elem* &r ) {
    if ( r == NULL || r->inf == 0 ) {
        r = new Elem;
        r->inf = x;
        r->left = NULL;
        r->right = NULL;
    } else {
        if ( x<r->inf ) {
            add( x, r->left );
        } else {
            add( x, r->right );
        } 
    }
}

Elem* find( int x, Elem* r, int& i ) {
    i++;
    if ( r != NULL ) {
        if ( x < r->inf ) {
            r = find( x, r->left, i );
        } else if ( x > r->inf ) {
            r = find( x, r->right, i );
        }

        return r;
    }

    return NULL;
}

void print_sort( Elem* r, int& i ) {
    if ( r != NULL ) {
        int j = i + 1;
        i++;
        print_sort( r->right, j );
        cout << r->inf << " " << i << endl;
        print_sort( r->left, j );
    }
}

Elem* a;

void m1() {
    int x;
    cin >> x;
    add( x, a );
}

void m2() {
    int x;
    int i = 0;
    cin >> x;
    cout << find( x, a, i );
}

void m3() {
    int i = 0;
    print_sort( a, i );
}

int main() {
    Dictionary<std::string, void*> usr;
    usr.add( "Добавить", ( void* )m1 );
    usr.add( "Найти", ( void* )m2 );
    usr.add( "Запринтить", ( void* )m3 );

    userinterface( usr );

    
    return 0;
}
