#include <iostream>

typedef int Inf;
typedef int Key;

struct Elem;
typedef Elem* pElem;
class Elem {
    public:
        Key key;
        Inf inf;
        pElem next; // ukazatel na next elem;
};

class Elem_2 {
    public:
        Key key1;
        Key key2;
        Key key3;
        Inf inf;
};

class Tab1 {
    private:
        pElem head;
    public:
        Tab1();
        void add( Key k, Inf i );
        void add_a( Key k, Inf i );
        void add_end( Key x, Inf i );
        void del( Key k );
        pElem search( Key k );;
        bool empty();
        void print();
        void sort();
};

Tab1::Tab1() {
    std::cout << "Create table" << std::endl;
    head = NULL;
}

void Tab1::add_a( Key k, Inf i ) {
    pElem min_e = head;
    pElem max_e;

    int min = 0;
    
    int max_m = 0;
    int max = 0;

    int toend = 0;
    
    if ( head != NULL ) {
        min = min_e->key;

        pElem p1;
        pElem p2;   

        p1 = head;

        while ( p1 != NULL ) {
           
            p2 = p1;
            p1 = p1->next;
        }

        std::cout << std::endl;

        if ( min > k ) {
            pElem p = new Elem;
            p->key = k;
            p->inf = i;
            p->next = head;
            head = p;
        } else {

            pElem p = new Elem;
            p->key = k;
            p->inf = i;
            p->next = NULL; 
            p2->next = p;
        }
    } else {    
        pElem p = new Elem;
        p->key = k;
        p->inf = i;
        p->next = head;
        head = p;
    }
}
    

void Tab1::add( Key k, Inf i ) {
    pElem p = new Elem;
    p->key = k;
    p->inf = i;
    p->next = head;
    head = p;
}

void Tab1::add_end( Key x, Inf i ) {
    pElem p1;
    pElem p2;

    p1 = head;
    p2 = head;

    while( p1 != NULL ) {
        p2 = p1;
        p1 = p1->next;
    };

    pElem p3 = new Elem;
    p3->key = x;
    p3->inf = i;
    p3->next = NULL; 
    p2->next = p3;
}

void Tab1::del( Key k ) {
    pElem p1;
    pElem p2;

    p1 = head;
    p2 = head;

    while ( ( p1 != NULL ) && ( p1->key != k ) ) {
        p2 = p1;
        p1 = p1->next;
    }

    if ( p1 != NULL ) {
        if ( p1 == p2 ) {
            head = p1->next;
            delete( p1 );
        } else {
            p2->next = p1->next;
            delete( p1 );
        }
    }
}

pElem Tab1::search( Key k ) {
    pElem p1;
    p1 = head;
    while ( ( p1 != NULL ) && ( p1->key != k ) ) {
        p1 = p1->next;
    }

    return p1;
}

bool Tab1::empty() {
    return head == 0;
}

void Tab1::print() {
    pElem p1;
    p1 = head;

    std::cout << "key" << "\t" << "value" << std::endl;
    while ( ( p1 != NULL ) ) {
        std::cout << p1->key << "\t" << p1->inf << std::endl;
        p1 = p1->next;
    }
}

void Tab1::sort() {
    pElem p1;
    pElem p2;

    p1 = head;
    p2 = head;

    while ( ( p1 != NULL ) ) {
        p1 = p1->next;

        while ( ( p2 != NULL && p1 != p2 ) ) {
            p2 = p2->next;

            if ( p1 != NULL && p2 != NULL ){
                std::cout << p1->key << "\t" << p2->key << std::endl;
            }
        }

        if ( p1 != NULL && p2 != NULL ){
            std::cout << p1->key << "\t" << p2->key << std::endl;
        }
        
    }
}

int main( int argc, char *argv[] ) {

    /*
    Tab1 tabl_1;
    int ex = 0;
    int ex_1 = 0;
    while ( ex != -1 ) {
        std::cout << "-1) Выйти\n1) Добавить в словарь элемент\n2) Удалить элемент\n3) Печатать элементы\nВведите операцию: ";
        std::cin >> ex;

        int a, b;
        if ( ex == 1 ) {
            std::cout << "Введите ключ: ";
            std::cin >> a;
            std::cout << "Введите значение: ";
            std::cin >> b;

            std::cout << "Добавить в начало ( 0 ) или в конец ( 1 _? : ";
            std::cin >> ex_1;

            if ( ex_1 == 0 ) {
                tabl_1.add( a, b );
            } else {'
                tabl_1.add_end( a, b );
            }

            
        } else if ( ex == 2 ) {
            std::cout << "Введите ключ: ";
            std::cin >> a;

            tabl_1.del( a );
        } else if ( ex == 3 ) {
            tabl_1.print();
        }
    }
    */


    Tab1 tabl_1;

    tabl_1.add_a( 10, 10 );
    tabl_1.add_a( 20, 10 );
    tabl_1.add_a( -10, 10 );
    tabl_1.add_a( 30, 10 );
    tabl_1.add_a( 0, 10 );
    tabl_1.add_a( -20, 10 );
    tabl_1.add_a( 50, 10 );
    tabl_1.add_a( -11, 10 );

    tabl_1.print();
    return 0;
}