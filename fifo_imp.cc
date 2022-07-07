#include <systemc>
using namespace sc_core;
using namespace sc_dt;
using namespace std;
typedef sc_int<32> sc_int32;
SC_MODULE(FIFO)
{
  public :
  	sc_fifo<sc_int<32>> fifo;
  	void producer();
  	void consumer();
  	SC_CTOR(FIFO) : fifo(2)
    {
      SC_THREAD(consumer);
      	SC_THREAD(producer);
      	
    }
};
void FIFO::producer()
{
  int i = 0;
  while(i < 3)
  {
  	sc_int32 value(rand()%100);
  	
  	fifo.write(value);
	cout<<"write:"<<value<<endl;
    cout<<"No of empty slot:"<<fifo.num_free()<<endl;
    i++;
  }
}
void FIFO::consumer()
{
  sc_int32 value(0);
  while(true)
  {
 	 fifo.read(value);
  	cout<<"read:"<<value<<endl;
  }
}
int sc_main(int , char *[])
{
  FIFO obj("fifo");
  sc_start();
  cout<<"delta cycle:"<<sc_delta_count()<<endl;
  return 0;
}
