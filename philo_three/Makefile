NAME = philo_three

SRC_DIR = ./src
INC_DIR = ./inc
OBJ_DIR = ./obj

SRC = main.c setup.c routine.c run.c
SRC += numbers_utility.c strings_utility.c time_utility.c display_utility.c
vpath %.c $(SRC_DIR)
INC = philosophers.h
vpath %.h $(INC_DIR)
OBJ = $(addprefix  $(OBJ_DIR)/,$(SRC:%.c=%.o))
vpath %.c $(SRC_DIR)

IFLAGS = $(foreach inc, $(INC_DIR),-I$(inc))
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address

CC = clang
RM = rm -rf
MV = mv
MKD = mkdir -p
STRT_STYLE = \033[1;32m
END_STYLE = \033[0m

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@($(MKD) $(OBJ_DIR))
	@($(CC) $(CFLAGS) -c $(IFLAGS) $< -o $@)

$(NAME): $(OBJ)
	@(echo "$(STRT_STYLE)Compiling...$(END_STYLE)")
	@$(CC) $(CFLAGS) $(IFLAGS) -o $@ $(OBJ) -lpthread
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

clean:
	@(echo "$(STRT_STYLE)Cleaning...$(END_STYLE)")
	@($(RM) $(OBJ_DIR))
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

fclean: clean
	@(echo "$(STRT_STYLE)Fcleaning...$(END_STYLE)")
	@($(RM) $(NAME))
	@(echo "$(STRT_STYLE)Done.$(END_STYLE)")

re: fclean all

.PHONY: all clean fclean re
