O = obj/
I = inc/
S = src/
L = lib/

include sources.mk
OBJ = $(SRC:$S%.c=$O%.o)

CC = gcc
#REMEMBER TO REMOVE -g
CFLAGS = -Wall -Werror -Wextra  -g
INCFLAGS = -I$I

UNAME := $(shell uname)
ifeq ($(UNAME), Linux)
	LINUXFLAGS = -pthread -lpthread
endif

RM = rm -f

.PHONY: all clean fclean re fcleanlibft fcleanall reall test

# MAKERS
all: $(NAME)

$O:
	@mkdir -p $@

$(OBJ): | $O

$O%.o: $S%.c $(HEADERS) | $O
	@printf "Création des objets en cours : $@ ...\n"
	@$(CC) $(CFLAGS) $(INCFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(CC) $^ $(LINUXFLAGS) -o $@
	@printf "Have fun :-)\n"
	#make test

# CLEANERS
clean:
	$(RM) $(OBJ)
fclean: clean
	$(RM) $(NAME)
re: fclean all

test :
	./tests/tester.sh