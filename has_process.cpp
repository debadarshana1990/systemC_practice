// Code your design here
#include <systemc>
using namespace sc_core;
using namespace std;
SC_MODULE(MODULE_C) 
{
 	const int i;

  	SC_HAS_PROCESS(MODULE_C);

  	MODULE_C(sc_module_name name, int i) : i(i) {

    SC_METHOD(func_c);
  }

  void func_c() {
    std::cout << name() << ", additional input argument" << std::endl;
  }
};
SC_MODULE(MODULE_D)
{
  int j ;
  SC_HAS_PROCESS(MODULE_D);
  MODULE_D(sc_module_name);
  void func_d()
  {
    cout<<"Outside definition"<<endl;
  }
};
MODULE_D::MODULE_D(sc_module_name name):sc_module(name),j(j)
{
  SC_METHOD(func_d);
}

 int sc_main(int argc, char* argv[])
{
  MODULE_C module_c("module_c", 1);
   MODULE_D module_d("module_d");
   sc_start();
 // obj.hello();
  return 0;
}
