NAME			=	libds.a

# **************************** COMPILER SETTINGS ***************************** #

CC				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror
CPPFLAGS		= 	-I../libft
AR				= 	ar
ARFLAGS			= 	-scr

# ********************************* LIBRAY *********************************** #

# libft
LIBFT_PATH		=	../libft
LDFLAGS			+=	-L./${LIBFT_PATH}
LDLIBS			+=	-lft -lftprintf -lgnl

# ****************************** SOURCE FILES ******************************** #

SRCS 			=	$(wildcard *.c)
OBJS			=	$(SRCS:.c=.o)
DEPS			= 	$(SRCS:.c=.d)

# ********************************** RULES ********************************** #

all:
	make -C $(LIBFT_PATH) --silent
	make $(NAME)

$(NAME): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

clean:
	rm -f $(OBJS) $(DEPS)

fclean:
	rm -f $(NAME) $(OBJS) $(DEPS)

re: 
	make fclean
	make all

.PHONY: all clean fclean re
