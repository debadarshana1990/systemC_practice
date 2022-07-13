// Code your design here.
// Uncomment the next line for SystemC modules.
#include <systemc>
#include "tlm.h"
#include "tlm_utils/simple_initiator_socket.h" // Header files from utilities
#include "tlm_utils/simple_target_socket.h"
using namespace sc_core;
using namespace std;
using namespace tlm;
struct Initiator: sc_module
{
    tlm_utils::simple_initiator_socket<Initiator, 32, tlm::tlm_base_protocol_types> socket;
    SC_CTOR(Initiator)
    : socket("socket") // Construct and name simple socket
    { // Register callbacks with simple socket
        socket.register_nb_transport_bw( this, &Initiator::nb_transport_bw );
        socket.register_invalidate_direct_mem_ptr( this, &Initiator::invalidate_direct_mem_ptr );
         SC_THREAD(request_thread);
    }
    virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay ) 
    {
        return tlm::TLM_COMPLETED; // Dummy implementation
    }
    virtual void invalidate_direct_mem_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range)
    { 

    } // Dummy implementation
    void request_thread();
};
void Initiator::request_thread(void)
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
	tlm_phase phase  = tlm::BEGIN_REQ;
  	socket->nb_transport_fw(*trans,phase, delay);
  	if ( trans->is_response_error() ) 
    {
      SC_REPORT_ERROR("TLM-2", "Response error from b_transport");
    }
  	else
    {
      	cout<<"Transaction complted"<<endl;
    }
}
struct Target: sc_module // Target component
{
    tlm_utils::simple_target_socket<Target, 32, tlm::tlm_base_protocol_types> socket;
    SC_CTOR(Target)
        : socket("socket") // Construct and name simple socket
    { // Register callbacks with simple socket
        socket.register_nb_transport_fw( this, &Target::nb_transport_fw );
        socket.register_b_transport( this, &Target::b_transport );
        socket.register_get_direct_mem_ptr( this, &Target::get_direct_mem_ptr );
        socket.register_transport_dbg( this, &Target::transport_dbg );
    }
    virtual void b_transport( tlm::tlm_generic_payload& trans, sc_time& delay )
    { } // Dummy implementation
    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans, tlm::tlm_phase& phase, sc_time& delay ) 
    {
      	  tlm::tlm_command cmd = trans.get_command();
  		sc_dt::uint64    adr = trans.get_address() / 4;
  		unsigned char*   ptr = trans.get_data_ptr();
  		unsigned int     len = trans.get_data_length();
  		unsigned char*   byt = trans.get_byte_enable_ptr();
  		unsigned int     wid = trans.get_streaming_width();

  		trans.set_response_status( tlm::TLM_OK_RESPONSE ); 
      	cout << sc_time_stamp() << " : [target] b_transport - rcv = " << ptr << endl;
      	cout << sc_time_stamp() << " : [target] b_transport - phase = " << phase << endl;
        return tlm::TLM_ACCEPTED; // Dummy implementation
    }
    virtual bool get_direct_mem_ptr( tlm::tlm_generic_payload& trans, tlm::tlm_dmi& dmi_data)
    { 
        return false;
     } // Dummy implementation
    virtual unsigned int transport_dbg(tlm::tlm_generic_payload& r)
    { 
        return 0; 
    } // Dummy implementation
};


int sc_main(int argc, char *argv[])
{
    Initiator *initiator;
    Target *target;
    initiator = new Initiator("initiator");
    target = new Target("target");
    initiator->socket.bind( target->socket ); // Bind initiator socket to target socket
    sc_start();
    return 0;
}
