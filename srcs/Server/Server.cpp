#include "../../headers/Server.hpp"

Server::Server(int port, std::string pass) : _server_password(pass), _server_name("Our_IRC")
{
	COUT "Server waiting on port " << port ENDL;

	struct sockaddr_in  servaddr;

	_main_socket = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (_main_socket < 0)
		exit(1);
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family         = AF_INET;
	servaddr.sin_addr.s_addr    = htonl(INADDR_ANY);
	servaddr.sin_port           = htons(port);

	if ((bind(_main_socket, (SA *) &servaddr, sizeof(servaddr))) < 0)
	{
		fprintf(stdout, "bind\n");
		exit(1);
	}

	if ((listen(_main_socket, 10)) < 0)
	{
		fprintf(stdout, "listen\n");
		exit(1);
	};
	addSocket(_main_socket, POLLIN);
	addUser(new User(_main_socket, "Server", "Server", "Server", "Server"));
	initReplies();
	initCommands();
}

Server::~Server( void )
{
	COUT "Destruct Server." ENDL;
}

void	Server::initReplies(void)
{
	_replies[0] = "RPL_WELCOME";
}

void	Server::initCommands(void)
{
	_commands["PASS"] = pass;
	_commands["NICK"] = nick;
	_commands["OPER"] = oper;
	_commands["USER"] = user;
	_commands["MODE"] = usermod;
}

