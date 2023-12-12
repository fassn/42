/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfargere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 11:25:37 by cfargere          #+#    #+#             */
/*   Updated: 2018/11/22 17:02:39 by cfargere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int					checked;
	unsigned long long	result;
	int					sign;

	checked = 0;
	result = 0;
	sign = 1;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if ((*str == '-' || *str == '+') && checked == 0)
	{
		checked = 1;
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
		result = result * 10 + *str++ - 48;
	if (result > 9223372036854775807 && sign == 1)
		return (-1);
	if (result >= 9223372036854775808uLL && sign == -1)
		return (0);
	return (result * sign);
}
