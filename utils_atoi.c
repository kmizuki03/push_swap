/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kato <kato@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 17:20:00 by kato              #+#    #+#             */
/*   Updated: 2025/07/01 16:34:29 by kato             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	skip_space(const char *str, int *i)
{
	while (str[*i] == ' ' || (str[*i] >= 9 && str[*i] <= 13))
		(*i)++;
	return (*i);
}

static int	get_sign(const char *str, int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '-' || str[*i] == '+')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

static int	overflow_check(int result, int sign, char c)
{
	if (result > INT_MAX / 10 || (result == INT_MAX / 10 && c - '0' > INT_MAX
			% 10))
	{
		if (sign == 1)
			return (INT_MAX);
		else
			return (INT_MIN);
	}
	return (0);
}

int	ft_atoi(const char *str)
{
	int	result;
	int	sign;
	int	i;
	int	over;

	result = 0;
	i = 0;
	skip_space(str, &i);
	sign = get_sign(str, &i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		over = overflow_check(result, sign, str[i]);
		if (over)
			return (over);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
