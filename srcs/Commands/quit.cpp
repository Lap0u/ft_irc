#include "../../headers/Commands.hpp"

int    quit(const std::string &line, int fd, Server& server)
{
	error(line, fd, server);
	server.deleteUserQuittingChannel(server.findMatchingUser(fd));
	server.deleteUserSocket(static_cast<nfds_t>(server.findPosSocket(fd)));
    return 0;
}