#ifndef __PASSIVEIO_H
#define __PASSIVEIO_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>

#include "conf.h"
#include "pollio.h"
#include "netio.h"

namespace GNET
{

class PassiveIO : public PollIO
{
	enum Type { STREAM, DGRAM };
	NetSession *assoc_session;
	Type type;
	DgramServerIO *dgram_server_io;

	void PollIn()
	{
		if (type == STREAM)
		{
			int s = accept(fd, 0, 0);
			if (s != -1)
				PollIO::Register(new StreamIO(s, assoc_session->Clone()), true, false);
		}
		else
		{
			PollIO::Register(dgram_server_io = new DgramServerIO(dup(fd), assoc_session), true, false);
			ForbidRecv();
			ForbidSend();
		}
	}

	PassiveIO (int x, const NetSession &y, Type t) : PollIO(x), assoc_session(y.Clone()), type(t), dgram_server_io(NULL)
	{
		assoc_session->LoadConfig();
	}

	/*PassiveIO (int x, const NetSession &y, Type t, variant conf) : PollIO(x), assoc_session(y.Clone()), type(t), dgram_server_io(NULL)
	{
		assoc_session->LoadConfig( conf );
	}*/
	virtual ~PassiveIO ()
	{
		if (type == STREAM)
			assoc_session->Destroy();
		else if ( dgram_server_io )
			dgram_server_io->Close();
	}

public:
	static PassiveIO *Open(const NetSession &assoc_session)
	{
		Conf *conf = Conf::GetInstance();
		Conf::section_type section = assoc_session.Identification(); 
		Conf::value_type type = conf->find(section, "type");
		SockAddr sa;

		int s = -1, optval = 1;
		Type t = STREAM;
		if (!strcasecmp(type.c_str(), "tcp"))
		{
			s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
			struct sockaddr_in *addr = sa;
			memset(addr, 0, sizeof(*addr));
			addr->sin_family = AF_INET;
			if ( (addr->sin_addr.s_addr = inet_addr(conf->find(section, "address").c_str())) == INADDR_NONE)
				addr->sin_addr.s_addr = INADDR_ANY;
			unsigned short port=atoi(conf->find(section, "port").c_str()); // for icpc bugs
			addr->sin_port = htons(port);
			assoc_session.OnCheckAddress(sa);

			setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
			setsockopt(s, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof(optval));

			optval = atoi(conf->find(section, "so_sndbuf").c_str());
			if (optval) setsockopt(s, SOL_SOCKET, SO_SNDBUF, &optval, sizeof(optval));
			optval = atoi(conf->find(section, "so_rcvbuf").c_str());
			if (optval) setsockopt(s, SOL_SOCKET, SO_RCVBUF, &optval, sizeof(optval));
			optval = atoi(conf->find(section, "tcp_nodelay").c_str());
			if (optval) setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof(optval));

			bind (s, sa, sa.GetLen());
			optval = atoi(conf->find(section, "listen_backlog").c_str());
			listen (s, optval ? optval : SOMAXCONN);
		}
		else if (!strcasecmp(type.c_str(), "udp"))
		{
			t = DGRAM;
			s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			struct sockaddr_in *addr = sa;
			memset(addr, 0, sizeof(*addr));
			addr->sin_family = AF_INET;
			if ( (addr->sin_addr.s_addr = inet_addr(conf->find(section, "address").c_str())) == INADDR_NONE)
				addr->sin_addr.s_addr = INADDR_ANY;
			unsigned short port=atoi(conf->find(section, "port").c_str()); // for icpc bugs
			addr->sin_port = htons(port);
			assoc_session.OnCheckAddress(sa);

			setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));

			optval = atoi(conf->find(section, "so_broadcast").c_str());
			if (optval) setsockopt(s, SOL_SOCKET, SO_BROADCAST, &optval, sizeof(optval));
			optval = atoi(conf->find(section, "so_sndbuf").c_str());
			if (optval) setsockopt(s, SOL_SOCKET, SO_SNDBUF, &optval, sizeof(optval));
			optval = atoi(conf->find(section, "so_rcvbuf").c_str());
			if (optval) setsockopt(s, SOL_SOCKET, SO_RCVBUF, &optval, sizeof(optval));

			bind (s, sa, sa.GetLen());
		}
		else if (!strcasecmp(type.c_str(), "unix"))
		{
			s = socket(AF_UNIX, SOCK_STREAM, 0);
			struct sockaddr_un *addr = sa;
			memset(addr, 0, sizeof(*addr));
			addr->sun_family = AF_UNIX;
			strncpy(addr->sun_path, conf->find(section, "address").c_str(), sizeof(addr->sun_path) - 1);
			addr->sun_path[sizeof(addr->sun_path) - 1] = '\0';
			unlink(addr->sun_path);
			assoc_session.OnCheckAddress(sa);

			optval = atoi(conf->find(section, "so_sndbuf").c_str());
			if (optval) setsockopt(s, SOL_SOCKET, SO_SNDBUF, &optval, sizeof(optval));
			optval = atoi(conf->find(section, "so_rcvbuf").c_str());
			if (optval) setsockopt(s, SOL_SOCKET, SO_RCVBUF, &optval, sizeof(optval));

			bind (s, sa, sa.GetLen());
			chmod(addr->sun_path, 0666);
			optval = atoi(conf->find(section, "listen_backlog").c_str());
			listen (s, optval ? optval : SOMAXCONN);
		}
		return s == -1 ? NULL : (PassiveIO*)PollIO::Register(new PassiveIO(s, assoc_session, t), true, false);
	}
};

};

#endif
