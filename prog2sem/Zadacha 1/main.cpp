#include <iostream>
#include <string>
#include <fstream>
//46
using namespace std;

class FloatS{
    private:
        string integer;
        string fract;
        int compare(FloatS t1);

    public:
        FloatS(string s);
        friend bool operator>(FloatS t1, FloatS t2);
        friend bool operator<(FloatS t1, FloatS t2);
        friend bool operator==(FloatS t1, FloatS t2);
};

bool operator>(FloatS t1, FloatS t2){
    return (t1.compare(t2) == 1);
    
}

bool operator<(FloatS t1, FloatS t2){
    return(t1.compare(t2) == -1);
}

bool operator==(FloatS t1, FloatS t2){
    return(t1.compare(t2) == 0);
}

FloatS::FloatS(string s){
    bool IsInteger = true;
    for(int i = 0; i < s.length(); i++){
        if(s[i] == '.')IsInteger = false;
    }
    string temp;
    if(IsInteger == true){
        for(int i = 0; i < s.length(); i++){
        temp += s[i];
        fract = "0";
    }
    integer = temp;
    } else{
        int pospoint = s.find('.');
        for(int i = 0; i < pospoint; i++){
            temp += s[i];
        }
        if(pospoint == 0){
            integer = "0";
        }
        integer = temp;
        temp = "";
        for(int i = pospoint + 1; i < s.length(); i++){
            temp += s[i];
        }
        fract = temp;
    }
    
}

int FloatS::compare(FloatS t1){
    string temp, temp2;
    int dif = (integer.length() - t1.integer.length());
    dif = abs(dif);
    if(integer.length() > t1.integer.length())for(int i = 0; i < (dif); i++ )t1.integer = "0" + t1.integer;
    if(integer.length() < t1.integer.length())for(int i = 0; i < (dif); i++ )integer = "0" + integer;
    dif = fract.length() - t1.fract.length();
    dif = abs(dif);
    if(fract.length() > t1.fract.length())for(int i = 0; i < (dif); i++ )t1.fract += "0";
    if(fract.length() < t1.fract.length())for(int i = 0; i < (dif); i++ )fract += "0";
    for(int i = 0; i < integer.length(); i++){
        temp += integer[i];
        temp2 += t1.integer[i];
        if(stoi(temp) > stoi(temp2))return 1;
        if(stoi(temp) < stoi(temp2))return -1;
        temp = "", temp2 = "";
    }
    for(int i = 0; i < fract.length() - 1; i++){
        temp += fract[i];
        temp2 += t1.fract[i];
        if(stoi(temp) > stoi(temp2))return 1;
        if(stoi(temp) < stoi(temp2))return -1;
        temp = "", temp2 = "";
    }
    return 0;
}

int main(){
    fstream in;
    ofstream out;
    string temp;
    in.open("COMPARE.IN");
    out.open("COMPARE.OUT");
    getline(in, temp);
    FloatS t1(temp);
    temp = "";
    getline(in, temp);
    FloatS t2(temp);
    if(t1 < t2)out << -1;
    else if(t1 > t2)out << 1;
    else if(t1 == t2)out << 0;
    in.close();
    out.close();
    return 0;
}