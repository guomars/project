#ifndef __CLIENT__STATE__
#define __CLIENT__STATE__

#ifdef WIN32
#include "gnproto.h"
#else
#include "protocol.h"
#endif

namespace GNET
{

extern GNET::Protocol::Manager::Session::State state_GLoginClient;
extern GNET::Protocol::Manager::Session::State state_GDataExchgClient;

};

#endif /* defined(__CLIENT__STATE__) */
