#include <iostream>

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

        void add( int x ) { // Добавить в стек.
            Elem* el = new( Elem );
            el->x = x;
            el->next = head;
            head = el;
        }

        bool isEmpty() { return head == NULL; }; // Пустой ли стек.

        int get() {
            Elem* p = head;
            if ( head->next != NULL ) {
                int a = p->x;
                head = head->next;
                delete( p );
                
                return a;
            }

            return 0;

        }; // Выборка.

        Elem* readHead() { return head; }; // Чтение из головы.
};

class Dack: public Stack {
    public:
        Dack() { head = NULL; };

        void add() {};
        void add_b( int x ) {
            Elem* el = new Elem;
            el->x = x;
            el->next = head;
            head = el;
        }

        void add_f( int x );

        void print() { // Печатает стек.
            Elem* el = head;
            while ( el ) {
                cout << el->x << " ";
                el = el->next;
            }
            cout << endl;
        }

        int get();
        int get_b() {
            Elem* p = head;
            int a = p->x;
            if ( head->next != NULL ) {
                head = head->next;
                delete( p );
            
                return a;
            }

            return 0;
        }; // Выборка.

        int get_f();
};

class Queue: public Stack {
    public:
        Queue() { head = NULL; };

        void add( int x );

        void print() { // Печатает стек.
            Elem* el = head;
            while ( el ) {
                cout << el->x << " ";
                el = el->next;
            }
            cout << endl;
        }

        int get() {
            Elem* p = head;
            if ( head->next != NULL ) {
                int a = p->x;
                head = head->next;
                delete( p );
                
                return a;
            }

            return 0;
        }; // Выборка.
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

void Dack::add_f( int x ) {
    Elem* el = new Elem;
    el->x = x;
    
    Elem* ls = last( head );
    el->next = NULL;
    ls->next = el;
}

void Queue::add( int x ) {
    Elem* el = new Elem;
    el->x = x;
    
    Elem* ls = last( head );
    el->next = NULL;
    ls->next = el;
}

int Dack::get_f() {
    Elem* p = preLast( head );
    if ( p->next != NULL ) {
        int a = p->next->x;
        delete( p->next );
        p->next = NULL;
        return a;
    }

    return 0;
}

int main() {
    Stack st;
    Queue qu;
    Dack dk;

    int s_act = 1;
    int sb_act = 0;

    while ( s_act != 0 ){
        cout << "1: Stack\n2: Dack\n3: Queue\n0: Exit" << endl;
        cin >> s_act;

        switch ( s_act ) {
            case 1: {
                cout << "1)Добавить элемент\n2)Вывести стек\n3)Проверка на пустой стек\n4)Удаление элемента\n"<<endl;
                cin >> sb_act;
                switch ( sb_act ) {
                    case 1: {
                        cout << "Введите значение" << endl;
                        int number;
                        cin >> number;
                        st.add( number );
                        break;
                    }

                    case 2: {
                        st.print();
                        break;
                    }

                    case 3: {
                        cout << ( st.isEmpty() ? "Стек пустой" : "Стек заполнен" ) << endl;
                        break;
                    }
                    
                    case 4: {
                        int s = st.get();
                        //if ( s != 0 ) {
                            cout << "Ваш последний элемент: " << s << endl;
                        //}
                        break;
                    }
                }

                break;
            }

            case 2: {
                cout << "1)Добавить элемент в начало\n2)Добавить элемент в конец\n3)Вывести дек\n4)Проверить на пустоту дек\n7)Взять элемент из начала\n8)Взять элемент из конца" << endl;
                cin >> sb_act;
                switch ( sb_act ) {
                    case 1: {
                        cout << "Введите значение" << endl;
                        int number;
                        cin >> number;
                        dk.add_f( number );
                        break;
                    }

                    case 2: {
                        cout << "Введите значение" << endl;
                        int number;
                        cin >> number;
                        dk.add_b( number );
                        break;
                    }

                    case 3: {
                        dk.print();
                        break;
                    }

                    case 4: {
                        cout << ( dk.isEmpty() ? "Дек пустой" : "Дек заполнен" ) << endl;
                        break;
                    }

                    case 5: {
                        int x = dk.get_f();
                        //if ( x != 0 ) {
                            cout << "Ваш последний элемент: " << x << endl;
                        //}
                        break;
                    }

                    case 6:{
                        int x = dk.get_b();
                        if ( x != 0 ) {
                            cout << "Ваш последний элемент: " << x << endl;
                        }
                        break;
                    }
                }

                break;
            }

            case 3: {
                cout << "1)Добавить элемент\n2)Вывесть очередь\n3)Проверить на пустоту\n4)Взять элемент из очереди\n" <<endl;
                cin >> sb_act;
                switch ( sb_act ) {
                    case 1: {
                        cout << "Введите значение" << endl;
                        int number;
                        cin >> number;
                        qu.add( number );
                        break;
                    }

                    case 2: {
                        qu.print();
                        break;
                    }

                    case 3: {
                        cout << ( qu.isEmpty() ? "Очередь пустая" : "Очередь заполнена" ) << endl;
                        break;
                    }
                    case 4: {
                        int x = qu.get();
                        //if ( x != 0 ) {
                            cout << "Ваш последний элемент: " << x << endl;
                        //}
                        break;
                    }
                }
                
                break;
            }

        }

    }

    return 0;
}
