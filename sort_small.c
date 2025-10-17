#include "push_swap.h"

static int	get_max_value_pos(t_stack *stack)
{
	int	max;
	int	pos;
	int	max_pos;

	max = stack->value;
	pos = 0;
	max_pos = 0;
	while (stack)
	{
		if (stack->value > max)
		{
			max = stack->value;
			max_pos = pos;
		}
		pos++;
		stack = stack->next;
	}
	return (max_pos);
}

void	sort_three(t_stack **stack_a)
{
	int	max_pos;

	if (is_sorted(*stack_a))
		return ;
	max_pos = get_max_value_pos(*stack_a);
	if (max_pos == 0)
		ra(stack_a, 1);
	else if (max_pos == 1)
		rra(stack_a, 1);
	if ((*stack_a)->value > (*stack_a)->next->value)
		sa(stack_a, 1);
}

static int	get_distance(t_stack *stack, int index)
{
	int	distance;

	distance = 0;
	while (stack)
	{
		if (stack->index == index)
			break ;
		distance++;
		stack = stack->next;
	}
	return (distance);
}

static void	push_min_to_b(t_stack **stack_a, t_stack **stack_b)
{
	int	min_index;
	int	distance;
	int	size;

	min_index = get_min_index(*stack_a);
	distance = get_distance(*stack_a, min_index);
	size = stack_size(*stack_a);
	if (distance <= size / 2)
	{
		while ((*stack_a)->index != min_index)
			ra(stack_a, 1);
	}
	else
	{
		while ((*stack_a)->index != min_index)
			rra(stack_a, 1);
	}
	pb(stack_a, stack_b, 1);
}

void	sort_small(t_stack **stack_a, t_stack **stack_b)
{
	int	size;

	size = stack_size(*stack_a);
	while (size > 3)
	{
		push_min_to_b(stack_a, stack_b);
		size--;
	}
	sort_three(stack_a);
	while (*stack_b)
		pa(stack_a, stack_b, 1);
}
