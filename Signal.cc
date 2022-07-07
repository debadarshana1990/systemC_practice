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
  	SC_CTOR(SIG)
  	{
      	SC_THREAD(sig_write);
    }
};
void SIG::sig_write()
{
  
 	
  	cnt_sig.write(10);
  	cout<<"count signal:"<<cnt_sig<<endl;
 	 wait(SC_ZERO_TIME);
	cout<<"count signal:"<<cnt_sig<<endl;
  
}
  
int sc_main(int, char *[])
{
  	SIG obj("SIG");

  	sc_start();
	cout<<"delta cycle:"<<sc_delta_count()<<endl;
  
	
  return 0;
}
