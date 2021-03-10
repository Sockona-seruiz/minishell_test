/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 09:36:56 by fgalaup           #+#    #+#             */
/*   Updated: 2021/01/24 14:07:47 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if (('a' <= c && 'z' >= c) ||
		('A' <= c && 'Z' >= c) ||
		('0' <= c && '9' >= c))
		return (1);
	return (0);
}