 #include <systemc>
using namespace sc_core;
using namespace std;
using namespace sc_dt;
SC_MODULE(EVENT)
{
  sc_event event;

  SC_CTOR(EVENT)
  {
    SC_THREAD(trigger);
    SC_THREAD(responder);

  }
  void trigger()
  {
      	sc_time  t_trig_delay(1,SC_SEC);
 
	sc_time  t_delay(2,SC_SEC);

 //   while(true)
    {
      event.notify(SC_ZERO_TIME);

    }
  }
  void responder()
  {
    while(true)
    {
      wait(event);
      cout<<"catched event:"<<sc_time_stamp()<<endl;
    }
  }
      


};
int sc_main(int, char *[])
{
  EVENT obj("event");

  sc_start();
cout<<"delta cycle:"<<sc_delta_count()<<endl;
  
	
  return 0;
