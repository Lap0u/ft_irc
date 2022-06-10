NAME		=	ircserv

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -g3

ifeq ($(D), 3)
	CXXFLAGS += -D DEBUG=2
else ifeq ($(D), 2)
    CXXFLAGS += -fsanitize=address -D DEBUG=2
else ifeq ($(D), 1)
    CXXFLAGS += -fsanitize=address    
endif

SRC			=	main.cpp \
				srcs/socket.cpp \
				srcs/User.cpp \
				srcs/Server/Server.cpp \
				srcs/Server/ServerConnection.cpp \
				srcs/Server/ServerGetters.cpp \
				srcs/Server/ServerParser.cpp \
				srcs/Server/ServerUtils.cpp \
				srcs/Message.cpp \
				srcs/Commands.cpp \
				srcs/MessageBuilder.cpp \
				srcs/whois.cpp \

OBJ			=	$(SRC:%.cpp=%.o)

all:		$(NAME)

$(NAME):	$(OBJ)
			$(CXX) $(CXXFLAGS) -MMD $(OBJ) -o $(NAME)

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm -rf $(NAME)

re:			fclean all

run:
			make all && ./$(NAME)

.PHONY:		all clean fclean re