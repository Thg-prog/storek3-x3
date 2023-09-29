#include <iostream>
#include <cstring>
using namespace std;

class Elem {
    public:
        int x;
        Elem* next;
};

class Stack {
    public:
        Elem* head;
        Stack() { head = NULL; }; // Пустой стек.

        void print() { // Печатает стек.
            Elem* el = head;
            while ( el ) {
                cout << el->x << " ";
                el = el->next;
            }
            cout << endl;
        }

        void add( int x ); // Добавить в стек.

        bool isEmpty() { return head == NULL; }; // Пустой ли стек.

        int get();

        Elem* readHead() { return head; }; // Чтение из головы.
};

Elem* last( Elem* p ) {
    if ( p == NULL ) return NULL;
    Elem *q;
    q = p;
    while ( q->next != NULL ) {
        q = q->next;
    }

    return q;
}

Elem* preLast( Elem* p ) {
    if ( p == NULL ) return NULL;
    if ( p->next == NULL ) return NULL;
    Elem *q, *q1;
    q = p;
    q1 = q->next;
    while ( q1->next != NULL ) {
        q = q->next;
        q1 = q1->next;
    }

    return q;
}

void Stack::add( int x ) {
    Elem* el = new Elem;
    el->x = x;

    if ( head == NULL ) {
        el->next = head;
        head = el;
    } else {
        Elem* ls = last( head );
        el->next = NULL;
        ls->next = el;
    }
}

int Stack::get() {
    int a = 0;
    Elem* p = preLast( head );
    
    if ( p == NULL ) { 
        a = head->x;
        head = NULL;
        return a; 
    };

    a = p->next->x;
    delete( p->next );
    p->next = NULL;
    
    return a;
}

class my_pav {
    private:
        char* p;
    public:
        my_pav( char* s ) {
            cout << "Constructor" << endl;
            p = new char[ strlen( s ) + 1 ];
            strcpy( p, s );
        }
        
        void show() { cout << p << endl; }
        char* postfix();
        
};

char* my_pav::postfix() {
    int len = strlen( p );
    char* str = new char[ len + 1 ];
    char* tmp = new char[ len + 1 ];
    int istr = 0, itmp = 0;

    for ( int i = 0; i<len; i++ ) {
        if ( p[ i ] >= 'a' && p[ i ] <= 'z' ) {
            str[ istr++ ] = p[ i ]; 
        } else {
            if ( p[ i ] == ')' ) {
                str[ istr++ ] = tmp[ --itmp ];
            } else if ( p[ i ] != '(' ) {
                tmp[ itmp++ ] = p[ i ];
            }
        }
    }
    str[ istr ] = '\0';
    return str;
}

/*
int main() {
    Stack st;

    char* str = new char[ 128 ];
    cout << "Enter PAV" << endl;
    cin >> str;
    my_pav str1( str );
    str1.show();
    str = str1.postfix();
    cout << str << endl;

    int val;
    
    for ( int i = 0; i<strlen( str ); i++ ) {
        if ( str[ i ] >= 'a' && str[ i ] <= 'z' ) {
            cout << "Введите значение для " << str[ i ] << ": ";
            cin >> val;
            st.add( val );
        }

        if ( str[ i ] == '+' ) {
            val = st.get();
            st.add( st.get() + val );
            st.print();
        } else if ( str[ i ] == '-' ) {
            val = st.get();
            st.add( st.get() - val );
            st.print();
        } else if ( str[ i ] == '*' ) {
            val = st.get();
            st.add( st.get() * val );
            st.print();
        } else if ( str[ i ] == '/' ) {
            val = st.get();
            st.add( st.get() / val );
            st.print();
        }
    }

    return 0;
}
*/