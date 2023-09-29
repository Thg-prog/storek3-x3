
template<typename T>
class Stack {
    private:
        T* arr;
        int n = 0;
        int max = 0;
        int sarr = 16;
    public:
        Stack();

        Stack( Stack&& other );
        Stack( const Stack& other ) noexcept;
        Stack( std::initializer_list<T> args );

        template<typename Iter>
        Stack( Iter begin, Iter end );

        ~Stack();

        void newmem() {
            max += size;
            arr = new T[ max ];
        }

        void push( T val );
        T pop();
        T check_pop() const;
        bool empty() const;
        int size() const;
        void clear();
        void top( T value );
        void swap( Stack& other );
    
        Stack& operator= ( const Stack& other ) ;
        Stack& operator= ( Stack&& other ) noexcept;

        bool operator== ( const Stack& other ) const;
        bool operator!= ( const Stack& other ) const;

        template<typename Y>
        friend std::ostream& operator<< ( std::ostream &out, const Stack<Y> &stack );
        
        template<typename Y>
        friend Stack<Y>& operator<< ( Stack<Y> &stack, T other );

        template<typename Y>
        friend Stack<Y>& operator>> ( T other, Stack<Y> &stack );
};
