NAME_SERVER = server
NAME_CLIENT = client

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRCS_DIR = srcs/
HEAD_DIR = includes/
FT_PRINTF_PATH = ft_printf/

SERVER_SRCS = server.c
CLIENT_SRCS = client.c

PRINTF_NAME = $(FT_PRINTF_PATH)libftprintf.a

SERVER_FILES = $(addprefix $(SRCS_DIR), $(SERVER_SRCS))
CLIENT_FILES = $(addprefix $(SRCS_DIR), $(CLIENT_SRCS))

SERVER_OBJS = $(SERVER_FILES:.c=.o)
CLIENT_OBJS = $(CLIENT_FILES:.c=.o)


all : $(NAME_SERVER) $(NAME_CLIENT)

$(PRINTF_NAME) :
	$(MAKE) -C $(FT_PRINTF_PATH) bonus

$(NAME_SERVER) : $(PRINTF_NAME) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o $(NAME_SERVER) -I $(HEAD_DIR) $(PRINTF_NAME)

$(NAME_CLIENT) : $(PRINTF_NAME) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o $(NAME_CLIENT) -I $(HEAD_DIR) $(PRINTF_NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I $(HEAD_DIR) $(PRINTF_NAME)

clean :
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS)
	$(MAKE) -C $(FT_PRINTF_PATH) clean

fclean : clean
	rm -f $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(FT_PRINTF_PATH) fclean

re : fclean all

.PHONY : all clean fclean re
