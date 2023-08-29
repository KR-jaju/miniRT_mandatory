NAME			=	libstr.a

# **************************** COMPILER SETTINGS ***************************** #

CC				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror
AR				= 	ar
ARFLAGS			= 	-scr

# ****************************** SOURCE FILES ******************************** #

SRCS			=\
					str.c
OBJS			=	$(SRCS:.c=.o)
DEPS			= 	$(SRCS:.c=.d)

# ******************************** MAKE RULES ******************************* #

all:
	make $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS) $(DEPS)

fclean:
	rm -f $(NAME) $(OBJS) $(DEPS)

re : 
	make fclean
	make all

 .PHONY : all bonus clean fclean re
