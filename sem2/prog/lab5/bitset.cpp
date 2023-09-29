#include "bitset.h"

// конструктор копирования

template<int N>
bitSet<N>::bitSet( const bitSet& bset ) {
    bits = bset.bits;
};

template<int N>
bitSet<N>::bitSet( bitSet&& bset ) noexcept {
    bits = bset.bits;
};

template<int N>
bitSet<N>::bitSet( unsigned long num ) {
    do {
        bits.insert( bits.begin(), num % 2 );
        _N++;
        num = num / 2; 
    } while ( num / 2 != 0 );

    if ( num / 2 == 0 ) {
        bits.insert( bits.begin(), num % 2 );
        _N++;
    }
}

template<int N>
bitSet<N>::bitSet( string bitchar ) : _N( bitchar.length() ), bits( _N, false ) {
    for ( char c : bitchar ) {
        bits.push_back( c == '1' ? true : false );
        bits.erase( bits.begin() );
    }
}

template<int N>
bool bitSet<N>::all() const {
    bool b = true;
    for ( int i = 0; i < _N - 1; i++ ) {
        if ( bits[ i ] != bits[ i + 1 ] ) b = false;
    }

    return b;
}

template<int N>
bool bitSet<N>::any() const {
    bool b = false;
    for ( int i = 0; i < _N; i++ ) if ( bits[ i ] ) b = true;

    return b;
}

template<int N>
bool bitSet<N>::nope() const {
    return !any();
}

template<int N>
int bitSet<N>::size() const {
    return bits.size();
}

template<int N>
void bitSet<N>::set( bool v ) {
    for ( int i = 0; i < bits.size(); i++ ) bits[ i ] = v;
};

template<int N>
void bitSet<N>::set( int i, bool v ) {
    bits[ i ] = v;
};

template<int N>
bool bitSet<N>::operator== ( const bitSet<N>& rhs ) {
    bool b = true;
    for ( int i = 0; i < _N; i++ ) {
        if ( rhs[ i ] != bits[ i ] ) b = false;
    }

    return b;
}

template<int N>
bool bitSet<N>::operator!= ( const bitSet<N>& rhs ) {
    return ( !( *this == rhs ) );
}

template<int N>
vector<bool>::reference bitSet<N>::operator[] ( int index ) {
    return bits[ index ];
}

template<int N>
bool bitSet<N>::operator[] ( int index ) const {
    return bits[ index ];
}

template<int N>
bitSet<N>& bitSet<N>::operator= ( const bitSet& bset ) {
    if ( this != &bset ) bits = bset.bits;
    return *this;
}

template<int N>
bitSet<N>& bitSet<N>::operator= ( bitSet&& bset ) noexcept {
    if ( this != &bset ) bits = bset.bits;
    return *this;
}

template<int N>
bitSet<N> bitSet<N>::operator~ () const {
    bitSet nset = *this;
    for ( int i = 0; i < _N; i++ ) nset[ i ] = !nset[ i ];

    return nset;
}

template<int N>
bitSet<N> bitSet<N>::operator<< ( int iter ) const {
    bitSet nset = *this;
    
    for ( int i = 0; i < iter; i++ ) {
        nset.bits.erase( nset.bits.begin() );
        nset.bits.push_back( 0 );
    }

    return nset;
}

template<int N>
bitSet<N> bitSet<N>::operator>> ( int iter ) const {
    bitSet nset = *this;

    for ( int i = 0; i < iter; i++ ) {
        nset.bits.pop_back();
        nset.bits.insert( nset.bits.begin(), 0 );
    }

    return nset;
}

template<int N>
bitSet<N>& bitSet<N>::operator<<= ( int pos ) {
    *this = ( *this << pos );
    return *this;
}

template<int N>
bitSet<N>& bitSet<N>::operator>>= ( int pos ) {
    *this = ( *this >> pos );
    return *this;
}

template<int N, int M>
bitSet<N> operator& ( const bitSet<N> lhs, const bitSet<M> rhs ) {
    if ( lhs.size() == rhs.size() ) {
        bitSet<N> nset( lhs.size() );

        for ( int i = 0; i < lhs.size(); i++ ) {
            if ( lhs[ i ] == 1 && rhs[ i ] == 1 ) nset.set( i, true );
        }
        
        return nset;
    } else {
        throw runtime_error( "ERR." );
    }
}

template<int N, int M>
bitSet<N> operator| ( const bitSet<N> lhs, const bitSet<M> rhs ) {
    if ( lhs.size() == rhs.size() ) {
        bitSet<N> nset( lhs.size() );

        for ( int i = 0; i < lhs.size(); i++ ) {
            if ( lhs[ i ] == 1 || rhs[ i ] == 1 ) nset.set( i, true );
        }
        
        return nset;
    } else {
        throw runtime_error( "ERR." );
    }
}

template<int N, int M>
bitSet<N> operator^ ( const bitSet<N> lhs, const bitSet<M> rhs ) {
    return ( ( lhs | rhs ) & ( ~lhs | ~rhs ) );
}

template<int N>
std::ostream& operator<< ( std::ostream &out, const bitSet<N> &bset ) {
    for ( int i = 0; i < bset.size(); i++ ) out << bset[ i ];
    return out;
}