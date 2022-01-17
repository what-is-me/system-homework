#include <bits/stdc++.h>
using namespace std;
template <typename T>
struct Jobs {
    string name;
    vector<T> Allocation;
    vector<T> Max;
    vector<T> Need;
    void init(int n) {
        Max = Allocation = Need = vector<T>(n, 0);
        cin >> name;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        for (int i = 0; i < n; i++) {
            cin >> Max[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> Allocation[i];
            Need[i] = Max[i] - Allocation[i];
        }
    }
};
template <typename T>
vector<T> operator+(const vector<T>& x, const vector<T>& y) {
    vector<T> ret(x);
    int n = ret.size();
    for (int i = 0; i < n; i++) {
        ret[i] += y[i];
    }
    return ret;
}
template <typename T>
vector<T> operator-(const vector<T>& x, const vector<T>& y) {
    vector<T> ret(x);
    int n = ret.size();
    for (int i = 0; i < n; i++) {
        ret[i] -= y[i];
    }
    return ret;
}
template <typename T>
bool operator<(const vector<T>& x, const vector<T>& y) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        if (x[i] > y[i]) return 0;
        if (x[i] < y[i]) return 1;
    }
    return 0;
}
template <typename T>
basic_ostream<char>& operator<<(basic_ostream<char>& out, const vector<T>& x) {
    int n = x.size();
    for (int i = 0; i < n - 1; i++) {
        out << x[i] << ", ";
    }
    if (n) out << x.back() << "    ";
    return out;
}
template <typename T>
struct Matrix {
    int n, m;
    vector<T> Available;
    vector<Jobs<T>> J;
    unordered_map<string, int> mp;
    stringstream Log;
    void init() {
        cout << "Input the type of resource and number of customer:" << endl;
        cin >> n >> m;
        cout << "Input the amount of resource (maximum , allocated) of each customer:" << endl;
        Available = vector<T>(n, 0);
        J = vector<Jobs<T>>(m);
        for (int i = 0; i < m; i++) {
            J[i].init(n);
            mp[J[i].name] = i;
        }
        cout << "Input the amout of resources(available):" << endl;
        for (int i = 0; i < n; i++) {
            cin >> Available[i];
        }
    }
    bool check() {
        vector<T> Work;
        vector<T> WA = Available;
        queue<Jobs<T>> q;
        for (const auto& i : J) q.push(i);
        Jobs<T> tmp;
        int searched = 0;
        Log << "Name    Work      Need     Allocation Work+Allocation    Finish" << endl;
        while (!q.empty()) {
            if (searched >= q.size()) {
                return 0;
            }
            tmp = q.front();
            q.pop();
            Work = WA;
            if (!(Work < tmp.Need)) {
                WA = Work + tmp.Allocation;
                Log << tmp.name << "    " << Work << tmp.Need << tmp.Allocation << WA << "  T" << endl;
                searched = 0;
            } else {
                q.push(tmp);
                searched++;
            }
        }
        return 1;
    }
    void chechSystem() {
        Log.str("");
        if (check()) {
            cout << Log.str() << "SYSTEM SECURITY!!!" << endl;
        } else {
            cout << "SYSTEM INSECURITY!!!" << endl;
        }
    }
    void checkRequest() {
        Log.str("");
        cout << "Please input the customer’s name and request:" << endl;
        string name;
        vector<T> test(n);
        cin >> name;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (!mp.count(name)) {
            cerr << "Unable To Find The Job!!!" << endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            cin >> test[i];
        }
        if ((J[mp[name]].Need < test) && (Available < test)) {
            cout << "SYSTEM INSUFFICIENT!!!\nCUSTOMER " + name + " CAN NOT OBTAIN RESOURCES IMMEDIATELY." << endl;
            return;
        }
        J[mp[name]].Need = J[mp[name]].Need - test;
        J[mp[name]].Allocation = J[mp[name]].Allocation + test;
        Available = Available - test;
        bool chk = check();
        J[mp[name]].Need = J[mp[name]].Need + test;
        J[mp[name]].Allocation = J[mp[name]].Allocation - test;
        Available = Available + test;
        if (chk) {
            cout << Log.str() << "SYSTEM SUFFICIENT!!!\nCUSTOMER " + name + " CAN OBTAIN RESOURCES IMMEDIATELY." << endl;
        } else {
            cout << "SYSTEM INSUFFICIENT!!!\nCUSTOMER " + name + " CAN NOT OBTAIN RESOURCES IMMEDIATELY." << endl;
        }
    }
};
int main() {
    char opt;
    Matrix<int> Sys;
    Sys.init();
    while (1) {
        // system("cls");
        cout << "1.judge the system security\n2.judge the request security\n3.quit" << endl;
        cin >> opt;
        switch (opt) {
            case '1':
                Sys.chechSystem();
                // system("pause");
                break;
            case '2':
                Sys.checkRequest();
                // system("pause");
                break;
            case '3':
                exit(0);
                break;
        }
    }
}
/*
3 5
P0 7 5 3 0 1 0
P1 3 2 2 2 0 0
P2 9 0 2 3 0 2
P3 2 2 2 2 1 1
P4 4 3 3 0 0 2
3 3 2
1
2
p1 1 0 2
2
p4 3 3 0
2
p0 4 4 3
*/