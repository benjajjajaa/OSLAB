#include <iostream>
using namespace std;

class MFT {
private:
    int ms, bs, nob, ef, n;
    int mp[10], tif;

public:
    void input() {
        cout << "Enter total memory: ";
        cin >> ms;

        cout << "Enter block size: ";
        cin >> bs;

        nob = ms / bs;
        ef = ms - nob * bs;

        cout << "Enter number of processes: ";
        cin >> n;

        for(int i = 0; i < n; i++) {
            cout << "Process " << i+1 << ": ";
            cin >> mp[i];
        }
    }

    void allocate() {
        int p = 0;
        tif = 0;

        cout << "\nPROCESS\tMEMORY\tALLOCATED\tINTERNAL FRAG\n";

        for(int i = 0; i < n && p < nob; i++) {
            cout << i+1 << "\t" << mp[i];

            if(mp[i] > bs)
                cout << "\tNO\t\t---\n";
            else {
                cout << "\tYES\t\t" << bs - mp[i] << endl;
                tif += bs - mp[i];
                p++;
            }
        }

        cout << "\nInternal Fragmentation: " << tif;
        cout << "\nExternal Fragmentation: " << ef;
    }
};

int main() {
    MFT obj;
    obj.input();
    obj.allocate();
    return 0;
}