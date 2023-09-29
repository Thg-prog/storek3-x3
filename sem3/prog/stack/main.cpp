#include "stack.cpp"
#include <vector>
#include <time.h>

using namespace std;

struct AB {
    int a;
    string b;
};

std::ostream& operator<< ( std::ostream &out, const AB &stru ) {
    out << stru.a << " " << stru.b;
    return out;
}

int main() {
    int* arr = new int[ 6 ];

    for ( int i = 0; i<6; i++ ) {
        arr[ i ] = i;
    }

	Stack<int> a( arr, arr+6 );
    
	Stack<int> b { 10, 10, 10, 10 };
	cout << b;

	return 0;
}
