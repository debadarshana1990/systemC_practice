// Code your design here.
// Uncomment the next line for SystemC modules.
 #include <systemc>
using namespace sc_core;
using namespace std;
using namespace sc_dt;
SC_MODULE(SIG)
{
  	sc_signal<int> cnt_sig;
  	void sig_write();
	void sig_read();
  	SC_CTOR(SIG)
  	{
      	SC_THREAD(sig_write);
		SC_THREAD(sig_read);
    }
};
void SIG::sig_write()
{
  
 	
  	cnt_sig.write(10);
	cnt_sig.write(20);
  	cout<<"count signal:"<<cnt_sig<<endl;

  
}
void SIG::sig_read()
{
  
 	wait(SC_ZERO_TIME);
  	
  	cout<<"count signal:"<<cnt_sig.read()<<endl;

  
}
  
int sc_main(int, char *[])
{
  	SIG obj("SIG");

  	sc_start();
	cout<<"delta cycle:"<<sc_delta_count()<<endl;
  
	
  return 0;
}
