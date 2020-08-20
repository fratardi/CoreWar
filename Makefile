
##
## GLOBAL VARIABLES
##

# binaries
CW_ASM ?= asm
CW_VM ?= corewar

# sources
COMMON_SRC = \
	op.c

SRC_ASM = \
	$(COMMON_SRC) \
	asm/asm_main.c \
	asm/encoder.c  \
	asm/error.c  \
	asm/help_parser.c  \
	asm/parse_cmd_args.c  \
	asm/parse_command.c  \
	asm/parser.c  \
	asm/process_command.c  \
	asm/process_comment.c  \
	asm/process_header.c  \
	asm/write.c

SRC_VM_BASE = \
	$(COMMON_SRC) \
	vm/arena.c \
	vm/arg.c \
	vm/verbose.c \
	vm/debug_champion.c \
	vm/parsing.c \
	vm/rank.c \
	vm/read_champion.c \
	vm/tools.c \
	vm/ope_support.c \
	vm/disasm/disasm.c \
	vm/visual/visual.c \
	vm/visual/visu_annex.c \
	vm/operations/add.c \
	vm/operations/aff.c \
	vm/operations/and.c \
	vm/operations/fork.c \
	vm/operations/ld.c \
	vm/operations/ldi.c \
	vm/operations/lfork.c \
	vm/operations/live.c \
	vm/operations/lld.c \
	vm/operations/lldi.c \
	vm/operations/or.c \
	vm/operations/st.c \
	vm/operations/sti.c \
	vm/operations/sub.c \
	vm/operations/xor.c \
	vm/operations/zjmp.c \

SRC_NO_SDL = \
	vm/vm.c \
	vm/exec.c \
	vm/run.c \
	vm/exit.c \

SRC_SDL = \
	vm/gui/dsl.c \
	vm/gui/dsl_draw.c \
	vm/gui/dsl_support.c \
	vm/gui/vm.c \
	vm/gui/exec.c \
	vm/gui/run.c \
	vm/gui/exit.c \

SRC_VM = $(SRC_NO_SDL) $(SRC_VM_BASE)
SRC_VM_SDL = $(SRC_SDL) $(SRC_VM_BASE)

# sources dir
SRC_PATH = srcs

# tests dir
TEST_PATH =	test

# libft
LIBFT_DIR = libft
LIBFT_INC_PATH = $(LIBFT_DIR)/include
LIBFT_L = -L $(LIBFT_DIR) -lft
LFT = ($LIBFT_DIR)/libft.a
LFT_V = ($LIBFT_DIR)/libft_v.a

# all include
INC_PATH = $(LIBFT_INC_PATH) include
INC = $(addprefix -I, $(INC_PATH))

# extra flag for linking
LDLIBS = $(LIBFT_LDLIBS) -lncurses

# SDL libs
SDL_LIB = ./Framework/SDL2.framework/SDL2
TTF_LIB =  ./Framework/SDL2_ttf.framework/SDL2_ttf
SDL_LIBS = $(SDL_LIB) $(TTF_LIB)

# compilation flags
CPPFLAGS =

# flags
W_FLAGS = -Wall -Wextra -Werror
FSANITIZE= -fsanitize=address,undefined #-g3 -DDEBUG
FLAGS= $(W_FLAGS) $(FSANITIZE)
CURSEFLAG = -lncurses
WW_FLAGS = $(W_FLAGS) -Wpedantic -Wshadow -Wconversion -Wcast-align \
  -Wstrict-prototypes -Wmissing-prototypes -Wunreachable-code -Winit-self \
  -Wmissing-declarations -Wfloat-equal -Wbad-function-cast -Wundef \
  -Waggregate-return -Wstrict-overflow=5 -Wold-style-definition -Wpadded \
  -Wredundant-decls  # more warnings

# objects
OBJ_PATH ?= obj
OBJ_ASM = $(addprefix $(OBJ_PATH)/, $(SRC_ASM:.c=.o))
OBJ_VM = $(addprefix $(OBJ_PATH)/, $(SRC_VM:.c=.o))

# objects for valgrind
OBJ_PATH_V ?= obj_v
OBJ_ASM_V = $(addprefix $(OBJ_PATH_V)/, $(SRC_ASM:.c=.o))
OBJ_VM_V = $(addprefix $(OBJ_PATH_V)/, $(SRC_VM:.c=.o))

# # objects with SDL
OBJ_VM_S = $(addprefix $(OBJ_PATH)/, $(SRC_VM_SDL:.c=.o))
#
# # objects for valgrind with SDL
OBJ_VM_SV = $(addprefix $(OBJ_PATH_V)/, $(SRC_VM_SDL:.c=.o))

# obj folders
OBJ_SUB = asm vm vm/operations vm/visual vm/disasm vm/gui
OBJ_DIRS = $(OBJ_PATH) $(addprefix $(OBJ_PATH)/, $(OBJ_SUB))
OBJ_DIRS_V = $(OBJ_PATH_V) $(addprefix $(OBJ_PATH_V)/, $(OBJ_SUB))

# commands
RM =		rm -f
RMDIR =		rmdir
MKDIR =		mkdir -p
CC =		clang
SUB_MAKE =	make -C

# printf
PRINTF = printf

