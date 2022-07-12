// Code your design here.
// Uncomment the next line for SystemC modules.
#include <systemc>
#include <tlm>
#include "tlm_utils/simple_initiator_socket.h"
#include "tlm_utils/simple_target_socket.h"
using namespace tlm_utils;
using namespace tlm;
using namespace sc_core;
using namespace std;
/* initiator module */

class initiaotr : public sc_module
{
   public:
  	simple_initiator_socket<initiaotr> init_socket;
  	SC_HAS_PROCESS(initiaotr);
  	initiaotr(sc_module_name name):
	sc_module(name),
	init_socket("Init_Socket")
	{
     	 SC_THREAD(request_thread);
	}
  	void request_thread();
};

void initiaotr::request_thread(void)
{
  	tlm_generic_payload* trans = new tlm_generic_payload;
  	string msg = "Initiator msg";
  	cout<<"[Initiator]"<<sc_time_stamp()<<"msg sent"<<endl;
    trans->set_command( TLM_WRITE_COMMAND );
    trans->set_address( 0 );
    trans->set_data_ptr( (unsigned char*) msg.c_str() );
    trans->set_data_length( 4 );
    trans->set_streaming_width( 4 );
    trans->set_byte_enable_ptr( 0 );
    trans->set_dmi_allowed( false );
    trans->set_response_status( tlm::TLM_INCOMPLETE_RESPONSE );
  	sc_time delay = SC_ZERO_TIME;
  	init_socket->b_transport(*trans, delay);
  	if ( trans->is_response_error() ) 
    {
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
    }
}
class target : public sc_module
{
   private:
  		virtual void b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& delay);
  public:
  	simple_target_socket<target> target_socket;
  
  	SC_HAS_PROCESS(target);
  
  	target(sc_module_name name):
	sc_module(name),
	target_socket("Target_Socket")
	{
      	target_socket.register_b_transport(this, &target::b_transport);
	}
};

void target::b_transport(tlm::tlm_generic_payload& trans, sc_time& delay) {

  tlm::tlm_command cmd = trans.get_command();
  sc_dt::uint64    adr = trans.get_address() / 4;
  unsigned char*   ptr = trans.get_data_ptr();
  unsigned int     len = trans.get_data_length();
  unsigned char*   byt = trans.get_byte_enable_ptr();
  unsigned int     wid = trans.get_streaming_width();

  trans.set_response_status( tlm::TLM_OK_RESPONSE ); 

  cout << sc_time_stamp() << " : [target] b_transport - rcv = " << ptr << endl;
}

int sc_main(int argc, char *argv[])
{
  	initiaotr obj1("Initiator");
  	target obj2("Target");
  	obj1.init_socket.bind(obj2.target_socket);
  	sc_start();
  	return 0;
}

  	
	

  	
