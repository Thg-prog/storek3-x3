#include<iostream>
#include<iomanip>
#include <functional>
using namespace std;

struct list;
typedef list* plist;
struct list {
    int r;
    plist next;
    double val;

    plist level;
    char atom;
};

char* str = new char[ 100 ];
list* p;

void input_to_list( plist &p ) {
    char c;
    c = str[ 0 ];
    str = str + 1;

    if ( c != 0 ) {        
        if ( c == '(' ) {
            p = new list;
            p->r = 0;
            input_to_list( p->level );
            input_to_list( p->next );
        } else if ( ( ( 'a' <= c ) && ( c <= 'z' ) ) || ( c == '+' ) || ( c == '-' ) || ( c == '*' ) || ( c == '/' ) ) {
            p = new list;
            p->r = ( ( ( 'a' <= c ) && ( c <= 'z' ) ) ? 2 : 1 );
            p->atom = c;
            input_to_list( p->next );
        } else if ( c == ')' ) {
            p = NULL;
        }
    } else {
        p = NULL;
    }
}

void print_of_list( plist p ) {
    list* q;
    if ( p != NULL ) {
        if ( p->r >= 1 ) {
            cout << p->atom;
        } else {
            cout << '(';
            q = p->level;
            while ( q != NULL ) {
                print_of_list( q );
                q = q->next;
            }
            cout << ')';
        }
    }
}

void printz( plist p ) {
    list* q = p->level;
    while ( q != NULL ) {
        cout << q->atom;
        printz( q );
        q = q->next;
    }
}

void init_values( plist p ) {
    list* q;
    if ( p != NULL ) {
        if ( p->r >= 2 ) {
            cout << "Введите число для " << p->atom << ": ";
            cin >> p->val;
        } else if ( p->r == 0 ) {
            q = p->level;
            while ( q != NULL ) {
                init_values( q );
                q = q->next;
            }
        }
    }
}

plist gethead( plist p ) {
    plist q = p->level;
    p->level = q->next;
    q->next = NULL;

    return q;
}

double val( plist p ) {
    if ( p != NULL ) {
        if ( p->level != NULL ) {
            double x = val( gethead( p ) );
            char oper = gethead( p )->atom;
            double y = val( gethead( p ) );

            if ( oper == '+' ) {
                return x + y;
            } else if ( oper == '-' ) {
                return x - y;
            } else if ( oper == '*' ) {
                return x * y;
            } else if ( oper == '/' ) {
                return x / y;
            }

        } else {
            return p->val;
        }
    }

    return 0;
}

/*
int main() {
    int act = -1;
    while ( act != 0 ) {
        cout << ""
    }

    list* p;
    cin >> str;
    input_to_list( p );

    init_values( p );
    print_of_list( p );
    cout << endl;
    cout << val( p ) << endl;
}
*/

#include "userint.cpp"
int main() {
    
    Dictionary<std::string, std::function<void(void)>> usr;
    usr.add( "Текст в лист", []() { 
        cin >> str;
        input_to_list( p );
    } );

    usr.add( "Принт листа", []() {
        print_of_list( p );
        cout << endl;
    } );

    usr.add( "Принт записи", []() {
        printz( p );
        cout << endl;
    } );

    usr.add( "Ввод переменных и результат", []() {
        init_values( p );
        cout << val( p ) << endl;
    } );
    
    userinterface( usr );
    return 0;
}