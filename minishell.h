/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:19:53 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/10 13:23:30 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#define PIPE = 9;

# include "get_next_line/get_next_line.h"
# include "libft/libft.h"

enum BLOCKS
{
	CMD,
	SEMICOLON,
};

typedef struct	s_sep_pos
{
	int i;
	struct s_sep_pos	*next;
}				t_sep_pos;

typedef struct	s_node
{
	void	*value;
	struct s_val	*left;
	struct s_val	*right;
}				t_node;

typedef struct	s_separator
{
	char	id;
}				t_sep;

typedef struct	s_str
{
	char	id;
	char	*s;
	char	*mask;
}				t_str;

typedef struct	s_block
{
	int			type;
	int			atribute;
	struct s_block		*next;
}				t_block;

#endif