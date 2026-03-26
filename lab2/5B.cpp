#include <iostream>
using namespace std;

int main() {
    int ms, mp[10], temp, n = 0;
    char ch = 'y';

    cout << "Enter total memory (Bytes): ";
    cin >> ms;

    temp = ms;

    for(int i = 0; ch == 'y'; i++, n++) {
        cout << "Enter memory for process " << i+1 << ": ";
        cin >> mp[i];

        if(mp[i] <= temp) {
            cout << "Allocated to process " << i+1 << endl;
            temp -= mp[i];
        } else {
            cout << "Memory Full\n";
            break;
        }

        cout << "Continue (y/n): ";
        cin >> ch;
    }

    cout << "\nPROCESS\tMEMORY ALLOCATED\n";
    for(int i = 0; i < n; i++)
        cout << i+1 << "\t" << mp[i] << endl;

    cout << "\nTotal Allocated: " << ms - temp;
    cout << "\nExternal Fragmentation: " << temp;

    return 0;
}