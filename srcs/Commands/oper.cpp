#include "../../headers/Commands.hpp"

int checkError(int fd, Server &server,
			   std::vector<std::string> word)
{
	if (word.size() != 3)
	{
		server.send_reply(fd, 461, "OPER", ES, ES, ES); // ERR_NEEDMOREPARAMS
		return 1;
	}
	if (word[2].compare(server.getOperPassword()) != 0)
	{
		server.send_reply(fd, 464, ES, ES, ES, ES); // ERR_PASSWDMISMATCH
		return 1;
	}
	return 0;
}

int oper(const std::string &line, int fd, Server &server)
{
	std::vector<std::string> word = ft_split(line, ' ');
	User *cur = server.findMatchingUser(fd);
	Oper *oper = NULL;

	if (checkError(fd, server, word))
		return (1);
	if (server.operExist(word[1]) == false)
	{
		oper = new Oper(word[1], cur);
		server.addOper(oper);
	}
	server.send_reply(fd, 381, ES, ES, ES, ES); // RPL_YOUREOPER
	std::string modeLine = "mode " + cur->getNick() + " +o";
	cur->setOperator(true);
	mode(modeLine, fd, server);
	return 0;
}

/**
 * @brief
 *
 *
 * 491    ERR_NOOPERHOST
			  ":No O-lines for your host"

		 - If a client sends an OPER message and the server has
		   not been configured to allow connections from the
		   client's host as an operator, this error MUST be
		   returned.

	==> Error doesn't exist.

464    ERR_PASSWDMISMATCH
			  ":Password incorrect"

		 - Returned to indicate a failed attempt at registering
		   a connection for which a password was required and
		   was either not given or incorrect.

381    RPL_YOUREOPER
			  ":You are now an IRC operator"

		 - RPL_YOUREOPER is sent back to a client which has
		   just successfully issued an OPER message and gained
		   operator status.

 */