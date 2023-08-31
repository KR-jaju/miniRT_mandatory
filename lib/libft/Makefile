NAME			=	libft.a

# **************************** COMPILER SETTINGS ***************************** #

CC				= 	cc
CFLAGS			= 	-Wall -Wextra -Werror
RM				= 	rm -f
AR				= 	ar
ARFLAGS			= 	-scr

# ****************************** SOURCE FILES ******************************** #

SRCS		=	ft_strlen.c ft_strlcpy.c ft_strlcat.c\
				ft_strchr.c ft_strnstr.c ft_strncmp.c\
				ft_strdup.c ft_strrchr.c ft_strnstr.c\
				ft_memset.c ft_memcpy.c ft_memmove.c\
				ft_memchr.c ft_memcmp.c ft_bzero.c\
				ft_atoi.c ft_calloc.c ft_isalnum.c\
				ft_isalpha.c ft_isascii.c ft_isdigit.c\
				ft_isprint.c ft_strdup.c ft_tolower.c\
				ft_toupper.c ft_substr.c ft_strjoin.c\
				ft_strtrim.c ft_split.c ft_itoa.c ft_strcmp.c\
				ft_strmapi.c ft_striteri.c ft_putchar_fd.c\
				ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
OBJS		=	$(SRCS:.c=.o)

LIBGNL		=	libgnl.a
LIBPRINTF	=	libftprintf.a
GNL_PATH	=	gnl
PRINTF_PATH	=	ft_printf

# ******************************** MAKE RULES ******************************* #

all:
	make $(NAME)

$(NAME): $(OBJS)
	make -C ./ft_printf --silent
	make -C ./gnl --silent
	cp ./$(PRINTF_PATH)/$(LIBPRINTF) ./$(LIBPRINTF)
	cp ./$(GNL_PATH)/$(LIBGNL) ./$(LIBGNL)
	$(AR) $(ARFLAGS) $@ $^ 

clean :
	make -C ./ft_printf clean
	make -C ./gnl clean
	$(RM) $(RMFLAG) $(OBJS)

fclean :
	make -C ./ft_printf fclean
	make -C ./gnl fclean
	$(RM) $(RMFLAG) $(OBJS) $(LIBPRINTF) $(LIBGNL) $(NAME)

re : 
	make fclean
	make all

 .PHONY : all bonus clean fclean re
