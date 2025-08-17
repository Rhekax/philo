/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdursun <mdursun@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 20:39:41 by mdursun           #+#    #+#             */
/*   Updated: 2025/08/17 20:51:16 by mdursun          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_isdigit(int c)
{
	if (c < 58 && c > 47)
		return (1);
	return (0);
}

static void	check_overflow(long digit, long result, long sign)
{
	if (sign == -1 && result > (2147483648 - digit) / 10)
		exit(EXIT_FAILURE);
	else if (sign == 1 && result > (2147483647 - digit) / 10)
		exit(EXIT_FAILURE);
}

int	ft_atoi(const char *str)
{
	long	result;
	long	sign;
	long	digit;

	sign = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == 45 || *str == 43)
	{
		if (*str == 45)
			sign = -1;
		str++;
	}
	if (!ft_isdigit(*str))
		exit(EXIT_FAILURE);
	while (*str >= 48 && *str <= 57)
	{
		digit = *str - 48;
		check_overflow(digit, result, sign);
		result = result * 10 + digit;
		str++;
	}
	return (result * sign);
}
