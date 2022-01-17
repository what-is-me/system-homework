#include <bits/stdc++.h>
struct Jobs {
    std::string name;
    std::vector<int> Allocation;
    std::vector<int> Max;
    std::vector<int> Need;
    void init(int n) {
        Max = Allocation = Need = std::vector<int>(n, 0);
        std::cin >> name;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        for (int i = 0; i < n; i++) {
            std::cin >> Max[i];
        }
        for (int i = 0; i < n; i++) {
            std::cin >> Allocation[i];
            Need[i] = Max[i] - Allocation[i];
        }
    }
};
std::vector<int> operator+(const std::vector<int>& x, const std::vector<int>& y) {
    std::vector<int> ret(x);
    int n = ret.size();
    for (int i = 0; i < n; i++) {
        ret[i] += y[i];
    }
    return ret;
}
std::vector<int> operator-(const std::vector<int>& x, const std::vector<int>& y) {
    std::vector<int> ret(x);
    int n = ret.size();
    for (int i = 0; i < n; i++) {
        ret[i] -= y[i];
    }
    return ret;
}
bool operator<(const std::vector<int>& x, const std::vector<int>& y) {
    int n = x.size();
    for (int i = 0; i < n; i++) {
        if (x[i] > y[i]) return false;
        if (x[i] < y[i]) return true;
    }
    return false;
}
std::basic_ostream<char>& operator<<(std::basic_ostream<char>& out, const std::vector<int>& x) {
    int n = x.size();
    for (int i = 0; i < n - 1; i++) {
        out << x[i] << ", ";
    }
    if (n) out << x.back() << "    ";
    return out;
}
struct Matrix {
    int n, m;
    std::vector<int> Available;
    std::vector<Jobs> J;
    std::unordered_map<std::string, int> mp;
    std::stringstream Log;
    void init() {
        std::cout << "Input the type of resource and number of customer:" << std::endl;
        std::cin >> n >> m;
        std::cout << "Input the amount of resource (maximum , allocated) of each customer:" << std::endl;
        Available = std::vector<int>(n, 0);
        J = std::vector<Jobs>(m);
        for (int i = 0; i < m; i++) {
            J[i].init(n);
            mp[J[i].name] = i;
        }
        std::cout << "Input the amout of resources(available):" << std::endl;
        for (int i = 0; i < n; i++) {
            std::cin >> Available[i];
        }
    }
    bool check() {
        std::vector<int> Work;
        std::vector<int> WA = Available;
        std::queue<Jobs> q;
        for (const auto& i : J) q.push(i);
        Jobs tmp;
        int searched = 0;
        Log << "Name    Work      Need     Allocation Work+Allocation    Finish" << std::endl;
        while (!q.empty()) {
            if (searched >= q.size()) {
                return 0;
            }
            tmp = q.front();
            q.pop();
            Work = WA;
            if (!(Work < tmp.Need)) {
                WA = Work + tmp.Allocation;
                Log << tmp.name << "    " << Work << tmp.Need << tmp.Allocation << WA << "  T" << std::endl;
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
            std::cout << Log.str() << "SYSTEM SECURITY!!!" << std::endl;
        } else {
            std::cout << "SYSTEM INSECURITY!!!" << std::endl;
        }
    }
    void checkRequest() {
        Log.str("");
        std::cout << "Please input the customer’s name and request:" << std::endl;
        std::string name;
        std::vector<int> test(n);
        std::cin >> name;
        transform(name.begin(), name.end(), name.begin(), ::tolower);
        if (!mp.count(name)) {
            std::cerr << "Unable To Find The Job!!!" << std::endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            std::cin >> test[i];
        }
        if ((J[mp[name]].Need < test) && (Available < test)) {
            std::cout << "SYSTEM INSUFFICIENT!!!\nCUSTOMER " + name + " CAN NOT OBTAIN RESOURCES IMMEDIATELY." << std::endl;
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
            std::cout << Log.str() << "SYSTEM SUFFICIENT!!!\nCUSTOMER " + name + " CAN OBTAIN RESOURCES IMMEDIATELY." << std::endl;
        } else {
            std::cout << "SYSTEM INSUFFICIENT!!!\nCUSTOMER " + name + " CAN NOT OBTAIN RESOURCES IMMEDIATELY." << std::endl;
        }
    }
};
int main() {
    char opt;
    Matrix Sys;
    Sys.init();
    while (1) {
        std::cout << "1.judge the system security\n2.judge the request security\n3.quit" << std::endl;
        std::cin >> opt;
        switch (opt) {
            case '1':
                Sys.chechSystem();
                break;
            case '2':
                Sys.checkRequest();
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