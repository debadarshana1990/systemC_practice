#include <systemc>
using namespace std;
SC_MODULE(Hello)
{
  SC_CTOR(Hello)
  {
    
  }
  void hello()
  {
    cout<<"Hello World"<<endl;
  }
};
 int sc_main(int argc, char* argv[])
{
  Hello obj("HELLO");
  obj.hello();
  return 0;
}