#include <iostream>
using namespace std;

const int n = 4;
bool* visited = new bool[ n ];
int graph[ n ][ n ] = {
    { 0, 1, 1, 0 },
    { 0, 0, 1, 1 },
    { 1, 0, 0, 1 },
    { 0, 1, 0, 0 }
};

void SDG( int i ) {
    int r;
    cout << i + 1 << " ";
    visited[ i ] = true;
    for ( r = 0; r<n; r++ ) {
        if ( ( graph[ i ][ r ] != 0 ) && ( !visited[ r ] ) ) {
            SDG( r );
        }
    }
}

void BFS( bool* visited, int unit ) {
    int* queue = new int[ n ];
    int count = 0;
    int head = 0;

    for ( int i = 0; i < n; i++ ) {
        queue[ i ] = 0;
    }
    queue[ count++ ] = unit;
    visited[ unit ] = true;
    while ( head < count ) {
        unit = queue[ head++ ];
        cout << unit + 1 << " ";
        for ( int i = 0; i < n; i++ ) {
            if ( graph[ unit ][ i ] && !visited[ i ] ) {
                queue[ count++ ] = i;
                visited[ i ] = true;
            }
        }
    }

    delete[] queue;
}

int main() {
    int start;
    cout << "Матрица смежности графа: " << endl;
    for ( int i = 0; i<n; i++ ) {
        visited[ i ] = false;
        for ( int j = 0; j<n; j++ ) {
            cout << " " << graph[ i ][ j ];
            cout << endl;
        }
    }
    
    cout << "Стартовая вершина: ";
    cin >> start;
    bool* vis = new bool[ n ];
    cout << "Порядок обхода: ";
    SDG( start - 1 );
    cout << endl;
    delete[] visited; 


    return 0;
}

