#include<iostream>
#include<cstring>
#include<vector>

using namespace std;

template<int N = 0>
class bitSet {
    private:
        size_t _N = 0;
        vector<bool> bits;
    public:
        bitSet( const bitSet& bset );
        bitSet( bitSet&& bset ) noexcept;
        bitSet( unsigned long num );
        bitSet() : bits( N, false ) {};
        bitSet( string bitchar );

        bool all() const;
        bool any() const;
        bool nope() const;

        int size() const;
        
        void set( bool v );
        void set( int i, bool v );

        bool operator== ( const bitSet<N>& rhs );
        bool operator!= ( const bitSet<N>& rhs );

        vector<bool>::reference operator[] ( int index );
        bool operator[] ( int index ) const;

        bitSet& operator= ( const bitSet& bset );
        bitSet& operator= ( bitSet&& bset ) noexcept;

        bitSet operator~ () const;
        bitSet operator<< ( int iter ) const;
        bitSet operator>> ( int iter ) const;

        bitSet& operator<<= ( int pos );
        bitSet& operator>>= ( int pos );

        template<int n, int m>
        friend bitSet<n> operator& ( const bitSet<n> lhs, const bitSet<n> rhs );

        template<int n, int m>
        friend bitSet<n> operator| ( const bitSet<n> lhs, const bitSet<m> rhs );

        template<int n, int m>
        friend bitSet<n> operator^ ( const bitSet<n> lhs, const bitSet<n> rhs );

        template<int n>
        friend std::ostream& operator<< ( std::ostream &out, const bitSet<n> &bset );
};