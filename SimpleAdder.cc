// Code your design here.
// Uncomment the next line for SystemC modules.
#include <systemc>
using namespace std;
using namespace sc_core;
using namespace sc_dt;
/* Adder Module */
SC_MODULE(ADDER)
{
  	/* Input port to read data */
  	sc_port<sc_signal_in_if<int> > in_a;
  	sc_port<sc_signal_in_if<int> > in_b;
  	/* Output port */
  	sc_port<sc_signal_out_if<int> > out;
  	/* clk */
  	sc_in<bool> clk;
  	/* constructor */
  	SC_CTOR(ADDER)
    {
      	SC_THREAD(add_func);
      	sensitive<<clk.pos();
      	dont_initialize();
    }
  	void add_func()
    {
      	while(true)
        {
          	int a = in_a->read();
          	int b = in_b->read();
          	int res = a + b;
          	out->write(res);
          	wait();
        }
    }
};
SC_MODULE(DATA_PROVIDER)
{
  	/* Input port to read data */
  	sc_port<sc_signal_out_if<int> > out_a;
  	sc_port<sc_signal_out_if<int> > out_b;
  	/* Output port */
  	sc_port<sc_signal_in_if<int> > in_res;
  	/* clk */
  	sc_in<bool> clk;
  	/* constructor */
  	SC_CTOR(DATA_PROVIDER)
    {
      	SC_THREAD(data_gen);
      	sensitive<<clk.neg();
		dont_initialize();
    }
  	void data_gen()
    {
      	while(true)
        {
			int a = rand()%10;
          	int b = rand()%10;
          	out_a->write(a);
          	out_b->write(b);
          	cout<<"written a:"<<a<<"  b:"<<b<<endl;
          	cout<<" Read data ::"<<in_res->read()<<endl;
          	wait();
        }
    }
};
SC_MODULE(CLOCK)
{
  	sc_out<bool> clk_tb;
	sc_out<bool> clk_adder;
  	SC_CTOR(CLOCK)
    {
      SC_THREAD(gen_clk);
    }
  	void gen_clk()
    {
       	bool pulse = true;
      	while(true)
        {
          	pulse = !pulse;
          	clk_tb->write(pulse);
          	clk_adder->write(pulse);
          	wait(1,SC_SEC);
        }
    }
};
int sc_main(int , char *[])
{
 	ADDER obj("Adder");
  	DATA_PROVIDER tb("TestBench");
  	CLOCK pulse("Clock");
  	/* Bind port->if->channel*/
  	sc_signal<int> in_a;
  	sc_signal<int> in_b;
  	obj.in_a(in_a);
  	tb.out_a(in_a);
    obj.in_b(in_b);
  	tb.out_b(in_b);
  
  	sc_signal<int> res;
  	obj.out(res);
  	tb.in_res(res);
  	
  	sc_signal<bool> clk_adder;
  	obj.clk(clk_adder);
  	pulse.clk_adder(clk_adder);
  
  	sc_signal<bool> clk_tb;
  	tb.clk(clk_tb);
  	pulse.clk_tb(clk_tb);
  
  	sc_start(10,SC_SEC);
	cout<<"delta cycle:"<<sc_delta_count()<<endl;
  	return 0;
}
  
