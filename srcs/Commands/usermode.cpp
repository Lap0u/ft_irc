#include "../../headers/Commands.hpp"

int    mode(const std::string &line, int fd, Server& server)
{
	COUT line ENDL;
	(void)fd;
	(void)server;
	COUT "Pointeur mode" ENDL;
    return 2;
}
