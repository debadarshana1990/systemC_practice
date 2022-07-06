// Code your design here.
// Uncomment the next line for SystemC modules.
 #include <systemc>
using namespace sc_core;
using namespace std;
using namespace sc_dt;
SC_MODULE(EVENT)
{
  sc_event event1,event2;

  SC_CTOR(EVENT)
  {
    SC_THREAD(trigger1);
	SC_THREAD(trigger2);
    SC_THREAD(responder);

  }
  void trigger1()
  {
      	sc_time  t_trig_delay(10,SC_SEC);
 
		sc_time  t_delay(2,SC_SEC);

  //  while(true)
    {

      event1.notify(t_trig_delay);
   
      wait(t_delay);
    }
  }
    void trigger2()
  {
      	sc_time  t_trig_delay(5,SC_SEC);
 
		sc_time  t_delay(2,SC_SEC);

  //  while(true)
    {

      event2.notify(t_trig_delay);
   
      wait(t_delay);
    }
  }
  void responder()
  {
    while(true)
    {
      sc_time timeout(3,SC_SEC);
      wait(timeout,event1|event2);
      cout<<"catched event:"<<sc_time_stamp()<<endl;
    }
  }
      


};
int sc_main(int, char *[])
{
  EVENT obj("event");

  sc_start(20,SC_SEC);
  
	
  return 0;
}
