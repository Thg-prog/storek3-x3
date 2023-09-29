struct coord_t {
    int x;
    int y;
};

class Cell {
    private:
        bool Alive = true;
        coord_t Pos;
        int Gen = 1;

    public:
        Cell() {};
        Cell( int x, int y );
        Cell( coord_t c );
        Cell( const Cell& cell );
        Cell( Cell&& cell );

        ~Cell() {};

        int getX() const;
        int getY() const;
        void setX( int _x );
        void setY( int _y );
        bool isAlive() const;
        void setAlive( bool _alive );
        void setGen( int _gen );
        int getGen() const;
        Cell& operator= ( const Cell& cell );
};

class Universe {
    private:
        int M; // Строка
        int N; // Столбец
        
        Cell* cells; // Массив клеток
        int P; // Популяция
        int G; // Поколение

        // по ссылке возращает для сравнивания ссылок Cell
        Cell* getcell( int X, int Y ) const; 

        // по ссылке определяет что cell не равно перечисленным обьектам Cell в области 3x3
        int find_in_circle( Cell* cell ) const;

        // находит ближайшее место к Cell для создание новой генерации
        coord_t nearest_coord_cell( Cell* cell ) const;

    public:
        Universe();
        Universe( int _M, int _N, int _P );
        Universe( int _M, int _N, int _P, coord_t* XY );
        Universe( const Universe& univ ); 
        Universe( Universe&& univ );

        ~Universe();

        int getM() const;
        int getN() const;
        int getP() const;
        
        void dist_cells();

        void new_generation();
        Universe new_generation() const;
        void new_generation_mem();

        Cell newgenCell( coord_t xy );
        
        Universe& operator= ( const Universe& other );

        friend std::ostream& operator<< ( std::ostream &out, const Universe &univ );
};