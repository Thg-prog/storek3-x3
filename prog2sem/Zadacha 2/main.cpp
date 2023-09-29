
#include <iostream>
#include <fstream>

using namespace std;

class Universe{
    private:
        int lenght;
        int height;
        int** cells;
        int** isRecently;
        void life(int** temp) const;
        void death(int** temp)const;
    public:
        Universe(int len, int hei, int** start_cells);
        Universe(const Universe &t);
        Universe(Universe &&t);
        Universe();
        Universe operator=(const Universe &t);
        Universe operator=(Universe &&t);

        ~Universe();
        Universe startGame(int p);
        Universe startGame(int p) const;

        int** getCells() const {return cells;}
};

Universe::Universe(){
    lenght = 0;
    height = 0;
    cells = nullptr;
    isRecently = nullptr;
}

Universe::Universe(const Universe &t){
    if(this->cells != nullptr){
        for(int i = 0; i < height; i++)delete cells[i];
        
    }
    if(this->isRecently != nullptr){
        for(int i = 0; i < height; i++)delete isRecently[i];
    }
    cells = new int*[t.height];
    isRecently = new int*[t.height];
    for(int i = 0; i < t.height; i++){
        cells[i] = new int[lenght];
        isRecently[i] = new int[lenght];
    }
    for(int i = 0; i < t.height; i++){
        for(int j = 0; j < t.lenght; j++){
            cells[i][j] = t.cells[i][j];
            isRecently[i][j] = t.isRecently[i][j];
        }
    }
}

Universe::Universe(Universe &&t){
    if(this == &t)return;
    if(this->cells != nullptr){
        for(int i = 0; i < height; i++)delete cells[i];
        delete[] cells;
    }
    if(this->isRecently != nullptr){
        for(int i = 0; i < height; i++)delete isRecently[i];
        delete[] isRecently;
    }
    cells = t.cells;
    isRecently = t.isRecently;
    t.cells = nullptr;
    t.isRecently = nullptr;
    t.height = 0;
    t.lenght = 0;
}
Universe Universe::operator=(const Universe &t){
    if(this == &t)return *this;
    if(this->cells != nullptr){
        for(int i = 0; i < height; i++)delete cells[i];
        delete[] cells;
    }
    if(this->isRecently != nullptr){
        for(int i = 0; i < height; i++)delete isRecently[i];
        delete[] isRecently;
    }
    cells = new int*[t.height];
    isRecently = new int*[t.height];
    for(int i = 0; i < t.height; i++){
        cells[i] = new int[lenght];
        isRecently[i] = new int[lenght];
    }
    for(int i = 0; i < t.height; i++){
        for(int j = 0; j < t.lenght; j++){
            cells[i][j] = t.cells[i][j];
            isRecently[i][j] = t.isRecently[i][j];
        }
    }
    return *this;
}

Universe Universe::operator=(Universe &&t){
    if(this == &t)return *this;
    if(this->cells != nullptr){
        for(int i = 0; i < height; i++)delete cells[i];
        delete[] cells;
    }
    if(this->isRecently != nullptr){
        for(int i = 0; i < height; i++)delete isRecently[i];
        delete[] isRecently;
    }
    cells = t.cells;
    isRecently = t.isRecently;
    t.cells = nullptr;
    t.isRecently = nullptr;
    t.height = 0;
    t.lenght = 0;
    return *this;
}

Universe::Universe(int hei, int len, int** start_cells){
    lenght = len;
    height = hei;
    cells = new int*[hei];
    isRecently = new int*[hei];
    for(int i = 0; i < hei; i++){
        cells[i] = new int[len];
        isRecently[i] = new int[len];

    }
    for(int i = 0; i < hei; i++){
        for(int j = 0; j < len; j++){
            cells[i][j] = start_cells[i][j];
            isRecently[i][j] = 0;
            }
    }
}

Universe::~Universe(){
    for(int i = 0; i < height; i++){
        delete isRecently[i];
        delete cells[i];
    }
    delete[] isRecently;
    delete[] cells;
}

void Universe::life(int** temp) const{
    int count = 0;
    for(int hei = 0; hei < height; hei++){
        for(int len = 0; len < lenght; len++){
            if(cells[hei][len] == 1){
                temp[hei][len] = cells[hei][len];
                continue;
            };
            for(int i = hei - 1; i <= hei + 1; i++){
                for(int j = len - 1; j <= len + 1; j++){
                    if(i >= 0 && i < height && j >= 0 && j < lenght){
                        if(cells[i][j] == 1)count += 1;
                    }
                }
            }
            if(count == 3){
                temp[hei][len] = 1;
                isRecently[hei][len] = 1;
            }
            else temp[hei][len] = cells[hei][len];
            count = 0;
        }
    }
    for(int i = 0; i < height; i++){
            for(int j = 0; j < lenght; j++){
                cells[i][j] = temp[i][j];
            }
        }
}

void Universe::death(int** temp)const{
    int count = 0;
    for(int hei = 0; hei < height; hei++){
        for(int len = 0; len < lenght; len++){
            if(cells[hei][len] == 0){
                temp[hei][len] = cells[hei][len];
                continue;
            };
            for(int i = hei - 1; i <= hei + 1; i++){
                for(int j = len - 1; j <= len + 1; j++){
                    if(i >= 0 && i < height && j >= 0 && j < lenght){
                        if(cells[i][j] == 1 && isRecently[i][j] != 1 && (i != hei || j != len))count += 1;
                    }
                }
            }
            if(count < 2 || count > 3)temp[hei][len] = 0;
            else temp[hei][len] = cells[hei][len];
            count = 0;
        }
    }
}

Universe Universe::startGame(int p){
    int** temp = new int*[height];
    for(int i = 0; i < lenght; i++)temp[i] = new int[lenght];
    int cont = 1;
    while(cont < p){
        life(temp);
        death(temp);
        
        for(int i = 0; i < height; i++){
            for(int j = 0; j < lenght; j++){
                cells[i][j] = temp[i][j];
                isRecently[i][j] = 0;
            }
        }
        
        
        cont++;
    }
    for(int i = 0 ; i < height; i++)delete temp[i];
    delete[] temp;
    return *this;
}

Universe Universe::startGame(int p) const{
    Universe temp(lenght, height, cells);
    return temp.startGame(p);
}
int main(){
    fstream in;
    ofstream out;
    in.open("./LIFE.IN");
    out.open("./LIFE.OUT");
    int m, n, p;
    in >> m;
    in >> n;
    in >> p;
    int** start_cells = new int*[m];
    for(int i = 0; i < m; i++){
        start_cells[i] = new int[n];
    }
    char o;
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){ 
            in >> o;
            if(o == '*')start_cells[i][j] = 1;
            else if (o == '.') start_cells[i][j] = 0;
            else start_cells[i][j] = 0;
    }
    }
   const Universe game(m, n, start_cells);
   Universe temp(game.startGame(p));
   for(int i = 0; i < m; i++){
       for(int j = 0; j < n; j++){
            if(temp.getCells()[i][j] == 1)out << "* ";
            else if(temp.getCells()[i][j] == 0)out << ". ";
            if(temp.getCells()[i][j] == 1) cout << "* ";
            else if(temp.getCells()[i][j] == 0) cout << ". ";
       }
       out << "\n";
       cout << "\n";
       delete start_cells[i];

   }
   delete[] start_cells;
    return 0;
}