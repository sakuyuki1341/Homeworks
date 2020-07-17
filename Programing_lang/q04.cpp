class Complex {
double r, i;
public:
Complex (double a = 0.0, double b = 0.0) 
 { r=a; i=b; };
Complex(const Complex& c);           //  (P)
void operator=(const Complex& c)      //  (Q)
Complex operator +(const Complex& a); //  (R)          
};  
int main() {
Complex x(1.0, 2.0), y(3.0);  //  (S)
Complex z1,z2,z3=x;        //  (T)
z 1= x + y;　　             //  (U)
z 2= x + 3.0;　　           //  (V)
z 3= 7.0 + y;　　           //  (W)
return 0;
}

