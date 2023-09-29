#include <iostream> 
#include <vector>

std::vector<int> t_vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


{ 1, 2, 3 } -- T
{ 0, 0, 1 } -- shk

for i 
    shk[ i ] == 1
        print T[ i ]

class Set {
    private:
        std::vector <int> vec;
    public:
        
        Set() { 

        }

        void add_member( int value ) { 
            for ( int i: t_vec ){
                if ( !this->is_member( value ) && i == value ){
                    this->vec.push_back( value );
                }
            }    
        }

        void del_member( int index ) { 
            if ( !this->is_empty() ){
                this->vec.erase( this->vec.begin()+index );
            }
        }

        bool is_member( int a ) {
            bool is = false;

            for ( int i: t_vec ){
                for ( int j: this->vec ){
                    if ( a == j && i == j ){
                        is = true;
                    }
                }
            }

            return is;
        }

        void remove_members( ){
            this->vec.erase( vec.begin(), vec.end() );
        }

        void print_members( ) {
            std::cout << "{ ";
            for ( int i: this->vec )
                    std::cout << i << "; ";
            std::cout << "}\n";
        }

        bool is_empty() {
            return this->vec.empty();
        }

        void union_members(){

        }

        // "Объединение"
        Set operator+( Set& s1 ) {
            Set s3;
            for ( int i: this->vec )
                s3.add_member( i );

            for ( int i: s1.vec )
                s3.add_member( i );

            return s3;
        }

        // "Пересечение"
        Set operator*( Set& s1 ) {
            Set s3;

            for ( int i: this->vec ){
                for ( int j: s1.vec ){
                    if ( i == j ){
                        s3.add_member( i );
                    }
                    
                }
            }
            return s3;
        }

        // "Разность"
        Set operator-( Set& s1 ) { 
            Set s3;

            for ( int i: this->vec ){
                for ( int j: s1.vec ){
                    if ( i != j ){
                        s3.add_member( i );
                    }
                    
                }
            }

            return s3;
        }

         // "Дополнение"
        Set operator-() { 
            Set s3;

            for ( int i: t_vec ){
                if ( !this->is_member( i ) ){
                    s3.add_member( i );
                }
            }            
            
            return s3;
        }
        
};

void mult_act( int _a, Set m_set ){
    Set set = m_set;
    if ( _a == 1 ){
        m_set.remove_members();
    }

    int a_act = 1;
    int value;
    while ( a_act != 0 ){
        if ( _a == 1 ){
            std::cout << "0 - Закрыть\n1 - Добавить элемент\n2 - Удалить элемент\n3 - Найти элемент\n4 - Проверить на пустоту\n5 - Вывести на экран\n6 - Обьединение множеств\n7 - Пересечение множеств\n8 - Разность множеств\n10 - Вернуться к 1 множеству\nВведите операцию: ";
        } else {
            std::cout << "0 - Закрыть\n1 - Добавить элемент\n2 - Удалить элемент\n3 - Найти элемент\n4 - Проверить на пустоту\n5 - Вывести на экран\n6 - Дополнение\n7 - Создание нового множества\n10 - Вернуться к 1 множеству\nВведите операцию: ";
        }
        
        std::cin >> a_act;
        
        if ( a_act == 1 ){
            std::cout << "Введите число: ";
            std::cin >> value;
            m_set.add_member( value );
        } else if ( a_act == 2 ){
            std::cout << "Введите индекс: ";
            std::cin >> value;
            m_set.del_member( value );
        } else if ( a_act == 3 ){
            std::cout << "Введите число: ";
            std::cin >> value;
            int a = ( m_set.is_member( value ) );
            printf(a ? "true" : "false");
            std::cout << "\n";
        } else if ( a_act == 4 ){
            std::cout << m_set.is_empty();
        } else if ( a_act == 5 ){
            m_set.print_members();
            if ( _a == 1 ){
                set.print_members();
            }
        } else if ( _a == 1 && a_act == 6 ){
            Set s3;
            s3 = m_set + set;
            s3.print_members();
        } else if ( _a != 1 && a_act == 6 ){
            Set s3;
            s3 = -m_set;
            s3.print_members();
        } else if ( _a == 1 && a_act == 7 ){
            Set s3;
            s3 = m_set * set;
            s3.print_members();
        } else if ( _a != 1 && a_act == 7 ){
            mult_act( 1, m_set );
        } else if ( _a == 1 && a_act == 8 ){
            Set s3;
            s3 = m_set - set;
            s3.print_members();
        } else if ( _a == 1 && a_act == 10 ){
            break;
        }
        std::cout << "\n";
    }
}

int main( int argc, char *argv[] ) {
    
    int act;
    std::cout << "Введите операцию (0 - закрыть, 1 - создание пустого множества: ";
    std::cin >> act;

    if ( act == 1 ){
        Set set;
        mult_act( 0, set );
    } else {
        return 0;
    }

    return 0;
}