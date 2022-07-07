 #include <systemc>
using namespace std;
using namespace sc_core;
SC_MODULE(SENSTIVITY)
{
  sc_event e1;
  SC_CTOR(SENSTIVITY)
  {
    SC_THREAD(eventTrig);
	SC_THREAD(static_sen);
    sensitive<<e1;
    
  }
  void eventTrig()
  {
    wait(SC_ZERO_TIME);
	e1.notify();
  //  wait(SC_ZERO_TIME);
      
  }
  void static_sen()
  {
	cout<<"Before wait:"<<endl;
  //  wait(e1);
    cout<<"after wait e1:"<<endl;
    wait();
cout<<"after wait :"<<endl;
      
  }
};
int sc_main(int , char *[])
{
  SENSTIVITY obj("nexttrig");
  sc_start(10,SC_SEC);
  return 0;
}
    
