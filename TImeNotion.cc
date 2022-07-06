 #include <systemc>
using namespace sc_core;
using namespace std;
using namespace sc_dt;
SC_MODULE(TIME_NOTION)
{
  int x = 1,  y = 2;
  SC_CTOR(TIME_NOTION)
  {
    SC_THREAD(add_x);
    SC_THREAD(mul_x);
	//SC_THREAD(mul_again_x);
  //  SC_THREAD(add_again_x);
  }
  void add_x()
  {
	cout << "Now at " << sc_time_stamp() << endl;
    x = x + 1;
    sc_time t_delay(3600,SC_SEC);
    wait(t_delay);
    cout << "After evaluation " << sc_time_stamp() << endl;
    cout<<"add-x:"<<x<<endl;
	double t = sc_time_stamp().to_seconds();
  std::cout << int(t) / 3600 << " hours, " << (int(t) % 3600) / 60 << " minutes, " << (int(t) % 60) << "seconds" << std::endl;
  }
  void mul_x()
  {
    x = x*2;
    cout<<"mul-x:"<<x<<endl;
  }

};
int sc_main(int, char *[])
{
  	sc_set_time_resolution(100,SC_MS);
  TIME_NOTION object("time");
  cout<<"time res:"<<sc_get_time_resolution()<<endl;

  sc_start();
  
	
  return 0;
}
