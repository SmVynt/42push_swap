/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lib.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psmolin <psmolin@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:35:02 by psmolin           #+#    #+#             */
/*   Updated: 2025/06/10 14:09:08 by psmolin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	ft_print(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
	}
	return (len);
}

/**
 * @brief function that gives n's digit of num
 * in the base 2.
 *
 * @param num The number to convert.
 * @param n The digit position
 * (0 for the rightest bit).
 *
 * @return Returns the n-th digit of num in base 2.
 */
int	ft_num2n(int num, int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		num = num / 2;
	return (num % 2);
}

/**
 * @brief function that gives n's digit of num
 * in the base 3.
 *
 * @param num The number to convert.
 * @param n The digit position
 * (0 for the rightest bit).
 *
 * @return Returns the n-th digit of num in base 2.
 */
int	ft_num3n(int num, int n)
{
	int	i;

	i = 0;
	while (i++ < n)
		num = num / 3;
	return (num % 3);
}

int	ft_strncmp(const char *s1, const char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (s1[i] && (s1[i] == s2[i]) && i < n)
		i++;
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
