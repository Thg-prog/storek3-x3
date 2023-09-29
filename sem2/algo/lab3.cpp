#include <iostream>
#include <cstring>
using namespace std;

class String {
    private:
        static const int n = 10;
        char str [ n + 2 ]; // 0 - длина, n+2 - конец \0
    public:
        String() { // обычный конструктор
            str[ 0 ] = 0;
        }

        String( char s[ ] ) { // конструктор с массивом
            str[ 0 ] = 0;
            for ( int i = 0; s[ i ] != '\0'; i++ ) {
                add( s[ i ] );
            }
        }

        void add( char x ) { // добавление символа
            if ( str[ 0 ] == this->n ){
                return;
            }

            str[ 0 ]++;
            str[ str[ 0 ] ] = x;
        }
        
        void del( int id ) { // удаление символа
            str[ id ] = '\0';
        }
        
        void strcut( int k, String &s ) { // разделенеие строки
            if ( k > 0 ) {
                for ( int i = k; i <= int( str[ 0 ] ); i++ ) {
                    s.add( str[ i ] );
                    //this->del( i );
                }

                str[ k ] = '\0'; // е подходит поскольку это не char*
            }
        }

        void addstr( String s ) { // конкатенция строк
            for ( int i = 1; i <= s.strlen_s(); i++ ) {
                this->add( s.str[ i ] );
            }
        }

        int findcombo( String s ) { // контекстный поиск
            int num = 0;
            int sum = 0;
            for ( int i = 1; i <= int( str[ 0 ] ); i++ ) {
                sum = 0;
                for ( int j = 1; j <= s.strlen_s(); j++ ) {
                    if ( str[ i + j - 1 ] == s.str[ j ] ) {
                        sum++;

                        if ( num == 0 ){
                            num = i;
                        }
                    } else {
                        num = 0;
                    }
                }

                if ( sum == s.strlen_s() ) {
                    break;
                }
            }

            return num;
        }

        void strmove( String s1, String s2 ) { // контекстная замена
            int b = s2.strlen_s();
            int n = findcombo( s1 );
            for ( int i = n; i<b; i++ ) {
                str[ i ] = s2.str[ i ];
            }

        }

        void display() { // выводит строку
            for ( int i = 1; str[ i ] != '\0'; i++ ) {
                cout << str[ i ];
            }

            cout << endl;
        }

        int strlen_s() { // выводит количество элементов
            return int( str[ 0 ] );
        }
};

int main() {
    int menu = 1;
    int create = 0;

    String* str = new String;
    int n = 1;

    /*while ( menu != 0 ) {
        cout << "0) Выйти" << endl;
        cout << "1) Создать строку" << endl;
        
        if ( n > 1 ) {
            cout << "2) Вывести строку(и)" << endl;
            cout << "3) Добавить символ в строку(и)" << endl;
        }

        if ( n > 2 ) {
            cout << "4) Добавить строку в конец строки" << endl;
            cout << "5) Найти похожее в строке" << endl;
        }
        
        cout << "Введите действие: ";

        cin >> menu;

        if ( menu == 0 ){
            break;
        } else if ( menu == 1 ) {
            str = new String[ n ];
            n++;
        } else if ( n >= 1 && menu == 2 ) {
            for ( int i = 1; i<n; i++ ){
                cout << i << ") ";
                str[ i ].display();
            }
            cout << endl;
        } else if ( n >= 1 && menu == 3 ) {
            int str_to_add = 0;
            char s;
            for ( int i = 1; i<n; i++ ){
                cout << i << ") Строка" << endl;
            }

            cout << "Выберете строку: ";
            cin >> str_to_add;
            cout << "Напечатайте символ: ";
            cin >> s;
            
            str[ str_to_add ].add( s );
            
            cout << endl;

        } else if ( n >= 2 && menu == 4 ) {
            int str_to_add = 0;
            int str_of = 0;

            for ( int i = 1; i<n; i++ ){
                cout << i << ") Строка" << endl;
            }

            cout << "Выберете строку: ";
            cin >> str_of;
            cout << "Выберете какую хотите добавить: ";
            cin >> str_to_add;

            str[ str_of ].addstr( str[ str_to_add ] );
        } else if ( n >= 2 && menu == 5 ) {
            int str_to_add = 0;
            int str_of = 0;

            for ( int i = 1; i<n; i++ ){
                cout << i << ") Строка" << endl;
            }

            cout << "Выберете строку: ";
            cin >> str_of;
            cout << "Выберете какую хотите найти: ";
            cin >> str_to_add;

            cout << str[ str_of ].findcombo( str[ str_to_add ] ) << endl;
        } else if ( n >= 2 && menu == 6 ) {
            int str_to_add = 0;
            int str_of = 0;
            int str_replace = 0;

            for ( int i = 1; i<n; i++ ){
                cout << i << ") Строка" << endl;
            }

            cout << "Выберете строку: ";
            cin >> str_of;
            cout << "Выберете какую строку которую хотите заменить: ";
            cin >> str_to_add;
            cout << "Выберете чем заменить: ";
            cin >> str_replace;

            str[ str_of ].strmove( str[ str_to_add ], str[ str_replace ] );
        }
    }*/

    String a, b;
    a.add( '1' );
    a.add( '2' );
    a.add( '3' );
    a.add( '2' );
    a.add( '4' );
    a.add( '5' );

    b.add( '2' );
    b.add( '4' );

    cout << a.findcombo( b ) << endl; 
    return 0;
}