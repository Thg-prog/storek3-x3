#include <iostream>
#include <cmath>

template<typename T>
class Tree {
    private:
		T value;
   		Tree left;
		Tree right;
	public:
        Tree();
        Tree( Stack&& other );
        Tree( const Stack& other ) noexcept;
        Tree( std::initializer_list<T> args );
        template<typename Iter>
        Tree( Iter begin, Iter end );
		~Tree( );

		void add( Tree th );
		void add_elem( T nw );
		T find( );
		Tree findTree( Tree a );
		
		void delete_elem( T el );
		void clear( );
		
		template<typename Y>
		friend operator<< ( ostream& out, Tree<Y> curr );
		
		template<typename Y>
		friend operator== ( Tree<Y> left, Tree<Y> right );
		
		template<typename Y>
		friend operator!= ( Tree<Y> left, Tree<Y> right );

};

Tree::Tree( ) { };
