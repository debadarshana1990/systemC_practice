// Code your design here.
// Uncomment the next line for SystemC modules.
#include <systemc>
#include <vector>
using namespace sc_core;
using namespace sc_dt;
using namespace std;

using std::vector;
SC_MODULE(RESOLVED_SIGNAL) 
{

  	sc_signal_resolved rv;

  	vector<sc_logic> levels;

  	SC_CTOR(RESOLVED_SIGNAL) : levels(vector<sc_logic>{sc_logic_0, sc_logic_1, sc_logic_Z, sc_logic_X})
    {
    	SC_THREAD(writer1);
    	SC_THREAD(writer2);
    	SC_THREAD(consumer);
  	}
  	void writer1() {
    int idx = 0;
  //  while (true) 
    {

      rv.write(sc_logic(0));

    }
  }
  void writer2() {
    int idx = 0;
  //  while (true)
    {


      rv.write(sc_logic(1));

    }
  }
  void consumer() {

    int idx = 0;
    wait(SC_ZERO_TIME);
 //   while (true) 
    {

      std::cout << " " << rv.read() << endl;

    }
  }
};
int sc_main(int, char*[]) 
{
	RESOLVED_SIGNAL obj("test");
  sc_start();
  cout<<"delta cycle:"<<sc_delta_count()<<endl;
  return 0;
}
