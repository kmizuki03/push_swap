#include "push_swap.h"

static int	calc_moves(int pos, int size)
{
	if (pos <= size / 2)
		return (pos);
	return (size - pos);
}

static int	calc_cost(t_stack *a, t_stack *b, int pos_a)
{
	int	idx_a;
	int	pos_b;
	int	size_a;
	int	size_b;
	int	cost_a;
	int	cost_b;

	idx_a = get_index_at_pos(a, pos_a);
	pos_b = get_position(b, get_target_index(b, idx_a));
	size_a = stack_size(a);
	size_b = stack_size(b);
	cost_a = calc_moves(pos_a, size_a);
	cost_b = calc_moves(pos_b, size_b);
	if ((pos_a <= size_a / 2 && pos_b <= size_b / 2) || 
		(pos_a > size_a / 2 && pos_b > size_b / 2))
	{
		if (cost_a > cost_b)
			return (cost_a);
		return (cost_b);
	}
	return (cost_a + cost_b);
}

static int	find_cheap(t_stack *a, t_stack *b)
{
	int	size;
	int	cheap_pos;
	int	cheap_cost;
	int	i;
	int	cost;

	size = stack_size(a);
	cheap_pos = 0;
	cheap_cost = calc_cost(a, b, 0);
	i = 1;
	while (i < size)
	{
		cost = calc_cost(a, b, i);
		if (cost < cheap_cost)
		{
			cheap_cost = cost;
			cheap_pos = i;
		}
		i++;
	}
	return (cheap_pos);
}

static void	exec_rot(t_stack **a, t_stack **b, int *posa, int *posb, int sa, int sb)
{
	while (*posa > 0 && *posb > 0 && *posa <= sa / 2 && *posb <= sb / 2)
	{
		rr(a, b, 1);
		(*posa)--;
		(*posb)--;
	}
	while (*posa < sa && *posb < sb && *posa > sa / 2 && *posb > sb / 2)
	{
		rrr(a, b, 1);
		(*posa)++;
		(*posb)++;
	}
	while (*posa > 0 && *posa <= sa / 2)
	{
		ra(a, 1);
		(*posa)--;
	}
	while (*posa < sa && *posa > sa / 2)
	{
		rra(a, 1);
		(*posa)++;
	}
	while (*posb > 0 && *posb <= sb / 2)
	{
		rb(b, 1);
		(*posb)--;
	}
	while (*posb < sb && *posb > sb / 2)
	{
		rrb(b, 1);
		(*posb)++;
	}
}

static void	do_move(t_stack **a, t_stack **b, int pos_a)
{
	int	idx_a;
	int	posa;
	int	posb;
	int	sa;
	int	sb;

	idx_a = get_index_at_pos(*a, pos_a);
	posa = pos_a;
	posb = get_position(*b, get_target_index(*b, idx_a));
	sa = stack_size(*a);
	sb = stack_size(*b);
	exec_rot(a, b, &posa, &posb, sa, sb);
	pb(a, b, 1);
}

void	turk_sort(t_stack **a, t_stack **b)
{
	int	size;
	int	pushed;
	int	pos;

	size = stack_size(*a);
	pushed = 0;
	if (size > 3)
	{
		pb(a, b, 1);
		pushed++;
	}
	if (size > 4)
	{
		pb(a, b, 1);
		pushed++;
	}
	while (size-- > 3)
	{
		do_move(a, b, find_cheap(*a, *b));
		pushed++;
	}
	sort_three(a);
	while (pushed--)
	{
		pos = get_position(*b, get_max_index(*b));
		size = stack_size(*b);
		while (pos > 0 && pos <= size / 2)
		{
			rb(b, 1);
			pos--;
		}
		while (pos < size && pos > size / 2)
		{
			rrb(b, 1);
			pos++;
		}
		pa(a, b, 1);
	}
	pos = get_position(*a, get_min_index(*a));
	size = stack_size(*a);
	if (pos <= size / 2)
	{
		while (pos-- > 0)
			ra(a, 1);
	}
	else
	{
		while (pos++ < size)
			rra(a, 1);
	}
}
