#include <iostream>
using namespace std;

class Base {
 public:
  void f(int i) { cout << "Base::f(int = " << i << ")" << endl; }
  virtual void f(double d)  { cout << "Base::f(double = " << d << ")" << endl; }
  virtual void g(int i = 10 ) { cout << "Base::g(int = " << i << ")" << endl; }
};
class Derived: public Base {
  public:
   void f(int i) { cout << "Derived::f(int = " << i << ")" << endl; }
   void f(double d) { cout << "Derived::f(double = "<< d << ")" << endl;}
   void g(int i = 20 ) {cout << "Derived::g(int = " << i << ")" << endl;}
};
int main() {
     Base  b;
     Derived d;
     Base*  pb = new Derived;
     b.f(1.0);  d.f(2.0);
     pb->f(3);  pb->f(4.0);  pb->g();
}

