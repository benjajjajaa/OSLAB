#include <iostream>
using namespace std;

class MVT {
private:
    int ms, mp[10], temp, n;

public:
    void input() {
        cout << "Enter total memory: ";
        cin >> ms;
        temp = ms;
        n = 0;
    }

    void allocate() {
        char ch = 'y';

        for(int i = 0; ch == 'y'; i++, n++) {
            cout << "Process " << i+1 << ": ";
            cin >> mp[i];

            if(mp[i] <= temp) {
                cout << "Allocated\n";
                temp -= mp[i];
            } else {
                cout << "Memory Full\n";
                break;
            }

            cout << "Continue (y/n): ";
            cin >> ch;
        }
    }

    void display() {
        cout << "\nPROCESS\tMEMORY\n";
        for(int i = 0; i < n; i++)
            cout << i+1 << "\t" << mp[i] << endl;

        cout << "\nTotal Allocated: " << ms - temp;
        cout << "\nExternal Fragmentation: " << temp;
    }
};

int main() {
    MVT obj;
    obj.input();
    obj.allocate();
    obj.display();
    return 0;
}