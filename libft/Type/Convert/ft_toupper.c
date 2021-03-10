/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgalaup <fgalaup@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 10:29:55 by fgalaup           #+#    #+#             */
/*   Updated: 2021/01/24 14:06:47 by fgalaup          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

int		ft_toupper(int c)
{
	if ('a' <= c && 'z' >= c)
		return (c - 32);
	return (c);
}
