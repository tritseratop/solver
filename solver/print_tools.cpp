#include "print_tools.h"

using namespace std;

ostream& operator<< (ostream& os, vector<double>& v) {
    bool first = true;
    os << "[" << setprecision(3);
    for (const double& x : v) {
        if (!first) {
            os << ", ";
        }
        first = false;
        os << setw(4) << x;
    }
    os << "]";
    return os;
}

void PrintTable(vector<double>& X, vector<double>& Y) {
    const int prec = 3;
    const int width = 5;
    for (int i = 0; i < static_cast<int>(width * 2 + 3); ++i) {
        cout << '-';
    }
    cout << setprecision(prec) << endl;
    cout << '|' << setfill('_') << setw(width) << 'X' << '|' << setw(width) << 'Y' << '|' << endl;
    cout << setfill(' ');
    for (int i = 0; i < static_cast<int>(X.size()); ++i) {
        cout << '|' << setw(width) << X[i] << '|' << setw(width) << Y[i] << '|' << endl;
    }
    for (int i = 0; i < static_cast<int>(width * 2 + 3); ++i) {
        cout << '-';
    }
    cout << endl;
}

