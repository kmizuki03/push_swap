/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_double_rotate(t_stack **a, t_stack **b, int *posa, int *posb,
			int sa, int sb);
void	exec_double_reverse(t_stack **a, t_stack **b, int *posa, int *posb,
			int sa, int sb);
void	exec_rotate_a(t_stack **a, int *posa, int sa);
void	exec_rotate_b(t_stack **b, int *posb, int sb);

static void	exec_all_rotations(t_stack **a, t_stack **b, int *posa, int *posb)
{
	int	sa;
	int	sb;

	sa = stack_size(*a);
	sb = stack_size(*b);
	exec_double_rotate(a, b, posa, posb, sa, sb);
	exec_double_reverse(a, b, posa, posb, sa, sb);
	exec_rotate_a(a, posa, sa);
	exec_rotate_b(b, posb, sb);
}

void	do_move(t_stack **a, t_stack **b, int pos_a)
{
	int	idx_a;
	int	posa;
	int	posb;

	idx_a = get_index_at_pos(*a, pos_a);
	posa = pos_a;
	posb = get_position(*b, get_target_index(*b, idx_a));
	exec_all_rotations(a, b, &posa, &posb);
	pb(a, b, 1);
}
