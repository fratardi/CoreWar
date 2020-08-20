/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:24:13 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:24:22 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H

# define ASM_H

# include "../libft/include/libft.h"
# include "../libft/include/ft_array.h"
# include "op.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

# define ARG_MAX_LEN	26
# define LABEL_MAX_LEN	23
# define OPCODE_MAX_LEN	7

# define EXT_ASM "s"
# define EXT_COR "cor"

# define EXIT_SUCCESS	0
# define EXIT_FAILURE	1
# define TRUE			1
# define FALSE			0

# define COMMENT_CHAR_2 ';'

# define COL_RESET		"\033[0m"
# define COL_RED		"\033[31;01m"
# define COL_GREEN		"\033[32;01m"
# define COL_CYAN		"\033[36;01m"
# define COL_BRED		"\033[1;01m\033[31;01m"
# define COL_BYELLOW	"\033[1;01m\033[33;01m"

# define MAX_WARNINGS	10

/*
** typedef to reduce line length (unsigned is a long word) and to make clear
** how much memory we're using
*/

typedef char			t_int8;
typedef int16_t			t_int16;
typedef int32_t			t_int32;
typedef int64_t			t_int64;
typedef unsigned char	t_uint8;
typedef uint16_t		t_uint16;
typedef uint32_t		t_uint32;
typedef uint64_t		t_uint64;

typedef struct			s_error
{
	char				*champ;
	char				*file;
	char				*li;
	char				**warnings;
	t_uint32			li_pos;
	t_int32				fd;
}						t_error;

enum					e_error
{
	E_OK = 0,
	E_WARNING = (1 << 0),
	E_USAGE = (1 << 1),
	E_READ = (1 << 2),
	E_OPEN = (1 << 3),
	E_CLOSE = (1 << 4),
	E_WRITE = (1 << 5),
	E_INPUT = (1 << 6)
};

extern t_error			g_err;
extern t_array			*g_result;
extern t_dico			*g_dico_labels;
extern t_op				g_op_tab[MAX_OP];

typedef enum			e_cmd_part
{
	C_START = 0,
	C_NAME = (1 << 0),
	C_COMMENT = (1 << 1),
	C_LABEL = (1 << 2),
	C_OP = (1 << 3),
	C_ARG = (1 << 4),
	C_MULTILINE_COMMENT = (1 << 5),
}						t_cmd_part;

typedef struct			s_command_input
{
	char				label[LABEL_MAX_LEN + 1];
	char				op[OPCODE_MAX_LEN + 1];
	char				av[MAX_ARGS_NUMBER][ARG_MAX_LEN + 1];
	t_int32				ac;
}						t_command_input;

typedef struct			s_command_output
{
	t_op				*op;
	t_arg_type			arg_type[MAX_ARGS_NUMBER];
	t_uint8				arg_sizeof[MAX_ARGS_NUMBER];
	t_uint32			loc;
	t_uint8				padding[4];
}						t_command_output;

void					process_header(t_header *header);
void					process_multiline_comment(char *line, t_header *header);
void					process_quotes(char *line, t_cmd_part *current);
void					init_global_err(char *champ);
t_bool					err_exit(t_uint8 err_type, char *msg);
void					parse(char *name);
void					init_dico(void);
char					*go_next_word(char *str);
char					*pass_word(char *str, t_cmd_part part);
size_t					verify_length(size_t length, t_command_input *command);
void					parse_command(t_command_input *input);
void					parse_args(t_command_input *input, \
						t_command_output *output);
void					process_command(void);
void					encode(t_command_input *input, \
								t_command_output *output);
void					asm_write(char *asm_name, t_header *header);
t_uint32				atoi_cor(const char *str, int opcode);
t_int32					eol(char c);

#endif
