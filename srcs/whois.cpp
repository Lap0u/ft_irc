#include "../headers/Commands.hpp"

#define RPL_AWAY 301

#define RPL_WHOISUSER 311

#define RPL_WHOISSERVER 312

#define RPL_WHOISOPERATOR 313

#define RPL_WHOISIDLE 317

#define RPL_ENDOFWHOIS 318

#define RPL_WHOISCHANNELS 319

#define ERR_NOSUCHNICK 401

#define ERR_NOSUCHSERVER 402

#define ERR_NONICKNAMEGIVEN 431                        

int    count_words(const std::string string, char delimiter)
{
    int count = 1;
    const char * str = string.c_str();
    int length = strlen(string.c_str());
    for (int i = 0; i < length; i++)
    {
        if (str[i] == delimiter)
        {
            COUT "str[i] ==      " << delimiter ENDL;
            COUT "i ==           " << i ENDL;
            COUT "length ==      " << length ENDL;
            count++;
        }
    }
    return count;
}

int    whois(const std::string &line, int fd, Server& server)
{
	(void)line;
	(void)fd;
	(void)server;

	COUT "Pointeur whois" ENDL;
	COUT line.c_str() << "!" ENDL;

    int count = count_words(line, ' ');
    COUT "nb words == " << count ENDL;
    return RPL_ENDOFWHOIS;
}