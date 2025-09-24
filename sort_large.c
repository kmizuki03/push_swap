/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:03:00 by kato              #+#    #+#             */
/*   Updated: 2025/09/24 17:28:52 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/*
** LIS + 最小コスト挿入方式
** 1) AからLISに含まれない要素のみBへ押し出し
** 2) Bの各要素の最小コスト位置を計算してAへ挿入
** 3) Aを最終的に最小indexが先頭になるよう回転
*/

typedef struct s_arr
{
	int			*data;
	int			size;
}				t_arr;

static int	min_int(int a, int b)
{
	return ((a < b) ? a : b);
}
static int	max_int(int a, int b)
{
	return ((a > b) ? a : b);
}

static void	free_and_exit(int *a, int *b)
{
	if (a)
		free(a);
	if (b)
		free(b);
}

/* スタックAのindex列を配列化 */
static t_arr	get_indices_array(t_stack *a)
{
	t_arr	arr;
	t_node	*cur;
	int		i;

	arr.size = a->size;
	arr.data = (int *)malloc(sizeof(int) * arr.size);
	if (!arr.data)
	{
		arr.size = 0;
		return (arr);
	}
	cur = a->top;
	i = 0;
	while (cur)
	{
		arr.data[i++] = cur->index;
		cur = cur->next;
	}
	return (arr);
}

/* O(n^2)でLIS長と復元用prevを計算 */
static int	*compute_lis_mask_from_indices(t_arr indices)
{
	int	n;
	int	*len;
	int	*prev;
	int	*mask;
	int	i;
	int	j;
	int	best_len;
	int	best_end;

	n = indices.size;
	len = (int *)malloc(sizeof(int) * n);
	prev = (int *)malloc(sizeof(int) * n);
	mask = (int *)malloc(sizeof(int) * n);
	if (!len || !prev || !mask)
	{
		free_and_exit(len, prev);
		if (mask)
			free(mask);
		return (NULL);
	}
	i = 0;
	while (i < n)
	{
		len[i] = 1;
		prev[i] = -1;
		i++;
	}
	i = 0;
	while (i < n)
	{
		j = 0;
		while (j < i)
		{
			if (indices.data[j] < indices.data[i] && len[j] + 1 > len[i])
			{
				len[i] = len[j] + 1;
				prev[i] = j;
			}
			j++;
		}
		i++;
	}
	best_len = 0;
	best_end = 0;
	i = 0;
	while (i < n)
	{
		if (len[i] > best_len)
		{
			best_len = len[i];
			best_end = i;
		}
		i++;
	}
	i = 0;
	while (i < n)
		mask[i++] = 0;
	while (best_end != -1)
	{
		mask[best_end] = 1;
		best_end = prev[best_end];
	}
	free_and_exit(len, prev);
	return (mask);
}

/* Aの先頭から順に、LISに含まれない要素をBへ押す（初期順でn回だけ判定） */
static void	push_non_lis_to_b(t_stack *a, t_stack *b, int *mask, int n)
{
	int	processed;
	int	i;

	processed = 0;
	i = 0;
	while (processed < n)
	{
		if (mask[i] == 0)
			pb(a, b);
		else
			ra(a);
		processed++;
		i++;
	}
}

