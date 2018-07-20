#include <cstdlib>
#include <iostream>
#include <string>
#include <list>
#include <typeinfo>

#include <tr1/functional>
#include <tr1/memory>

using namespace std;

shared_ptr<void> ptr;

shared_ptr<void> get()
{
    return ptr;
}
void set(shared_ptr<void> p)
{
    ptr = p;
}
int main(int argc, char **argv)
{
    string *a = new string("1");
    shared_ptr<void> p1(nullptr);
    //p1.reset(a);
    //set(p1);
    ptr.reset(a);
    cout << "count: " << ptr.use_count() << endl;
    //ptr.reset();
    shared_ptr<void> p = get();
    if(p){
        cout << "ok" << endl;
    } else {
        cout << "no" << endl;
    }
//    cout << "count: " << p.use_count() << endl;
//    ptr.reset();
    cout << "count: " << ptr.use_count() << endl;
//    cout << "count: " << p.use_count() << endl;
    return 0;
}
