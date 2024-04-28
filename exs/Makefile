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

ifndef EX
	EX								:= ch01 ch02 ch03 ch04 ch05
endif
RM								:= rm -rf
	
################################################################################
##                                DIRECTORIES                                 ##
################################################################################

OBJ_DIR						:= ../obj
SRC_DIR						:= ../src
LIB_DIR						:= ../lib
LIBFT_DIR					:= $(LIB_DIR)/libft
MLX_DIR						:= $(LIB_DIR)/MLX42
INC_DIRS					:= ../include $(LIBFT_DIR)/include $(MLX_DIR)/include

vpath %.c $(SRC_DIR) ./
vpath %.h $(INC_DIRS)
vpath %.o $(OBJ_DIR)

SOURCE						:= $(shell find $(SRC_DIR) -name '*.c' -exec basename {} \;)
SOURCE						:= $(filter-out main.c, $(SOURCE))
OBJECTS						:= $(addprefix $(OBJ_DIR)/, $(SOURCE:.c=.o))
	
################################################################################
##                                   FLAGS                                    ##
################################################################################

CFLAGS						:= -Wall -Wextra -Werror -O3 -g3
INCLUDE						:= $(addprefix -I, $(INC_DIRS))
LDFLAGS						:= -L$(LIBFT_DIR) -L$(MLX_DIR)/build
LDLIBS						:= -lft -lmlx42 -lglfw

ifeq ($(shell uname), Darwin)
	LDLIBS				+= -framework Cocoa -framework OpenGL -framework IOKit
else
	LDLIBS				+= -ldl -pthread -lm
endif

define run
	$(CC) $(CFLAGS) $(INCLUDE) $^ $(LDFLAGS) $(LDLIBS) -o $@ && ./$@ --verbose
endef

################################################################################
##                                COMPILATION                                 ##
################################################################################

all: $(EX) clean

.PHONY: ch01
ch01: $(OBJECTS) ch01.c
	@$(call run, "$^")

.PHONY: ch02
ch02: $(OBJECTS) ch02.c
	@$(call run, "$^")

.PHONY: ch03
ch03: $(OBJECTS) ch03.c
	@$(call run, "$^")

.PHONY: ch04
ch04: $(OBJECTS) ch04.c
	@$(call run, "$^")

.PHONY: ch05
ch05: $(OBJECTS) ch05.c
	@$(call run, "$^")

$(OBJECTS):
	@make -C .. -s

clean:
	@printf "$(MAGENTA)[$(EX)] $(DEFAULT)Cleaning up tests..."
	@$(RM) $(EX)
	@printf "\r%100s\r$(MAGENTA)[$(EX)] $(YELLOW)Full clean success "
	@printf "🧹🧹$(DEFAULT)\n"

fclean: clean

re: fclean all

.PHONY: all clean fclean re
