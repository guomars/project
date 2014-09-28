//
//  State.cpp
//  Client
//
#ifdef WIN32
#include <winsock2.h>
#include <windows.h>

#include "gnproto.h"
#include "gncompress.h"

#else
#include "binder.h"
#endif

#include "State.hxx"
#include "callid.hxx"

namespace GNET
{

static GNET::Protocol::Type _state_GLoginClient[] =
{
    PROTOCOL_CHALLENGE,
};  
    
GNET::Protocol::Manager::Session::State state_GLoginClient(_state_GLoginClient,
                        sizeof(_state_GLoginClient)/sizeof(GNET::Protocol::Type), 6000);
    
static GNET::Protocol::Type _state_GDataExchangeClient[] =
{   
    PROTOCOL_CHALLENGE,
};

GNET::Protocol::Manager::Session::State state_GDataExchangeClient(_state_GDataExchangeClient,
                        sizeof(_state_GDataExchangeClient)/sizeof(GNET::Protocol::Type), 7200);

};
	
