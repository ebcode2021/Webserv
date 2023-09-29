# PROGRAM_NAME
NAME = webserv

# VARIABLE
CC = c++
CFLAGS = -Wall -Wextra -Werror -std=c++98
RM = rm -rf

SRCS =  main3.cpp	\
		\
		classes/config/config.cpp		\
		classes/config/errorPage.cpp	\
		classes/config/limitExcept.cpp	\
		\
		classes/config/location/locationBlock.cpp	\
		\
		classes/config/server/serverBlock.cpp	\
		classes/config/server/serverInfo.cpp	\
		\
		classes/validate/validate.cpp			\
		\
		classes/server/server.cpp				\
		classes/server/serverInfoList.cpp		\
		\
		classes/socket/sockData.cpp		\
		classes/socket/sockInfo.cpp		\
		classes/socket/modeInfo.cpp		\
		\
		classes/http/httpBody.cpp		\
		classes/http/pathInfo.cpp		\
		classes/http/httpStatus.cpp		\
		classes/http/cgiMetadata.cpp	\
		classes/http/cgiInfo.cpp		\
		\
		classes/http/request/httpRequest.cpp		\
		classes/http/request/httpRequestLine.cpp	\
		classes/http/request/httpRequestHeader.cpp	\
		\
		classes/http/response/httpResponse.cpp		\
		classes/http/response/httpResponseHeader.cpp	\
		classes/http/response/httpResponseLine.cpp		\
		\
		utility/error.cpp	\
		utility/utils.cpp	\
		utility/validateUtils.cpp	\
		utility/sockUtils.cpp		\
		utility/serverUtils.cpp		\
		utility/eventUtils.cpp		\
		utility/parseUtils.cpp		\
		utility/encoding.cpp		\
		utility/pathUtils.cpp		\
		utility/autoIndexUtils.cpp	\
		\
		classes/kq/kqHandler.cpp	\
		\
		event/processEvent.cpp		\
		event/processRequest.cpp	\
		
		



SRCS_DIR = src/
SRCS_PATH = $(addprefix $(SRCS_DIR), $(SRCS))

INCLUDE_DIRS = includes/							\
			   includes/event/						\
			   includes/common/						\
			   includes/utility/					\
			   includes/classes/server/				\
			   includes/classes/config/				\
			   includes/classes/config/location/	\
			   includes/classes/config/server/		\
			   includes/classes/validate/			\
			   includes/classes/server/				\
			   includes/classes/socket/				\
			   includes/classes/kq/					\
			   includes/classes/http/				\
			   includes/classes/http/request/		\
			   includes/classes/http/response/







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