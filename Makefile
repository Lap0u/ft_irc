NAME		=	ircserv

CXX			=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98
CXXFLAGS		+= -g3 -fsanitize=address

SRC			=	main.cpp \
				srcs/socket.cpp \
				srcs/User.cpp \
				srcs/Server.cpp

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