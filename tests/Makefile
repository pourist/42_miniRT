################################################################################
##                                   COLORS                                   ##
################################################################################

DEFAULT     := \033[0;39m
GRAY        := \033[0;90m
RED         := \033[0;91m
GREEN       := \033[0;92m
YELLOW      := \033[0;93m
BLUE        := \033[0;94m
MAGENTA     := \033[0;95m
CYAN        := \033[0;96m
WHITE       := \033[0;97m
	
################################################################################
##                                   MINIRT                                   ##
################################################################################

TESTS							:= tuples
RM								:= rm -rf
	
################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR						:= ../obj
SRC_DIR						:= ../src
LIB_DIR						:= ../lib
LIBFT_DIR					:= $(LIB_DIR)/libft
MLX_DIR						:= $(LIB_DIR)/MLX42
INC_DIRS						:= include $(LIBFT_DIR)/include $(MLX_DIR)/include

vpath %.c $(SRC_DIR) ./
vpath %.h $(INC_DIRS)
vpath %.o $(OBJ_DIR)

SOURCE						:= $(shell find $(SRC_DIR) -name '*.c' -exec basename {} \;)
SOURCE						:= $(filter-out main.c, $(SOURCE))
OBJECTS						:= $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))
	
################################################################################
##                                   FLAGS                                    ##
################################################################################

CFLAGS						:= -Wall -Wextra -Werror
INCLUDE						:= $(addprefix -I, $(INC_DIRS))
LDFLAGS						:= -L$(LIBFT_DIR) -L$(MLX_DIR)/build
LDLIBS						:= -lft -lmlx42 -lglfw -lcriterion

ifeq ($(shell uname), Darwin)
	LDLIBS				+= -framework Cocoa -framework OpenGL -framework IOKit
else
	LDLIBS				+= -ldl -pthread -lm
endif

ifdef DEBUG
	CFLAGS					 += -g3
else
	CFLAGS 					 += -O3
endif

define run
	$(CC) $(CFLAGS) $(INCLUDE) $^ $(LDFLAGS) $(LDLIBS) -o $@ && ./$@ --verbose
endef

################################################################################
##                                COMPILATION                                 ##
################################################################################

all: $(TESTS) clean

.PHONY: tuples
tuples: $(OBJECTS) test_tuples.c
	@$(call run, "$^")

clean:
	@printf "$(MAGENTA)[$(NAME)] $(DEFAULT)Cleaning up tests..."
	@$(RM) $(TESTS)

fclean: clean
	@printf "\r%100s\r$(MAGENTA)[tests] $(YELLOW)Full clean success "
	@printf "🧹🧹$(DEFAULT)\n"

re: fclean all

.PHONY: all clean fclean re
