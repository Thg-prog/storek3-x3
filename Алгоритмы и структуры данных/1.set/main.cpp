#include <iostream>
#include <vector>

using namespace std;

bool isMemberOfUniversum(int* universum, int n, int element);

class Set
{
private:
    vector<int> scale;
    vector<int> universum;
public:
    Set(int* _universum, int n) {
        universum.resize(n);
        for (int i = 0; i < n; i++) {
            universum[i] = _universum[i];
        }
        scale.resize(n);
        for (int i = 0; i < n; i++) {
            scale[i] = 0;
        }
    }

    void addMember(int element) {
        int len = universum.size();
        for (int i = 0; i < len; i++) {
            if (element == universum[i]) {
                scale[i] = 1;
            }
        }
    }

    bool isMember(int element) {
        int len = universum.size();
        for (int i = 0; i < len; i++) {
            if (element == universum[i] && scale[i] == 1) {
                return true;
            }
        }
        return false;
    }

    void delMember(int element) {
        int len = universum.size();
        for (int i = 0; i < len; i++) {
            if (element == universum[i]) {
                scale[i] = 0;
            }
        }
    }
    bool isEmpty() {
        int len = scale.size();
        int c = 0;
        for (int i = 0; i < len; i++) {
            if (scale[i] == 0) c++;
        }
        if (c == 0) return true;
        return false;
    }
    
    Set operator+(Set& s1)
    {
    	int len = universum.size();
    	int _universum[len];
    	for (int i = 0; i < len; i++) {
    		_universum[i] = universum[i];
    	}
    	Set s3(_universum, len);
    	for(int i = 0; i < len; i++) { 
			if (scale[i] == 1 || s1.scale[i] == 1) {
				s3.scale[i] = 1; 
			}
		}
    	return s3;
    }
    Set operator*(Set& s1)
    {
    	int len = universum.size();
    	int _universum[len];
    	for (int i = 0; i < len; i++) {
    		_universum[i] = universum[i];
    	}
	    Set s3(_universum, len);
	    for(int i = 0; i < len; i++) {
	    	if (scale[i] == 1 && s1.scale[i] == 1)  {
	    		s3.scale[i] = 1;
	    	}
	    }
	    return s3;
    }
    
    Set operator-(Set& s1) { 
		int len = universum.size();
    	int _universum[len];
    	for (int i = 0; i < len; i++) {
    		_universum[i] = universum[i];
    	}
	    Set s3(_universum, len);
	    for(int i = 0; i < len; i++) {
		    if (scale[i] == 0 && s1.scale[i] == 1) {
		    	s3.scale[i] = 0;
		    }
	    }
	    return s3;
	}
    
	
    Set operator-() // "Дополнение"
    { }

    void show() {
        int len = universum.size();
        cout << "The elements of the current set" << endl;
        for (int i = 0; i < len; i++) {
            if (scale[i] == 1) {
                cout << universum[i] << " ";
            }
        }
        cout << endl;
    }
};

class UI {
public:
    void inputUniversum(int* universum, int n) {
        cout << "Enter the numbers: ";
        for (int i = 0; i < n; i++) {
            cin >> universum[i];
        }
    }

    void printUniversum(int* universum, int n) {
        for (int i = 0; i < n; i++) {
            cout << universum[i] << " ";
        }
        cout << endl;
    }

    void printSets(vector<Set>& v) {
        int len = v.size();
        if (len > 0) {
            cout << "Sets:" << endl;
            for (int i = 0; i < len; i++) {
                cout << i << ": " << "s" << i << "; ";
            }
            cout << endl;
        } else {
            cout << "There are no sets!" << endl;
        }
    }

    void showElementsOfTheSet(vector<Set>& v) {
        printSets(v);
        int len = v.size();
        if (len != 0) {
            cout << "Enter the number of the set what you want to show: ";
            int number;
            cin >> number;
            v[number].show();
        }
    }

    void toIncludeInTheSet(int* universum, int n, vector<Set>& v) {
        printUniversum(universum, n);
        int element;
        cout << "Enter the element of the universum you want to include in the set: ";
        cin >> element;
        if (isMemberOfUniversum(universum, n, element)) {
            printSets(v);
            cout << "Enter the number of the set where you want to include the number: ";
            int number;
            cin >> number;
            int len = v.size();
            if (number >= 0 && number <= len-1) {
	            if (!v[number].isMember(element)) {
	                v[number].addMember(element);
	                v[number].show();
	            } else {
	                cout << "The number is already an element of the set!" << endl;
	            }
        	} else {
        		cout << "There are no current set" << endl;
        	}
        } else {
            cout << "The number is not an element of the universum" << endl;
        }
    }

