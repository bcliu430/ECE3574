
class Base
{
public:
  int x;
  virtual void doit(){};
  
private:
  float y;
};

class Derived: public Base
{
public:
  int getX(){ return x; };

  bool doit();
};

int main()
{
  Derived d;
  d.getX();
  d.x = 1;
  
  return 0;
}
