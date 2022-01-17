#include <bits/stdc++.h>
using namespace std;

namespace Best {
    struct zone {
        int address, end, size;
        zone(int a, int e) : address(a), end(e), size(e - a + 1) {}
        zone() : zone(0, 0) {}
        bool operator<(const zone& b) const;
    };
    bool zone::operator<(const zone& b) const {
        if (size == b.size) return address < b.address;
        return size < b.size;
    }
    struct Fit {
        set<zone> unused;
        Fit() {
            unused.insert(zone(0, 32766));
        }
        void print() {
            printf("%10s%10s%10s%10s\n", "Index", "Address", "End", "Size");
            int i = 0;
            for (const zone& p : unused) {
                printf("%10d%10d%10d%10d\n", ++i, p.address, p.end, p.size);
            }
        }
        void assign(int n) {
            auto it = unused.lower_bound(zone(0, n - 1));
            if (it == unused.end()) {
                cerr << "Too large application!" << endl;
                return;
            }
            zone tmp = *it;
            unused.erase(it);
            printf("SUCCESS!!!    ADDRESS=%d\n", tmp.end - n + 1);
            if (tmp.address != tmp.end - n)
                unused.insert(zone(tmp.address, tmp.end - n));
        }
        void accept(int adr, int n) {
            int ed = adr + n - 1;
            auto S = unused.end();
            for (auto i = unused.begin(); i != unused.end(); i++) {
                if (i->end == adr - 1) S = i;
            }
            if (S != unused.end()) {
                adr = S->address;
                unused.erase(S);
            }
            auto E = unused.end();
            for (auto i = unused.begin(); i != unused.end(); i++) {
                if (i->address == ed + 1) E = i;
            }
            if (E != unused.end()) {
                ed = E->end;
                unused.erase(E);
            }
            unused.insert(zone(adr, ed));
        }
    };
}
namespace First {
    struct zone {
        int address, end, size;
        zone(int a, int e) : address(a), end(e), size(e - a + 1) {}
        zone() : zone(0, 0) {}
        bool operator<(const zone& b) const;
    };
    bool zone::operator<(const zone& b) const {
        return address < b.address;
    }
    struct Fit {
        set<zone> unused;
        Fit() {
            unused.insert(zone(0, 32766));
        }
        void print() {
            printf("%10s%10s%10s%10s\n", "Index", "Address", "End", "Size");
            int i = 0;
            for (const zone& p : unused) {
                printf("%10d%10d%10d%10d\n", ++i, p.address, p.end, p.size);
            }
        }
        void assign(int n) {
            auto it = unused.begin();
            for (; it != unused.end(); it++) {
                if (it->size >= n) break;
            }
            if (it == unused.end()) {
                cerr << "Too large application!" << endl;
                return;
            }
            zone tmp = *it;
            unused.erase(it);
            printf("SUCCESS!!!    ADDRESS=%d\n", tmp.end - n + 1);
            if (tmp.address != tmp.end - n)
                unused.insert(zone(tmp.address, tmp.end - n));
        }
        void accept(int adr, int n) {
            int ed = adr + n - 1;
            auto S = unused.end();
            for (auto i = unused.begin(); i != unused.end(); i++) {
                if (i->end == adr - 1) S = i;
            }
            if (S != unused.end()) {
                adr = S->address;
                unused.erase(S);
            }
            auto E = unused.end();
            for (auto i = unused.begin(); i != unused.end(); i++) {
                if (i->address == ed + 1) E = i;
            }
            if (E != unused.end()) {
                ed = E->end;
                unused.erase(E);
            }
            unused.insert(zone(adr, ed));
        }
    };
}

int main() {
    printf("input the way (best or first):\n");
    string opt;
    int x, y;
    cin >> opt;
    if (opt == "best") {
        using namespace Best;
        Fit tmp;
        while (1) {
            tmp.print();
            cout << "Assign or Accept:";
            cin >> opt;
            if (opt == "ac") {
                cout << "Input adr and size:";
                cin >> x >> y;
                tmp.accept(x, y);
            } else if (opt == "as") {
                cout << "input APPLACATION: ";
                cin >> x;
                tmp.assign(x);
            } else if (opt == "q")
                exit(0);
        }
    } else {
        using namespace First;
        Fit tmp;
        while (1) {
            tmp.print();
            cout << "Assign or Accept:";
            cin >> opt;
            if (opt == "ac") {
                cout << "Input adr and size:";
                cin >> x >> y;
                tmp.accept(x, y);
            } else if (opt == "as") {
                cout << "input APPLACATION: ";
                cin >> x;
                tmp.assign(x);
            } else if (opt == "q")
                exit(0);
        }
    }
}
/*
best
as
30000
ac
3000 2767
ac
8000 4000
ac
2767 10
as
3000
as
3000
*/