    void toExcludeElement(vector<Set>& v) {
        printSets(v);
        int len = v.size();
        if (len != 0) {
            cout << "Enter the number of the set where you want to exclude the number: ";
            int number;
            cin >> number;
            int len = v.size();
            if (number >= 0 && number <= len-1) {
	            cout << "Enter the element of the set you want to exclude from the set: ";
	            int element;
	            cin >> element;
	            if (v[number].isMember(element) && !v[number].isEmpty()) {
	                v[number].delMember(element);
	                if (v.size() != 0)
	                        v[number].show();
	            } else {
	                cout << "There are no current element" << endl;
	            }
        	} else {
        		cout << "There are no current set" << endl;
        	}
        }
    }
    
    void toUnite(vector<Set>& v) {
    	printSets(v);
    	if (v.size() != 0) {
	    	cout << "Enter the number of the first set what you want to unite: ";
	    	int number1;
	    	cin >> number1;
	    	cout << "Enter the number of the second set what yout want to unite: ";
	    	int number2;
	    	cin >> number2;
	    	int len = v.size();
	    	if (number1 >= 0 && number1 <= len-1 && number2 >= 0 && number2 <= len-1 && number1 != number2) {
	    		v[number1] = v[number1] + v[number2];
	    	} else {
	    		cout << "There are no current set" << endl;
	    	}
    	}
    }
    
    void toCross(vector<Set>& v) {
    	printSets(v);
    	if (v.size() != 0) {
	    	cout << "Enter the number of the first set what you want to cross: ";
	    	int number1;
	    	cin >> number1;
	    	cout << "Enter the number of the second set what yout want to cross: ";
	    	int number2;
	    	cin >> number2;
	    	int len = v.size();
	    	if (number1 >= 0 && number1 <= len-1 && number2 >= 0 && number2 <= len-1 && number1 != number2) {
	    		v[number1] = v[number1] * v[number2];
	    	} else {
	    		cout << "There are no current set" << endl;
	    	}
    	}
    }
    
    void toSubstract(vector<Set>& v) {
    	printSets(v);
    	if (v.size() != 0) {
	    	cout << "Enter the number of the first set what you want to subsract: ";
	    	int number1;
	    	cin >> number1;
	    	cout << "Enter the number of the second set what yout want to substract: ";
	    	int number2;
	    	cin >> number2;
	    	int len = v.size();
	    	if (number1 >= 0 && number1 <= len-1 && number2 >= 0 && number2 <= len-1 && number1 != number2) {
	    		v[number1] = v[number1] - v[number2];
	    	} else {
	    		cout << "There are no current set" << endl;
	    	}
    	}
    }
};

bool isMemberOfUniversum(int* universum, int n, int element) {
    for (int i = 0; i < n; i++) {
        if (universum[i] == element) {
            return true;
        }
    }
    return false;
}

int main()
{
    UI ui;
    cout << "Enter the length of universum: ";
    int n;
    cin >> n;
    int universum[n];
    ui.inputUniversum(universum, n);
    vector<Set> v;
    cout << "Values: -1-to exit; 0-to print universum; 1-to create empty set; 2-to include in the set; 3-to print array of sets;\
	4-to show elements of the set; 5-to exclude element from set; 6-to unite with something set; 7-to cross with something set;\
	 8-to substract with something set" << endl;
    int value;
    while(true) {
        cout << "Enter the value: ";
        cin >> value;
        if (value == -1) {
            break;
        } else if (value == 0) {
            ui.printUniversum(universum, n);
        } else if (value == 1) {
            Set s(universum, n);
            v.push_back(s);
        } else if (value == 2) {
            ui.toIncludeInTheSet(universum, n, v);
        } else if (value == 3) {
            ui.printSets(v);
        } else if (value == 4) {
            ui.showElementsOfTheSet(v);
        } else if (value == 5) {
            ui.toExcludeElement(v);
        } else if (value == 6) {
        	ui.toUnite(v);
        } else if (value == 7) {
        	ui.toCross(v);
        } else if (value == 8) {
        	ui.toSubstract(v);
        }
    }
    return 0;
}
