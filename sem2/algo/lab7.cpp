#include<iostream>
#include<iomanip>
#include<vector>
using namespace std;

//struct Tree;

struct Tree {
    char root;
    Tree* left;
    Tree* right;
};

struct list;
typedef list* plist;
struct list {
    int r;
    plist next;
    plist level;
    char atom;
};

char* str = new char[ 100 ];
Tree* a;
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
            p->r = 1;
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
        if ( p->r == 1 ) {
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

plist getHead( plist p ) {
    plist q = p->level;
    p->level = q->next;
    q->next = NULL;

    return q;
}



Tree* construct( Tree* p1, char i, Tree* p2 ) {
    Tree* p = new Tree;
    p->root = i;
    p->left = p2;
    p->right = p1;
    return p;
}

Tree* listToTree( auto x ) {
    Tree* y;

    if ( x->atom ) {
        y = new Tree;
        y->root = x->atom;
    } else {
        y = construct( listToTree( getHead( x ) ), getHead( x )->atom, listToTree( getHead( x ) ) );
    }

    return y;
}

bool isempty( Tree* x ) {
    if ( x->left == NULL && x->right == NULL ) {
        return true;
    }

    return false;
}

bool isroot( Tree* x ) {
   return false;
}

void print_tree( Tree* q ) {
    if ( q != NULL ) { 
        if ( !( ( 'a' <= q->root ) && ( q->root <= 'z' ) ) ) {
            cout << '(';
        }

        print_tree( q->left );
        cout << q->root;
        print_tree( q->right );

        if ( !( ( 'a' <= q->root ) && ( q->root <= 'z' ) ) ) {
            cout << ')';
        }
    }
}

void count_tree( int& i, int co=0, int co2=0 ) {
    char c = str[ i ];
    if ( c == '(' ) {
        co++;
    } else if ( c == '+' || c == '-' || c == '*' || c == '/' ) {
        co2++;
    }

    if ( co >= co2 ) {
        i++;
        count_tree( i, co, co2 );
    }
}

// ((a+b)*c)
void construct_tree( int& i, Tree*& x ) {
    char c = str[ i ];
    i++;

    int j = i;

    count_tree( j );
    if ( c == '(' ) {        
        x = new Tree;
        x->root = str[ j ];
        construct_tree( i, x->left );
        j++;
        construct_tree( j, x->right );
    } else {
        x = new Tree;
        x->root = c;
    }
    
}

list* treeToList( Tree* root, list* head, int i = 0 ) {
    if ( !root ) {
        return NULL;
    }

    treeToList( root->left, head, i );
    list* node = new list;
    node->atom = root->root;

    if ( node->atom ) {
        node->r = 1;
    } else {
        node->r = 0;
    }

    cout << root->root << " " << node->r << endl;

    node->next = head;
    treeToList( root->right, head, i );

    return head;
}

void m1() {
    cout << "Введите текст: ";
    cin >> str;
    int i = 0;
    construct_tree( i, a );
}

void m1_1() {
    cout << "Введите текст: ";
    cin >> str;
    input_to_list( p );
}

void m2() {
    print_tree( a );
    cout << endl;
}

void m2_2() {
    print_of_list( p );
    cout << endl;
}

void m3() {
    p = treeToList( a, p );
}

void m4() {
    a = listToTree( p );
}

#include "userint.cpp"
int main() {
    Dictionary<std::string, void*> usr;
    usr.add( "Арифметическое выражение в дерево", ( void* )m1 );
    usr.add( "Арифметическое выражение в список", ( void* )m1_1 );
    usr.add( "Принт дерева", ( void* )m2 );
    usr.add( "Принт листа", ( void* )m2_2 );
    usr.add( "Дерево в лист", ( void* )m3 );
    usr.add( "Лист в дерево", ( void* )m4 );

    userinterface( usr );

    
    return 0;
}
