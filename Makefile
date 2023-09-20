NAME			=	miniRT

# **************************** COMPILER SETTINGS ***************************** #

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror -MMD -MP
CPPFLAGS		=	-I./include
LDFLAGS			=
LDLIBS			=	

ifdef DEV
    CFLAGS = -MMD -MP -g -fsanitize=address
    CPPFLAGS += -I./test
endif

# ********************************* LIBRAY *********************************** #

# libft
LIBFT_PATH		=	./lib/libft
CPPFLAGS		+=	-I./${LIBFT_PATH}
LDFLAGS			+=	-L./${LIBFT_PATH}
LDLIBS			+=	-lft -lftprintf -lgnl

# libstr
LIBSTR_PATH		=	./lib/libstr
CPPFLAGS		+=	-I./${LIBSTR_PATH}
LDFLAGS			+=	-L./${LIBSTR_PATH}
LDLIBS			+=	-lstr

# libds
LIBDS_PATH		=	./lib/libds
CPPFLAGS		+=	-I./${LIBDS_PATH}
LDFLAGS			+=	-L./${LIBDS_PATH}
LDLIBS			+=	-lds

# libmlx
LIBMLX_PATH		=	./lib/libmlx
CPPFLAGS		+=	-I./${LIBMLX_PATH}
LDFLAGS			+=	-L./${LIBMLX_PATH}
LDLIBS			+=	-lmlx -framework OpenGL -framework AppKit

# libmath
LIBMATH_PATH	=	./lib/libmath
CPPFLAGS		+=	-I./${LIBMATH_PATH}
LDFLAGS			+=	-L./${LIBMATH_PATH}
LDLIBS			+=	-lmath

# ****************************** SOURCE FILES ******************************** #

SRCS 			=	\
					$(wildcard src/*.c) \
					$(wildcard src/*/*.c) \
					$(wildcard src/*/*/*.c)
OBJS			=	$(SRCS:.c=.o)
DEPS			=	$(SRCS:.c=.d)

ifdef DEV
    SRCS += $(wildcard test/*.c)
endif

# ********************************** RULES ********************************** #

all:
	make -C $(LIBFT_PATH) --silent
	make -C $(LIBSTR_PATH) --silent
	make -C $(LIBDS_PATH) --silent
	make -C $(LIBMLX_PATH) --silent
	make -C $(LIBMATH_PATH) --silent
	make $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

clean:
	make -C $(LIBFT_PATH) clean --silent
	make -C $(LIBSTR_PATH) clean --silent
	make -C $(LIBDS_PATH) clean --silent
	make -C $(LIBMLX_PATH) clean --silent
	make -C $(LIBMATH_PATH) clean --silent
	rm -f $(OBJS) $(DEPS)

fclean:
	make -C $(LIBFT_PATH) fclean --silent
	make -C $(LIBSTR_PATH) fclean --silent
	make -C $(LIBDS_PATH) fclean --silent
	make -C $(LIBMLX_PATH) clean --silent
	make -C $(LIBMATH_PATH) fclean --silent
	rm -f $(NAME) $(OBJS) $(DEPS)

re: 
	make fclean
	make all

dev:
	make DEV=1

.PHONY: all clean fclean re