/* Bの値(インデックス)を挿入するA内のターゲット位置(先頭からの回数) */
static int	find_target_pos_in_a(t_stack *a, int b_index)
{
	t_node	*cur;
	int		pos;
	int		best_pos;
	int		best_diff;

	cur = a->top;
	pos = 0;
	best_pos = -1;
	best_diff = INT_MAX;
	while (cur)
	{
		if (cur->index > b_index && cur->index - b_index < best_diff)
		{
			best_diff = cur->index - b_index;
			best_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	if (best_pos != -1)
		return (best_pos);
	/* 無ければAの最小indexの位置 */
	cur = a->top;
	pos = 0;
	best_pos = 0;
	best_diff = INT_MAX;
	while (cur)
	{
		if (cur->index < best_diff)
		{
			best_diff = cur->index;
			best_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	return (best_pos);
}

/* コスト計算に基づき回転を適用（rr/rrrは使わず個別に回す） */
static void	apply_min_cost_rotation(t_stack *a, t_stack *b, int pos_a,
		int pos_b)
{
	int	a_up;
	int	b_up;
	int	a_down;
	int	b_down;
	int	cost_rr;
	int	cost_rrr;
	int	cost_ra_rrb;
	int	cost_rra_rb;

	a_up = pos_a;
	b_up = pos_b;
	a_down = a->size - pos_a;
	b_down = b->size - pos_b;
	cost_rr = max_int(a_up, b_up);
	cost_rrr = max_int(a_down, b_down);
	cost_ra_rrb = a_up + b_down;
	cost_rra_rb = a_down + b_up;
	if (cost_rr <= cost_rrr && cost_rr <= cost_ra_rrb && cost_rr <= cost_rra_rb)
	{
		while (a_up > 0 && b_up > 0)
		{
			ra(a);
			rb(b);
			a_up--;
			b_up--;
		}
		while (a_up-- > 0)
			ra(a);
		while (b_up-- > 0)
			rb(b);
	}
	else if (cost_rrr <= cost_rr && cost_rrr <= cost_ra_rrb
		&& cost_rrr <= cost_rra_rb)
	{
		while (a_down > 0 && b_down > 0)
		{
			rra(a);
			rrb(b);
			a_down--;
			b_down--;
		}
		while (a_down-- > 0)
			rra(a);
		while (b_down-- > 0)
			rrb(b);
	}
	else if (cost_ra_rrb <= cost_rr && cost_ra_rrb <= cost_rrr
		&& cost_ra_rrb <= cost_rra_rb)
	{
		while (a_up-- > 0)
			ra(a);
		while (b_down-- > 0)
			rrb(b);
	}
	else
	{
		while (a_down-- > 0)
			rra(a);
		while (b_up-- > 0)
			rb(b);
	}
}

/* Bの全要素について、最小コストのものからAへ戻す */
static void	insert_all_by_min_cost(t_stack *a, t_stack *b)
{
		t_node *cur;
		int best_cost;
		int best_pos_b;
		int best_pos_a;
		int pos_b;
			int target_a;
			int a_up;
			int b_up;
			int a_down;
			int b_down;
			int cost;

	while (!is_empty(b))
	{
		cur = b->top;
		best_cost = INT_MAX;
		best_pos_b = 0;
		best_pos_a = 0;
		pos_b = 0;
		while (cur)
		{
			target_a = find_target_pos_in_a(a, cur->index);
			a_up = target_a;
			b_up = pos_b;
			a_down = a->size - target_a;
			b_down = b->size - pos_b;
			cost = min_int(max_int(a_up, b_up), max_int(a_down, b_down));
			cost = min_int(cost, a_up + b_down);
			cost = min_int(cost, a_down + b_up);
			if (cost < best_cost)
			{
				best_cost = cost;
				best_pos_b = pos_b;
				best_pos_a = target_a;
			}
			cur = cur->next;
			pos_b++;
		}
		apply_min_cost_rotation(a, b, best_pos_a, best_pos_b);
		pa(a, b);
	}
}

/* Aの最小indexを先頭に */
static void	rotate_a_to_min_index(t_stack *a)
{
	t_node	*cur;
	int		pos;
	int		min_pos;
	int		min_idx;
		int cnt;

	cur = a->top;
	pos = 0;
	min_pos = 0;
	min_idx = INT_MAX;
	while (cur)
	{
		if (cur->index < min_idx)
		{
			min_idx = cur->index;
			min_pos = pos;
		}
		cur = cur->next;
		pos++;
	}
	if (min_pos <= a->size / 2)
		while (min_pos-- > 0)
			ra(a);
	else
	{
		cnt = a->size - min_pos;
		while (cnt-- > 0)
			rra(a);
	}
}

void	sort_large_stack(t_stack *stack_a, t_stack *stack_b)
{
	t_arr	indices;
	int		*lis_mask;

	if (!stack_a || stack_a->size <= 1)
		return ;
	indices = get_indices_array(stack_a);
	if (!indices.data)
		error_exit(stack_a, stack_b);
	lis_mask = compute_lis_mask_from_indices(indices);
	if (!lis_mask)
	{
		free(indices.data);
		error_exit(stack_a, stack_b);
	}
	push_non_lis_to_b(stack_a, stack_b, lis_mask, indices.size);
	insert_all_by_min_cost(stack_a, stack_b);
	rotate_a_to_min_index(stack_a);
	free(lis_mask);
	free(indices.data);
}
