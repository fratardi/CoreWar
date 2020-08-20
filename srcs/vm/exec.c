/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scoron  <scoron@student.42.fr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/29 16:02:14 by scoron            #+#    #+#             */
/*   Updated: 2020/07/02 16:18:29 by scoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_action	g_action[MAX_OP] = {
	cw_live,
	cw_ld,
	cw_st,
	cw_add,
	cw_sub,
	cw_and,
	cw_or,
	cw_xor,
	cw_zjmp,
	cw_ldi,
	cw_sti,
	cw_fork,
	cw_lld,
	cw_lldi,
	cw_lfork,
	cw_aff
};

t_uint8			*cw_jump(t_uint8 const *pos, t_int32 jump, t_int32 idx)
{
	t_int32	diff;
	t_int32	i;

	i = -1;
	if (idx > 0 && idx < 42)
		jump %= IDX_MOD;
	else
		jump %= MEM_SIZE;
	while (jump < 0)
		jump = MEM_SIZE + jump;
	diff = (t_int32)(pos - g_cwdata.memory + jump);
	while (diff < 0)
		diff = MEM_SIZE + diff;
	if (idx == 42 && g_cwdata.verbose == 1)
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x)", jump,
				(t_int32)(pos - g_cwdata.memory), diff);
		while (++i <= jump)
			ft_printf(" %.2x", *(g_cwdata.memory +
			(((pos + i) - g_cwdata.memory) % MEM_SIZE)));
		ft_printf("\n");
	}
	return (g_cwdata.memory + (diff % MEM_SIZE));
}

static t_int32	scan_arg(t_uint8 op_code, t_uint8 param_code, t_uint8 arg_nb)
{
	t_uint8 type;

	type = g_op_tab[op_code].type[arg_nb];
	if ((type == 0 && param_code == 0) ||
	((type & T_REG) && (param_code == REG_CODE)) ||
	((type & T_IND) && (param_code == IND_CODE)) ||
	((type & T_DIR) && (param_code == DIR_CODE)))
		return (SUCCESS);
	return (FAILED);
}

static t_int32	cw_param_code(t_uint8 *pos, t_uint8 opc)
{
	t_uint8 pcode;
	t_uint8 nb;

	pcode = *cw_jump(pos, 1, 0);
	nb = g_op_tab[opc - 1].params;
	if ((nb > 2 && scan_arg((t_uint8)(opc - 1),
			(t_uint8)((pcode & 0x0c) >> 2), 2))
		|| (nb > 1 && scan_arg((t_uint8)(opc - 1),
				(t_uint8)((pcode & 0x30) >> 4), 1))
		|| (nb > 0 && scan_arg((t_uint8)(opc - 1),
				(t_uint8)((pcode & 0xc0) >> 6), 0)))
		return (FAILED);
	return (SUCCESS);
}

t_int32			exec_opcode(t_cw_proc *proc,
		t_uint8 *pos, t_uint8 opc)
{
	t_int32 res;

	res = FAILED;
	if (g_cwdata.verbose > 3 && (g_cwdata.verbose < 10 ||
	g_cwdata.nbr_cycle >= g_cwdata.verbose))
		print_refresh_area(0);
	if ((g_op_tab[opc - 1].params > 1 ||
	opc == 16) && cw_param_code(pos, opc) != SUCCESS)
		proc->pos = cw_jump(pos, error_jump(pos, opc), 42);
	else
	{
		if (g_cwdata.verbose == 1)
			ft_printf("\nCycle %d, pos 0x%.4x : process %d [%s] attempts"
			" \"%s\" (%x)\n", g_cwdata.nbr_cycle, proc->pos - g_cwdata.memory,
			proc->nb, proc->champ->name, g_op_tab[opc - 1].name, *proc->pos);
		res = g_action[opc - 1](proc, pos);
	}
	return (res);
}

void			exec_process(t_cw_proc *proc)
{
	if (proc->step == S_RUNNING)
	{
		if (*proc->pos < 0x1 || *proc->pos > MAX_OP)
			proc->pos = cw_jump(proc->pos, 1, 0);
		else
		{
			proc->opc = *proc->pos;
			proc->cycles_left = g_op_tab[*proc->pos - 1].cycles - 1;
			proc->step = S_SLEEPING;
		}
	}
	else if (proc->step == S_SLEEPING)
	{
		if (proc->cycles_left > 1)
			--proc->cycles_left;
		else
		{
			proc->step = S_RUNNING;
			if (exec_opcode(proc, proc->pos, proc->opc) == FAILED
			&& g_cwdata.verbose == 1)
				ft_printf(" FAILED\n");
		}
	}
}