# colors
WHITE =		\033[37m
RED =		\033[31m
GREEN =		\033[32m
YELLOW =	\033[33m
BLUE =		\033[34m
MAGENTA =	\033[35m
CYAN =		\033[36m
NC =		\033[0m

##
## RULES
##

all: $(CW_ASM) $(CW_VM)

val: asm_val vm_val

sdl: $(CW_ASM) vm_sdl

sdl_val: asm_val vm_sdl_val

$(CW_VM): $(LFT) $(OBJ_VM)
	@echo "\n--- Making $(RED)corewar$(NC) ---"
	@echo "$(CYAN)>>> Making $(CW_VM) binary$(NC)"
	@$(CC) $(FLAGS) $(CURSEFLAG) $(OBJ_VM) $(LIBFT_L) $(INC) -o $(CW_VM)
	@echo "$(GREEN)vm ($@) is ready\n\n$(NC)"

vm_val: $(LFT_V) $(OBJ_VM_V)
	@$(RM) $(CW_VM)
	@echo "\n--- Making $(RED)corewar$(NC) for valgrind test---"
	@echo "$(CYAN)>>> Making $(CW_VM) binary$(NC)"
	@$(CC) $(W_FLAGS) $(CURSEFLAG) $(OBJ_VM_V) $(LIBFT_L) $(INC) -o $(CW_VM)
	@echo "$(GREEN)vm for valgrind is ready\n\n$(NC)"

vm_sdl: $(LFT) $(OBJ_VM_S)
	@$(RM) $(CW_VM)
	@echo "\n--- Making $(RED)corewar$(NC) with GUI---"
	@echo "$(CYAN)>>> Making $(CW_VM) binary$(NC)"
	@$(CC) $(FLAGS) -Wl,-rpath, "./Framework/" $(CURSEFLAG) $(OBJ_VM_S) $(LIBFT_L) $(SDL_LIBS) $(INC) -o $(CW_VM)
	@echo "$(GREEN)vm with GUI is ready\n\n$(NC)"

vm_sdl_val: $(LFT_V) $(OBJ_VM_SV)
	@$(RM) $(CW_VM)
	@echo "\n--- Making $(RED)corewar$(NC) for valgrind test with GUI---"
	@echo "$(CYAN)>>> Making $(CW_VM) binary$(NC)"
	@$(CC) $(W_FLAGS) $(CURSEFLAG) $(OBJ_VM_SV) $(LIBFT_L) $(SDL_LIBS) $(INC) -o $(CW_VM)
	@echo "$(GREEN)vm for valgrind with GUI is ready\n\n$(NC)"

$(CW_ASM): $(LFT) $(OBJ_ASM)
	@echo "\n--- Making $(RED)corewar$(NC)---"
	@echo "$(CYAN)>>> Making $(CW_ASM) binary$(NC)"
	@$(CC) $(FLAGS) $(OBJ_ASM) $(LIBFT_L)  $(INC) -o $(CW_ASM)
	@echo "$(GREEN)asm is ready\n\n$(NC)"

asm_val: $(LFT_V) $(OBJ_ASM_V)
	@$(RM) $(CW_ASM)
	@echo "\n--- Making $(RED)corewar$(NC) for valgrind test---"
	@echo "$(CYAN)>>> Making $(CW_ASM) binary$(NC)"
	@$(CC) $(W_FLAGS) $(OBJ_ASM_V) $(LIBFT_L) $(INC) -o $(CW_ASM)
	@echo "$(GREEN)asm for valgrind is ready\n\n$(NC)"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(MKDIR) $(OBJ_DIRS)
	@echo "$(MAGENTA)>>> Making $@$(NC)"
	@$(CC) $(FLAGS) $(INC) -c $< -o $@

$(OBJ_PATH_V)/%.o: $(SRC_PATH)/%.c
	@$(MKDIR) $(OBJ_DIRS_V)
	@echo "$(MAGENTA)>>> Making $@$(NC)"
	@$(CC) $(W_FLAGS) $(INC) -c $< -o $@

$(LFT): FORCE
	@echo "$(GREEN)checking $(LIBFT_DIR)...$(NC)"
	@$(SUB_MAKE) $(LIBFT_DIR)

$(LFT_V): FORCE
	@echo "$(GREEN) checking $(LIBFT_DIR)...$(NC)"
	@$(SUB_MAKE) $(LIBFT_DIR) val

FORCE:

clean:
	@echo "$(RED)deleting objects...$(NC)"
	@$(SUB_MAKE) $(LIBFT_DIR) clean
	@$(SUB_MAKE) $(LIBFT_DIR) clean_val
	@$(RM) -rf $(OBJ_PATH) $(OBJ_PATH_V)

fclean : clean
	@echo "$(RED)deleting executable...$(NC)"
	@$(SUB_MAKE) $(LIBFT_DIR) fclean
	@$(SUB_MAKE) $(LIBFT_DIR) fclean_val
	@$(RM) $(CW_ASM) $(CW_VM)

clean_val:
	@$(RM) -rf $(OBJ_PATH_V)
	@$(SUB_MAKE) $(LIBFT_DIR) fclean
	@$(RM)  $(CW_ASM) $(CW_VM)

re: fclean all

push : fclean
	@git add -A
	@git commit -m "quick push"
	@git push origin master
	git status

# norme
norme:
	+$(SUB_MAKE) $(LIBFT_DIR) norme
	norminette $(INC_PATH) $(SRC_PATH)
#phone
.PHONY: all, vm, asm, vm_val, asm_val, vm_sdl, vm_sdl_val, $(CW_ASM), $(CW_VM), clean, fclean, re, push, norme
