##
## EPITECH PROJECT, 2021
## makefile
## File description:
## makefile
##

SRC	=	src/*.c\

CFLAGS	=	-Wall -Wextra -Wno-deprecated -g3 -fPIC -I include/

OBJS	=	$(SRC:.c=.o)

NAME	=	libmy_malloc.so

all:	$(NAME)

$(NAME): $(OBJS)
	gcc -fPIC -shared -o $(NAME) $(OBJS) $(CFLAGS)

clean:
	rm -rf $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
