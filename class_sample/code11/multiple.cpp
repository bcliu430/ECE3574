
class Base1 {};
class Base2 {};

class Derived: public Base1, private Base2
{};

int main()
{
  Base1 b1;
  Base2 b2;
  Derived d;
  
  return 0;
}
