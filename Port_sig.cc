#include <systemc>
using namespace std;
using namespace sc_core;
using namespace sc_dt;
SC_MODULE(M1)
{
 	sc_port<sc_signal_in_if<int> > in_p;
  	SC_CTOR(M1)
    {
      	SC_THREAD(reader);
		sensitive << in_p;
    	dont_initialize();
    }
  	void reader()
    {
      	cout<<"Read:"<<in_p->read()<<endl;
    }
};
SC_MODULE(M2)
{
 	sc_port<sc_signal_out_if<int> > out_p;
  	SC_CTOR(M2)
    {
      	SC_THREAD(writer);
      
    }
  	void writer()
    {
      	out_p->write(5);
    }
};
int sc_main(int , char *[])
{
  	M1 obj1("m1");
  	M2 obj2("m2");
  	sc_signal<int> sig;
  	obj1.in_p(sig);
  	obj2.out_p(sig);
  	sc_start();
	cout<<"delta cycle:"<<sc_delta_count()<<endl;
  	return 0;
}
