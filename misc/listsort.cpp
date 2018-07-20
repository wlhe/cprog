#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <typeinfo>

using namespace std;

class A
{
  public:
    A() { cout << "A()" << endl; };
    A(int x) { this->x = x; }
    A(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
    ~A() { cout << "～A" << endl; };
    static bool comp1(const A *a, const A *b) { return (a->x > b->x) ? true : false; }
    static bool comp2(const A &a, const A &b) { return (a.y < b.y) ? true : false; }
    int x;
    int y;

    bool operator<(const A &a) const
    {
        cout << "operator < " << endl;
        return (this->x < a.x) ? true : false;
    }
};

int main(int argc, char **argv)
{
    A *a1 = new A(1, 5);
    A *a2 = new A(4, 3);
    A *a3 = new A(2, 6);
    list<A *> la;
    list<A> lb;
    la.push_back(a1);
    la.push_back(a2);
    la.push_back(a3);
    cout << "size la: " << la.size() << endl;
    la.sort(&A::comp1);
    for (auto &i : la) {
        cout << "x: " << i->x << ",y: " << i->y << endl;
    }

    /*
        la.sort(&A::comp2);
        la.sort([](const A *a, const A *b) {return ((a->x < b->x) ? true : false);});
        for(auto i : la){
            cout << "x: " << i->x << ",y: " << i->y << endl;
        }
    */
    //    if(*a1 < *a2){
    //        cout << "*a1 < *a2" << endl;
    //    } else {
    //        cout << "*a1 > *a2" << endl;
    //
    //    }

    //    la.sort();
    //    for(auto &i : la){
    //        i->x = 1;
    //        cout << "x: " << i->x << ",y: " << a2->x << endl;
    //    }

    cout << "size la: " << la.size() << endl;
    return 0;
}
