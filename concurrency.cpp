// Code your design here.
// Uncomment the next line for SystemC modules.
#include <systemc>
#include <iostream>
using namespace sc_core;
using namespace std;
SC_MODULE(CONCOR)
{
  SC_CTOR(CONCOR)
  {
    SC_THREAD(thread1);
    SC_THREAD(thread2);
  }
  void thread1(void)
  {
    while(true)
    {
      cout<<sc_time_stamp()<<":thread1"<<endl;
      wait(2,SC_SEC);
    }
  }
  void thread2(void)
  {
    while(true)
    {
      cout<<"\t"<<sc_time_stamp()<<":thread2"<<endl;
      wait(3,SC_SEC);
    }
  }
};
int sc_main(int argc, char* argv[])
{
  CONCOR con("con");
  sc_start(10,SC_SEC);
  return 0;
}
