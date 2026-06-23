NAME		= libasm.a

ASM			= nasm
ASMFLAGS	= -f elf64
AR			= ar
ARFLAGS		= rcs
RM			= rm -f

SRC_DIR		= srcs
OBJ_DIR		= objs

MANDATORY_SRCS	= $(filter-out %_bonus.s,$(wildcard $(SRC_DIR)/ft_*.s))
BONUS_SRCS		= $(wildcard $(SRC_DIR)/ft_*_bonus.s)

MANDATORY_OBJS	= $(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(MANDATORY_SRCS))
BONUS_OBJS		= $(patsubst $(SRC_DIR)/%.s,$(OBJ_DIR)/%.o,$(BONUS_SRCS))

all: $(NAME)

$(NAME): $(MANDATORY_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(MANDATORY_OBJS)

bonus: $(MANDATORY_OBJS) $(BONUS_OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(MANDATORY_OBJS) $(BONUS_OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.s
	mkdir -p $(OBJ_DIR)
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	$(RM) $(MANDATORY_OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
