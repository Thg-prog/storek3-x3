#include <iostream>
#include <cmath>

template<typename T>
class Stack {
    private:
        T* arr;
        int n;
        int max; 
        int sarr;
    public:
        Stack();
        Stack( int _sarr );
        Stack( Stack&& other ) noexcept;
        Stack( const Stack& other );
        Stack( std::initializer_list<T> args );
        template<typename Iter>
        Stack( Iter begin, Iter end );

        ~Stack();

        void push( T val );
        T pop();
        T check_pop() const;
        bool empty() const noexcept;
        int size() const noexcept;
        int sizearr() const noexcept;
        void clear() noexcept;
        void top( T value );
		void swap( T &other );
        void relmem();
        Stack& operator= ( const Stack& other ) ;
        Stack& operator= ( Stack&& other ) noexcept;
        bool operator== ( const Stack& other ) const;
        bool operator!= ( const Stack<T>& other ) const;
        
        template<typename Y>
        friend std::ostream& operator<< ( std::ostream &out, const Stack<Y> &stack );
        
        // stack1 << 1 << 3 << 5
        template<typename Y>
        friend Stack<Y>& operator<< ( Stack<Y> &stack, Y other );

        // stack1 >> a >> b;
        template<typename Y>
        friend Stack<Y>& operator>> ( Stack<Y> &stack, Y &other );
};


template<typename T>
Stack<T>::Stack() : Stack( 10 ) {};

template<typename T>
Stack<T>::Stack( int _sarr ) : sarr( _sarr ), n( 0 ) {
    if ( _sarr > 0 ) {
		max = _sarr;
		arr = new T[ max ];
	} else { 
		max = 10;
		arr = new T[ max ];
	}
}

template<typename T>
Stack<T>::Stack( Stack<T>&& other ) : n( other.n ), sarr( other.sarr ), max( other.max ) {
    arr = other.arr;
	other.n = 0;
}
        
template<typename T>
Stack<T>::Stack( const Stack<T>& other ) noexcept : n( other.n ), sarr( other.sarr ), max( other.max ) {
    arr = new T[ other.max ];
    std::copy( other.arr, other.arr+max, arr );
}

template<typename T>
Stack<T>::Stack( std::initializer_list<T> args ) : Stack( args.size() ) {
    n = args.size();
    int _sarr = n / sarr;
    
    if ( _sarr * sarr < n ) {
        max  = ( _sarr * sarr ) + sarr;
    } else {
        max = _sarr * sarr;
    }

    if ( max > 0 ) {
        arr = new T[ max ];

        auto c = args.begin();
        for ( int i = 0; i<n; i++ ) {
            arr[ i ] = *c;
            ++c;
        }
    }
}

template<typename T>
template<typename Iter>
Stack<T>::Stack( Iter begin, Iter end ) : Stack( std::distance( begin, end ) ) {    
    int nd = std::distance( begin, end );
    n = nd;

    int _sarr = nd / sarr;
    if ( _sarr * sarr < nd ) {
        max = ( _sarr * sarr ) + sarr;
    } else {
        max = _sarr * sarr;
    }

    if ( max  > 0 ) {
        arr = new T[ max ];

        for ( Iter i = begin; i != end; i++ ) {
            arr[ nd-(end-i) ] = *i;
        }
    }
}

template<typename T>
Stack<T>::~Stack() {
    delete[] arr;
}

template<typename T>
void Stack<T>::push( T val ) {
    n++;

    if ( n > max ) {
        max += sarr; 
        T* nrr = new T[ max ];
        std::copy( arr, arr+n, nrr );
        delete[] arr;
        arr = nrr;            
    }

    arr[ n - 1 ] = val;
}

template<typename T>
T Stack<T>::Stack::pop() {
    if ( n > 0 ) {
        n--;            
        return arr[ n ];
    } else {
        throw std::invalid_argument( "out of range" );
    }
}

template<typename T>
T Stack<T>::check_pop() const {
    if ( n > 0 ) {
        return arr[ n ];
    } else { 
        throw std::invalid_argument( "out of range" );
    }
}

template<typename T>
bool Stack<T>::empty() const {
    return n == 0;
}

template<typename T>
int Stack<T>::size() const {
    return n;
}

template<typename T>
int Stack<T>::sizearr() const {
    return max;
}

template<typename T>
void Stack<T>::clear() {
    n = 0;
}

template<typename T>
void Stack<T>::top( T value ) {
    arr[ n - 1 ] = value;
}

template<typename T>
void Stack<T>::swap( T &other ) { 
	T tmp = arr[ n - 1 ];
	arr[ n - 1 ] = other;
	other = tmp;
}

template<typename T>
void Stack<T>::relmem() {
    int _sarr = n / sarr;
    if ( _sarr * sarr < n ) {
        max = ( _sarr * sarr ) + sarr;
    } else {
        max = _sarr * sarr;
    }
    
    if ( max > 0 ) {
        T* nrr = new T[ max ];
        std::copy( arr, arr+n, nrr );
        delete[] arr;
        arr = nrr;
    }
}

template<typename T>
Stack<T>& Stack<T>::operator= ( const Stack<T>& other ) noexcept {
    if ( this != &other ) {
        arr = new T[ other.max ];
        n = other.n;
        sarr = other.sarr;
        max = other.max;

        std::copy( other.arr, other.arr+n, arr );
    }

    return *this;
}

template<typename T>
Stack<T>& Stack<T>::operator= ( Stack<T>&& other ) {
    if ( this != &other ) {
        arr = new T[ other.max ];
        n = other.n;
        sarr = other.sarr;
        max = other.max;

        std::copy( other.arr, other.arr+n, arr );

        other.n = 0;
    }

    return *this;
}

template<typename T>
bool Stack<T>::operator== ( const Stack<T>& other ) const {
    if ( n == other.n ) {
        bool t = true;
        for ( int i = 0; i<n; i++ ) {
            if ( arr[ i ] != other.arr[ i ] ) {
                t = false;
                break;
            }
        }

        return t;
    } else {
        return false;
    } 
}

template<typename T>
bool Stack<T>::operator!= ( const Stack<T>& other ) const {
    return !( *this == other );
}

template<typename T>
std::ostream& operator<< ( std::ostream &out, const Stack<T> &stack ) {
    for ( int i = 0; i<stack.n; i++ ) {
        out << stack.arr[ i ] << "\n";
    }

    return out;
}

// stack1 << 1 << 3 << 5
template<typename T>
Stack<T>& operator<< ( Stack<T> &stack, T other ) {
    stack.push( other );
    return stack;
}

// stack1 >> a >> b;
template<typename T>
Stack<T>& operator>> ( Stack<T> &stack, T &other ) {
    other = stack.pop();
    return stack;
}
