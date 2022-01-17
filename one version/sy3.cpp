#include <bits/stdc++.h>
using namespace std;

struct Zone {
    int address, end, size;
    function<bool(Zone, Zone)> ls;
    Zone(int a, int e, function<bool(Zone, Zone)> f) : address(a), end(e), size(e - a + 1), ls(f) {}
    Zone(function<bool(Zone, Zone)> f) : Zone(0, 0, f) {}
    bool operator<(const Zone& b) const {
        return ls(*this, b);
    }
};
auto Best = [](const Zone& a, const Zone& b) {
    if (a.size == b.size) return a.address < b.address;
    return a.size < b.size;
};
auto First = [](const Zone& a, const Zone& b) {
    return a.address < b.address;
};
struct Fit {
    function<bool(Zone, Zone)> f;
    set<Zone> unused;
    Fit(function<bool(Zone, Zone)> f) : f(f) {}
    void append(int l, int r) {
        unused.insert(Zone(l, r, f));
    }
    virtual void assign(int n) = 0;
    void print() {
        printf("%10s%10s%10s%10s\n", "Index", "Address", "End", "Size");
        int i = 0;
        for (const Zone& p : unused) {
            printf("%10d%10d%10d%10d\n", ++i, p.address, p.end, p.size);
        }
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
        append(adr, ed);
    }
};
struct BestFit : public Fit {
    BestFit() : Fit(Best) {}
    void assign(int n) {
        auto it = unused.lower_bound(Zone(0, n - 1, Best));
        if (it == unused.end()) {
            cerr << "Too large application!" << endl;
            return;
        }
        const Zone& tmp = *it;
        unused.erase(it);
        printf("SUCCESS!!!    ADDRESS=%d\n", tmp.end - n + 1);
        if (tmp.address != tmp.end - n)
            unused.insert(Zone(tmp.address, tmp.end - n, Best));
    }
};
struct FirstFit : public Fit {
    FirstFit() : Fit(First) {}
    void assign(int n) {
        auto it = unused.begin();
        for (; it != unused.end(); it++) {
            if (it->size >= n) break;
        }
        if (it == unused.end()) {
            cerr << "Too large application!" << endl;
            return;
        }
        const Zone& tmp = *it;
        unused.erase(it);
        printf("SUCCESS!!!    ADDRESS=%d\n", tmp.end - n + 1);
        if (tmp.address != tmp.end - n)
            unused.insert(Zone(tmp.address, tmp.end - n, First));
    }
};
int main() {
    printf("input the way (best or first):\n");
    string opt;
    int x, y;
    cin >> opt;
    Fit* tmp;
    if (opt == "best") {
        tmp = new BestFit();

    } else {
        tmp = new FirstFit();
    }
    while (1) {
        tmp->print();
        cout << "Assign or Accept:";
        cin >> opt;
        if (opt == "ac") {
            cout << "Input adr and size:";
            cin >> x >> y;
            tmp->accept(x, y);
        } else if (opt == "as") {
            cout << "input APPLACATION: ";
            cin >> x;
            tmp->assign(x);
        } else if (opt == "q")
            exit(0);
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