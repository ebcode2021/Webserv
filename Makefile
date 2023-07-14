# PROGRAM_NAME
NAME = webserv

# VARIABLE
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

# PHILOSOPHERS_SRC
SRCS =  main3.cpp	\
		utility/error.cpp	\
		utility/utils.cpp	\
		utility/validate.cpp	\
		utility/validateUtils.cpp\
		classes/Config.cpp	\
		classes/LocationBlock.cpp	\
		classes/ServerBlock.cpp		\
		classes/ErrorPage.cpp		\
		classes/LimitExcept.cpp		\
		classes/ServerInfo.cpp		\
		classes/TcpSocket.cpp		\
		classes/KqueueHandler.cpp	\
		classes/SocketEventHandler.cpp \
		classes/SessionStorage.cpp	\
		server/server.cpp


SRCS_DIR = src/
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))

INCLUDE_DIRS = includes/				\
			   includes/common/			\
			   includes/utility/		\
			   includes/classes/server/	\
			   includes/classes/config/	\







OBJS = $(SRCS_PATH:.cpp=.o)



# COMMANDS
%.o : %.cpp
	@echo "$(YELLOW) *** Generating push_swap objects... *** $(DEFAULT)"
	$(CC) $(CFLAGS) -c $< -o $@ $(addprefix -I, $(INCLUDE_DIRS))

$(NAME) : $(OBJS)
	@echo "$(GREEN) *** Compiling philo ... *** $(DEFAULT)"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	make clean
	@echo "$(GREEN) *** Compile Done!! *** $(DEFAULT)"


all : $(NAME)
	@echo "$(GREEN) *** Project Ready! *** $(DEFAULT)"

clean :
	$(RM) $(OBJS)
	@echo "$(RED) *** Deleteing Objects Done! *** $(DEFAULT)"

fclean : clean
	$(RM) $(NAME)
	@echo "$(RED) *** Delete Program Done! *** $(DEFAULT)"

re :
	make fclean
	make all
	make clean


.PHONY : all clean fclean re

# COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
DEFAULT = \033[0m