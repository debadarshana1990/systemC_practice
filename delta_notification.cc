 #include <systemc>
using namespace sc_core;
using namespace std;
SC_MODULE(DELTA_TEST)
{
  int x = 1,  y = 2;
  SC_CTOR(DELTA_TEST)
  {
    SC_THREAD(add_x);
    SC_THREAD(mul_x);
    SC_THREAD(add_again_x);
  }
  void add_x()
  {
    x = x + 1;
    cout<<"add-x:"<<x<<endl;
  }
  void mul_x()
  {
    wait(SC_ZERO_TIME);
    x = x*2;
    cout<<"mul-x:"<<x<<endl;
  }
  void add_again_x()
  {
    x = x + 2;
    cout<<"add-again-x:"<<x<<endl;
  }
};
int sc_main(int, char *[])
{
  DELTA_TEST delta("delta");
  sc_start();
  return 0;
}
