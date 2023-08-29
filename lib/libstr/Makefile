

.DEFAULT_GOAL	= all

CC			= cc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
AR			= ar
ARFLAGS		= -scr

# ********************************** LIBSTR ********************************** #

LIBSTR		= libstr.a
SRCS		=\
				str.c

OBJS		= $(SRCS:.c=.o)
$(LIBSTR): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

# ******************************** MAKE RULES ******************************* #

all :
	make $(LIBSTR)

clean :
	$(RM) $(RMFLAG) $(OBJS)

fclean :
	$(RM) $(RMFLAG) $(OBJS)
	$(RM) $(RMFLAG) $(LIBSTR)

re : 
	make fclean
	make all

 .PHONY : all bonus clean fclean re
