// Code your design here.
// Uncomment the next line for SystemC modules.
#include <systemc>
using namespace std;
using namespace sc_core;
using namespace sc_dt;
SC_MODULE(SM1)
{
  	sc_port<sc_signal_out_if<int> > p;
  	SC_CTOR(SM1)
    {
      	SC_THREAD(writer);
    }
  	void writer()
    {
      	int data = 1;
      while(true)
      {
      		p->write(data++);
       		 wait(1,SC_SEC);
      }
    }
};
SC_MODULE(SM2)
{
  	sc_port<sc_signal_in_if<int> > p;
  	SC_CTOR(SM2)
    {
      	SC_THREAD(reader);
      	sensitive<<p;
      	dont_initialize();
    }
  	void reader()
    {
      	while(true)
        {
      		cout<<"Reader thread :val::"<<p->read()<<endl;
          	wait();
        }
    }
};
SC_MODULE(M1)
{
  	sc_port<sc_signal_out_if<int> > p;
  	SM1 sub1;
  	SC_CTOR(M1):sub1("SubSM1")
    {
      	sub1.p(p);
    }
};
SC_MODULE(M2)
{
  	sc_port<sc_signal_in_if<int> > p;
  	SM2 sub2;
  	SC_CTOR(M2):sub2("SubSM2")
    {
      	sub2.p(p);
    }
};
int sc_main(int , char*[])
{
  	M1 obj1("m1");
  	M2 obj2("m2");
  	sc_signal<int> s;
  	obj1.p(s);
  	obj2.p(s);
  	sc_start(10,SC_SEC);
  	cout<<"delta cycle:"<<sc_delta_count()<<endl;
  	return 0;
}
  
