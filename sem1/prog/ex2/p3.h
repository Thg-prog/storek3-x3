class Num {
    private:
        std::string n; // строка числа
        int s; // система счисления
        int d; // число переведенное
    public:
        Num();
        Num( int d );
        Num( std::string a, int _s );
        Num( Num&& n );
        Num( const Num& n );

        friend bool operator== ( const Num& ath, const Num& other );
        friend bool operator!= ( const Num& ath, const Num& other );
        friend bool operator> ( const Num& ath, const Num& other );
        friend bool operator< ( const Num& ath, const Num& other );
        friend bool operator>= ( const Num& ath, const Num& other );
        friend bool operator<= ( const Num& ath, const Num& other );

        Num& operator= ( const Num& other );

        friend std::ostream& operator<< ( std::ostream &out, const Num &num );
        friend std::istream& operator>> ( std::istream &in, Num &num );
};