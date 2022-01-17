#include <bits/stdc++.h>
using namespace std;
const int SLICE = 2;
const int PRI = 50;
const int maxn = 5;
struct PCB {
    string name;
    int pri;
    int cputime, needtime, count, round;
    mutable char state;
    friend istream& operator>>(istream& in, PCB& x) {  //输入与初始化每个进程控制块
        in >> x.name >> x.needtime;
        x.cputime = 0;
        x.count = 0;
        x.round = x.needtime / SLICE + !!(x.needtime % SLICE);
        x.pri = PRI - x.needtime;
        x.state = 'W';
        return in;
    }
    bool run() {  //进程控制块运行
        int slice = min(SLICE, needtime);
        pri -= 3;
        cputime += slice;
        needtime -= slice;
        count++;
        if (needtime <= 0) {
            state = 'F';
            return 1;
        } else {
            state = 'W';
        }
        return 0;
    }
    void print1() const {
        cout << name << "\t"
             << cputime << "\t"
             << needtime << "\t"
             << count << "\t"
             << round << "\t"
             << state << endl;
    }
    void print2() const {
        cout << name << "\t"
             << cputime << "\t"
             << needtime << "\t"
             << count << "\t"
             << pri << "\t"
             << state << endl;
    }
    bool operator<(const PCB& y) const {
        if (pri == y.pri) return name < y.name;
        return pri > y.pri;
    }
};
class Solution {
public:
    virtual void run() = 0;
    virtual void init() = 0;
    ~Solution() {}
};
class TimeSliceRotation : public Solution {
    list<PCB> runtime;  //就绪及运行队列
    list<PCB> endwork;  //完成队列
    void show() {       //输出当前状态
        cout << "Name  cputime needtime count  round  state" << endl;
        for (PCB& x : runtime) {
            x.print1();
        }
        for (PCB& x : endwork) {
            x.print1();
        }
        cout << "Ready queue:";
        for (PCB& x : runtime) {
            if (x.state == 'R') continue;
            cout << x.name << " ";
        }
        cout << endl;
        cout << "Completed queue:";
        for (PCB& x : endwork) {
            cout << x.name << " ";
        }
        cout << "\n"
             << endl;
    }

public:
    TimeSliceRotation() = default;
    void init() {  //初始化
        PCB tmp;
        for (int i = 0; i < 5; i++) {
            cin >> tmp;
            runtime.push_back(tmp);
        }
    }
    void run() {  //运行
        PCB tmp;
        while (!runtime.empty()) {
            runtime.begin()->state = 'R';
            show();
            tmp = runtime.front();
            runtime.pop_front();
            if (tmp.run()) {
                endwork.push_back(tmp);
            } else {
                runtime.push_back(tmp);
            }
        }
        show();
    }
};

class PriorityNumberAlgorithm : public Solution {
    multiset<PCB> runtime;
    list<PCB> endwork;
    void show() {
        cout << "Name  cputime needtime count   pri   state" << endl;
        for (const PCB& x : runtime) {
            x.print2();
        }
        for (PCB& x : endwork) {
            x.print2();
        }
        cout << "Ready queue:";
        for (const PCB& x : runtime) {
            if (x.state == 'R') continue;
            cout << x.name << " ";
        }
        cout << endl;
        cout << "Completed queue:";
        for (PCB& x : endwork) {
            cout << x.name << " ";
        }
        cout << "\n\n";
    }

public:
    PriorityNumberAlgorithm() = default;
    void init() {
        PCB tmp;
        for (int i = 0; i < 5; i++) {
            cin >> tmp;
            runtime.insert(tmp);
        }
    }
    void run() {
        PCB tmp;
        while (!runtime.empty()) {
            runtime.begin()->state = 'R';
            tmp = *runtime.begin();
            show();
            runtime.erase(runtime.begin());
            if (tmp.run()) {
                endwork.push_back(tmp);
            } else {
                runtime.insert(tmp);
            }
        }
        show();
    }
};
int main() {
    int T;
    cin >> T;
    Solution* t;
    if (T == 1) {
        t = new PriorityNumberAlgorithm();
    } else {
        t = new TimeSliceRotation();
    }
    t->init();
    t->run();
}
/*
a1    3
a2    2
a3    4
a4    2
a5    1
*/