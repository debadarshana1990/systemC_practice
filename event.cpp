#include <systemc>
using namespace sc_core;
SC_MODULE(EVENT) 
{
  sc_event e;
  SC_CTOR(EVENT) 
  {
    SC_THREAD(trigger);
    SC_THREAD(catcher);
  }
  void trigger() 
  {
    while (true) 
    {
      e.notify(2, SC_SEC);
      wait(2, SC_SEC);
    }
  }
  void catcher() 
  {
    while (true) 
    {
      wait(e);
      std::cout << "Event cateched at " << sc_time_stamp() << std::endl;
    }
  }
};
int sc_main(int, char*[])
 {
  EVENT event("event");
  sc_start(8, SC_SEC);
  return 0;
}
