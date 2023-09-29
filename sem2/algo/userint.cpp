#include <iostream>
#include <tuple>
#include <variant>
#include <cstring>
#include <functional>
using namespace std;

template<typename KeyType, typename ValueType>
class KeyAndValue {
    private:
        ValueType (*f)();
    public:
        KeyAndValue() {};
        KeyAndValue( KeyType _key, ValueType _value ) {
            key = _key;
            value = _value;
        }

        KeyType key;
        ValueType value;

        bool isfunc() {
            if ( f != nullptr ) return true;
            return false; 
        }

        void func() {
            if ( isfunc() ) {
                //f = (ValueType (*)())value;
                value();
            }
        }
};

template<typename KeyType, typename ValueType>
KeyAndValue<KeyType, ValueType> create_keyvalue( KeyType key, ValueType value ) {
    KeyAndValue<KeyType, ValueType> a;
    a.key = key;
    a.value = value;

    return a;
}

template<typename KeyType, typename ValueType>
class Dictionary {
    private:
        KeyAndValue<KeyType, ValueType>* keysAndValues = nullptr;
        int cp = 0;
    public:
        Dictionary() {};
        ~Dictionary() {
			delete[] keysAndValues;
  	    }

        const int len() const {
            return cp;
        }

        void add( KeyType key, ValueType value ) {
            KeyAndValue<KeyType, ValueType>* nw = new KeyAndValue<KeyType, ValueType>[ cp + 1 ];
            copy( keysAndValues, keysAndValues+cp, nw );

            delete[] keysAndValues;
            keysAndValues = nw;
            
            keysAndValues[ cp ] = KeyAndValue( key, value );
            cp++;
        };

        KeyAndValue<KeyType, ValueType> get( int ind ) const {
            return keysAndValues[ ind ];
        }
};

void userinterface( Dictionary<string, std::function<void()>> inter ) {
    cout << "---USER-INTERFACE---\n";
    int temp_w = -2;
    while ( temp_w != -1 ) {
        cout << "-1) Выйти" << endl;
        for ( int i = 0; i < inter.len(); i++ ) {
            KeyAndValue kav = inter.get( i );
            cout << i <<") " << kav.key << endl;
        }

        cout << "Введите: ";
        cin >> temp_w;
        system( "clear" );
        inter.get( temp_w ).func();
    }
}