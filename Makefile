# PROGRAM_NAME
NAME = webserv

# VARIABLE
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

# PHILOSOPHERS_SRC
SRCS =  main.cpp	\
		utility/error.cpp	\
		utility/notice.cpp	\
		utility/utils.cpp	\
		utility/validate.cpp	\
		utility/validateUtils.cpp\
		classes/Config.cpp	\
		classes/LocationBlock.cpp	\
		classes/ServerBlock.cpp		\
		classes/ServerList.cpp		\
		classes/ErrorPage.cpp		\
		classes/LimitExcept.cpp		\
		classes/ServerInfo.cpp		\
		classes/TcpSocket.cpp		\
		classes/KqueueHandler.cpp	\
		classes/SocketEventHandler.cpp \
		http/request/HttpRequest.cpp \
		http/request/HttpRequestHeader.cpp \
		http/request/HttpRequestLine.cpp 



SRCS_DIR = src/
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))

INCS = includes/
CLASS_INCS = includes/classes/
COMMON_INCS = includes/common/
UTILITY_INCS = includes/utility/
HTTP_INCS = includes/http/
HTTP_COMMON_INCS = includes/http/common/
HTTP_REQUEST_INCS = includes/http/request/
HTTP_RESPONSE_INCS = includes/http/response/

OBJS = $(SRCS_PATH:.cpp=.o)



# COMMANDS
%.o : %.cpp
	@echo "$(YELLOW) *** Generating push_swap objects... *** $(DEFAULT)"
	$(CC) $(CFLAGS) -c $< -o $@ -I $(INCS) -I $(CLASS_INCS) -I $(COMMON_INCS) -I $(UTILITY_INCS) -I $(HTTP_INCS) -I $(HTTP_COMMON_INCS) -I $(HTTP_REQUEST_INCS) -I $(HTTP_RESPONSE_INCS)

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