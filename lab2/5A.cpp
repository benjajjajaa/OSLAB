#include <iostream>
using namespace std;

int main() {
    int ms, bs, nob, ef, n;
    int mp[10], tif = 0;
    int i, p = 0;

    cout << "Enter total memory (Bytes): ";
    cin >> ms;

    cout << "Enter block size (Bytes): ";
    cin >> bs;

    nob = ms / bs;
    ef = ms - nob * bs;

    cout << "Enter number of processes: ";
    cin >> n;

    for(i = 0; i < n; i++) {
        cout << "Enter memory for process " << i+1 << ": ";
        cin >> mp[i];
    }

    cout << "\nBlocks available: " << nob << endl;
    cout << "\nPROCESS\tMEMORY\tALLOCATED\tINTERNAL FRAG\n";

    for(i = 0; i < n && p < nob; i++) {
        cout << i+1 << "\t" << mp[i];

        if(mp[i] > bs) {
            cout << "\tNO\t\t---\n";
        } else {
            cout << "\tYES\t\t" << bs - mp[i] << endl;
            tif += (bs - mp[i]);
            p++;
        }
    }

    if(i < n)
        cout << "\nMemory Full, remaining processes not allocated\n";

    cout << "\nTotal Internal Fragmentation: " << tif;
    cout << "\nTotal External Fragmentation: " << ef;

    return 0;
}