/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_ops_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:05:00 by kato              #+#    #+#             */
/*   Updated: 2025/09/24 16:06:28 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	pop_with_index(t_stack *stack, int *index)
{
	t_node	*temp;
	int		value;

	if (!stack || !stack->top)
		error_exit(stack, NULL);
	temp = stack->top;
	value = temp->value;
	if (index)
		*index = temp->index;
	stack->top = stack->top->next;
	free(temp);
	stack->size--;
	return (value);
}
