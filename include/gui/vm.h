/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron <scoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/11 13:09:45 by scoron            #+#    #+#             */
/*   Updated: 2020/06/11 13:09:47 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../../libft/include/libft.h"
# include "../../Framework/SDL2_image.framework/Headers/SDL_image.h"
# include "../../Framework/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../../Framework/SDL2.framework/Headers/SDL.h"
# include "../op.h"

# define WIN_W 1500
# define WIN_H 900
# define FONT_SIZE 12

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

/*
** A_ for Argument type
*/

# define A_DIR			1
# define A_LDIR			2
# define A_IND			4
# define A_SIND			8
# define A_REG			16
# define A_VAL			32

# define FAILED			1
# define SUCCESS		0

# define HERO_COLOR_0	0xFFA50000
# define HERO_COLOR_1	0xBAC96400

/*
** Structure to help us read arguments
*/

typedef	struct			s_argcode
{
	t_uint8				mask;
	t_uint8				shift;
}						t_argcode;

/*
** Struct for champions
*/

typedef struct			s_champ
{
	struct s_champ		*next;
	const t_int8		name[PROG_NAME_LENGTH + 1];
	const t_int8		comment[COMMENT_LENGTH + 1];
	t_uint8				exec[CHAMP_MAX_SIZE + 1];
	size_t				exec_size;
	t_int32				nb;
	t_uint32			last_live;
	t_uint32			lives_count;
}						t_champ;

/*
** Different steps of a process
*/

typedef enum			e_step
{
	S_RUNNING,
	S_SLEEPING
}						t_step;

/*
** Process struct (or Carriage struct)
*/

typedef struct			s_cw_proc
{
	struct s_cw_proc	*next;
	t_uint8				*pos;
	t_champ				*champ;
	t_int32				reg[REG_NUMBER + 1];
	t_int32				nb;
	t_uint32			cycles_left;
	t_int32				last_live;
	t_uint8				opc;
	t_uint8				carry;
	t_step				step;
}						t_cw_proc;

/*
** GUI Struct for SDL
*/

typedef struct			s_cw_gui
{
	SDL_Window			*window;
	SDL_Renderer		*renderer;
	TTF_Font			*font;
	t_uint8				*hex_str;

}						t_cw_gui;

/*
** Data of current processes
*/

typedef struct			s_cw_data
{
	struct s_champ		*first_champ;
	struct s_cw_proc	*first_proc;
	t_uint8				*memory;
	t_uint32			*colors;
	struct s_cw_gui		*gui;
	ssize_t				dump;
	t_int32				verbose;
	t_uint32			lives_count;
	t_uint32			nbr_champ;
	t_uint32			nbr_proc;
	t_uint32			nbr_histo;
	t_int32				nbr_cycle;
	t_int32				checks;
	t_int32				since_last_check;
	t_int32				cycles_to_die;
}						t_cw_data;

extern t_cw_data		g_cwdata;

/*
**Declaration for struct in op.c
*/

extern t_op				g_op_tab[MAX_OP];
extern t_argcode		g_argcode[MAX_ARGS_NUMBER + 1];
typedef t_int32			(*t_action)(t_cw_proc *, t_uint8 *);

/*
**Debug functions
*/

void					print_champions_list(t_champ *champs);
void					print_carriage(void);
void					hex_to_i(t_uint8 *content,
						t_uint32 size, t_uint32 is_ind);

/*
**Visu
*/

void					print_refresh_area(t_int32 init);
void					clear_color(void);

/*
**VM EXEC
*/

void					cw_run(void);
void					exec_process(t_cw_proc *proc);
t_uint8					*cw_jump(t_uint8 const *pos,
						t_int32 jump, t_int32 idx_res);
t_uint8					*cp_on_buf(t_uint8 *buf,
						t_uint8 *pos, t_uint16 nb);
void					cw_carry(t_cw_proc *proc, t_int32 off);
t_int32					cw_read(t_uint8 *cursor, t_uint16 nb);
void					cw_write_int(t_uint8 *dest,
						t_uint8 *src, t_int32 color);
t_uint32				error_jump(t_uint8 *pos, t_uint8 opc);
t_int32					cw_check_regs_valid(t_uint8 *pos,
						t_uint8 mask, t_uint8 dir_is_short);

/*
**Parsing
*/

t_uint32				cw_parsing(t_int32 ac, t_int8 **av);
t_int32					cw_get_arg(t_cw_proc *proc,
						t_uint8 **cursor, t_uint8 nb, t_uint32 code_type);
size_t					cw_btoi(const t_uint8 *m, size_t len);
t_champ					*find_champ(t_int32 nb);
t_uint32				check_param(t_int8 *str, t_int8 *next);
t_uint32				check_option_next(t_int8 *str, t_int8 *next);
t_uint32				check_optional_next(t_uint32 param, t_int8 *next);
void					read_champ(const t_int8 *cor, t_int32 rank);
t_int32					find_rank(t_int32 rank);

/*
**Annexes
*/

void					clean_rank(void);
t_int32					abs(t_int32 nb);
t_int32					cw_exit(t_int32 ecode,
						t_int32 usage, t_int8 *msg);
t_uint32				convert_magic(t_uint32 d);
t_uint32				cw_size_param(t_uint8 param, t_uint8 dir_size);
t_int32					cw_sum(t_uint32 arg1, t_uint32 arg2);
t_int32					cw_minus(t_uint32 arg1, t_uint32 arg2);

/*
**Prepare processes and Arena
*/

void					fill_champ_arena(t_uint8 *pos,
						t_champ *champ, t_uint32 color);
t_int32					init_arena(void);
void					push_proc(t_cw_proc *proc);
void					fork_push_proc(t_cw_proc *proc);
void					fork_proc(t_cw_proc *new_proc,
						t_cw_proc *src, t_uint8 *pos);

/*
** Disasm
*/

t_uint32				disasm(t_champ *champs);
t_int8					get_arg_type_disasm(t_uint32 arg);

/*
**Operations
*/

t_int32					cw_add(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_and(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_live(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_aff(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_fork(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_lfork(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_ld(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_ldi(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_lld(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_lldi(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_or(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_st(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_sti(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_sub(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_xor(t_cw_proc *proc, t_uint8 *pos);
t_int32					cw_zjmp(t_cw_proc *proc, t_uint8 *pos);

/*
**Visual annex
*/

void					join_color_code(t_uint8 *buf,
						t_uint32 color_code);
void					join_buf(t_uint8 *buf,
						t_int8 *to_join, t_uint32 size);
void					clear_color(void);
void					print_head(void);

/*
**SDL
*/

void					dsl_init(void);
void					cw_print_grid(void);
void					cw_clean_grid(void);
void					set_rect_info(SDL_Rect *rect, t_uint32 pos);
void					cw_rect_init_sov(SDL_Rect *rect);
t_int8					*seg_hex_str(t_uint8 *src,
						t_uint8 *dst, t_uint32 start);
void					cw_draw_sov(void);
void					cw_draw_cross(SDL_Rect *rect);

#endif
