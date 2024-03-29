#include <iostream>

// forward declare State type
class State;

// machine has-a state
class Machine
{
public:
  Machine();

  void input1(bool in);
  bool getOutput1();
  void next();

private:
    class State *current;
};

// a state has outputs 
class State
{
public:
  virtual void on(Machine *m)
  {
    cout << "   already ON\n";
  }
  virtual void off(Machine *m)
  {
    cout << "   already OFF\n";
  }
};

void Machine::on()
{
  current->on(this);
}

void Machine::off()
{
  current->off(this);
}

class ON: public State
{
public:
  ON()
  {
    cout << "   ON-ctor ";
  };
  ~ON()
  {
    cout << "   dtor-ON\n";
  };
  void off(Machine *m);
};

class OFF: public State
{
public:
  OFF()
  {
    cout << "   OFF-ctor ";
  };
  ~OFF()
  {
    cout << "   dtor-OFF\n";
  };
  void on(Machine *m)
  {
    cout << "   going from OFF to ON";
    m->setCurrent(new ON());
    delete this;
  }
};

void ON::off(Machine *m)
{
  cout << "   going from ON to OFF";
  m->setCurrent(new OFF());
  delete this;
}

Machine::Machine()
{
  current = new OFF();
  cout << '\n';
}

int main()
{
  void(Machine:: *ptrs[])() =
    {
      Machine::off, Machine::on
    };
  Machine fsm;
  int num;
  while (1)
    {
      cout << "Enter 0/1: ";
      cin >> num;
      (fsm. *ptrs[num])();
    }
}
