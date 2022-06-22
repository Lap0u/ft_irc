#include "../headers/Irc.hpp"
#include "../headers/Server.hpp"

#define WI_RPL_AWAY 301

#define WI_RPL_WHOISUSER 311

#define WI_RPL_WHOISSERVER 312

#define WI_RPL_WHOISOPERATOR 313

#define WI_RPL_WHOISIDLE 317

#define WI_RPL_ENDOFWHOIS 318

#define WI_RPL_WHOISCHANNELS 319

#define WI_ERR_NOSUCHNICK 401

#define WI_ERR_NOSUCHSERVER 402

#define WI_ERR_NONICKNAMEGIVEN 431      

#define N_RPL_NAMREPLY 353

#define N_RPL_ENDOFNAMES 366

#define J_ERR_NEEDMOREPARAMS 461

#define J_ERR_INVITEONLYCHAN 473

#define J_ERR_CHANNELISFULL 471

#define J_ERR_NOSUCHCHANNEL 403

#define J_ERR_TOOMANYTARGETS 407

#define J_ERR_BANNEDFROMCHAN 474

#define J_ERR_BADCHANNELKEY 475

#define J_ERR_BADCHANMASK 476

#define J_ERR_TOOMANYCHANNELS 405

#define J_ERR_UNAVAILRESOURCE 437

#define J_RPL_TOPIC 332

#define J_RPL_NAMREPLY 353

#define J_RPL_ENDOFNAMES 366

void	test_reply(int fd, Server & server)
{
	server.send_reply(fd, 431, ES, ES, ES, ES);
	server.send_reply(fd, 432, "nick", ES, ES, ES);
	server.send_reply(fd, 433, "nick", ES, ES, ES);
	server.send_reply(fd, 437, "nick", ES, ES, ES);
	server.send_reply(fd, 484, ES, ES, ES, ES);
	server.send_reply(fd, 461, "OPER", ES, ES, ES); // ERR_NEEDMOREPARAMS
	server.send_reply(fd, 464, ES, ES, ES, ES); // ERR_PASSWDMISMATCH
	server.send_reply(fd, 381, ES, ES, ES, ES); // RPL_YOUREOPER
	server.send_reply(fd, 461, "PASS", ES, ES, ES);
	server.send_reply(fd, 462, ES, ES, ES, ES);
	server.send_reply(fd, 409, ES, ES, ES, ES);
    server.send_reply(fd, 411, "PRIVMSG", ES, ES, ES);
    server.send_reply(fd, 412, ES, ES, ES, ES);
    server.send_reply(fd, 407, "target", "407", "Message couldn't be delivered", ES);
    server.send_reply(fd, 401, "target", ES, ES, ES);
	server.send_reply(fd, 461, "USER", ES, ES, ES);
	server.send_reply(fd, 462, ES, ES, ES, ES);
	server.send_reply(fd, 001, "Nick", "Username", server.getServerName(), ES);
	server.send_reply(fd, 002, server.getServerName(), server.getVersion(), ES, ES);
	server.send_reply(fd, 003, server.getDate(), ES, ES, ES);
	server.send_reply(fd, 004, server.getServerName(), server.getVersion(), USER_MODE, CHANNEL_MODE);
	server.send_reply(fd, 461, "MODE", ES, ES, ES); //ERR_NEEDMOREPARAMS
	server.send_reply(fd, 501, ES, ES, ES, ES); //ERR_UMODEUNKNOWNFLAG
	server.send_reply(fd, 502, ES, ES, ES, ES); //ERR_USERSDONTMATCH
	server.send_reply(fd, 221, "AoO", ES, ES, ES); // RPL_UMODEIS
    server.send_reply(fd, WI_ERR_NONICKNAMEGIVEN, ES, ES, ES, ES);
    server.send_reply(fd, WI_ERR_NOSUCHNICK, "nick", ES, ES, ES);
	server.send_reply(fd, WI_RPL_WHOISUSER, "Nick", "UserName", server.getServerName(), "RealName");
	server.send_reply(fd, WI_RPL_WHOISSERVER, "Nick", server.getServerName(), server.getServerInfos(), ES);
    server.send_reply(fd, WI_RPL_WHOISOPERATOR, "Nick", ES, ES, ES);
    server.send_reply(fd, WI_RPL_WHOISIDLE, "Nick", "0", ES, ES);
    server.send_reply(fd, WI_RPL_WHOISCHANNELS, "Nick", "make_function_to_get_user_channel", ES, ES);
    server.send_reply(fd, WI_RPL_AWAY, "Nick", " is away", ES, ES);
    server.send_reply(fd, WI_RPL_ENDOFWHOIS, "Nick", ES, ES, ES);
	server.send_reply(fd, J_ERR_NEEDMOREPARAMS, "join:", ES, ES, ES);
	server.send_reply(fd, J_RPL_TOPIC, "channame", "chanTopic", ES, ES);
	server.send_reply(fd, J_ERR_BADCHANNELKEY, "UserName", "channame", ES, ES);
	server.send_reply(fd, N_RPL_NAMREPLY, "channame", "user_list", ES, ES);
	server.send_reply(fd, N_RPL_ENDOFNAMES, "channame", ES, ES, ES);

	COUT "End of replies test, Bye.." ENDL;
	exit(1);
}

void    launch_serv(std::string port, std::string password)
{
	Server		server(atoi(port.c_str()), password);
	int			ret_poll;
	std::string	recvline;
	std::string	separatedline;
	int			fd;
	
	// test_reply(1, server);
	while(1)
	{
		ret_poll = poll(server.getSocket(0), server.getSocketSize(), 15000);
		if (ret_poll == -1)
		{
			perror("poll");
			exit (1); // need a clean exit closing all fds
		}
		else if (ret_poll == 0)
			continue ;
		for (nfds_t i = 0; i < server.getSocketSize(); i++)
		{
			if ((server.getSocket(i)->revents & POLLIN) == POLLIN)
			{
				server.getSocket(i)->revents = 0;
				if (i == 0)
				{
					fd = accept(server.getMainSocket(), (SA*) NULL, NULL);
					if (fd == -1)
					{
						perror("accept");
						exit(1);
					}
					server.addSocket(fd, POLLIN);
					User *user = new User();
					user->setSocket(fd);
					server.addUser(user);
				}
				else
					fd = server.getSocket(i)->fd;
				recvline = server.getPackage(fd);
				if (recvline.empty())
					continue ;
				while (recvline.find("\r\n") != std::string::npos)
				{
					separatedline = recvline.substr(0, recvline.find("\r\n"));
					server.parseCmd(separatedline, fd);
					recvline.erase(0, recvline.find("\r\n") + 2);
				}
				recvline.clear();
			}
		}
	}
	// close(temp_fd);//
}
