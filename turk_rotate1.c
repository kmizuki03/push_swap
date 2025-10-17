/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turk_rotate1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmizuki <kmizuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:51:10 by kmizuki           #+#    #+#             */
/*   Updated: 2025/10/17 12:51:11 by kmizuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exec_double_rotate(t_stack **a, t_stack **b, int *posa, int *posb,
		int sa, int sb)
{
	while (*posa > 0 && *posb > 0 && *posa <= sa / 2 && *posb <= sb / 2)
	{
		rr(a, b, 1);
		(*posa)--;
		(*posb)--;
	}
}

void	exec_double_reverse(t_stack **a, t_stack **b, int *posa, int *posb,
		int sa, int sb)
{
	while (*posa < sa && *posb < sb && *posa > sa / 2 && *posb > sb / 2)
	{
		rrr(a, b, 1);
		(*posa)++;
		(*posb)++;
	}
}
