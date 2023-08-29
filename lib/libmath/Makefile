NAME			=	libmath.a

# **************************** COMPILER SETTINGS ***************************** #

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -MMD -MP
CPPFLAGS		=	-I../include
LDFLAGS			=
LDLIBS			=	

# ****************************** SOURCE FILES ******************************** #

SRCS 			=	$(wildcard *.c)
OBJS			=	$(SRCS:.c=.o)
DEPS			= 	$(SRCS:.c=.d)

# ********************************** RULES ********************************** #

all:
	make $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

clean:
	rm -f $(OBJS) $(DEPS)

fclean:
	rm -f $(NAME) $(OBJS) $(DEPS)

re: 
	make fclean
	make all

.PHONY: all clean fclean re
