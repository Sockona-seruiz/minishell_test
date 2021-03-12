/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:19:53 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/11 15:56:39 by seruiz           ###   ########lyon.fr   */
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

enum			e_shell_instruction_type
{
	SHELL_INSTRUCTION_UNKNOWN,
	SHELL_INSTRUCTION_COMMAND,
	SHELL_INSTRUCTION_BUILTIN,
	// SHELL_INSTRUCTION_SEPARATOR,
	// SHELL_SEPARATOR_TYPE_UNKNOWN,
	SHELL_SEPARATOR_TYPE_END,
	SHELL_SEPARATOR_TYPE_PIPE,
	SHELL_SEPARATOR_TYPE_AND,
	SHELL_SEPARATOR_TYPE_OR,
	SHELL_SEPARATOR_TYPE_ASSIGNMENT,
	SHELL_SEPARATOR_TYPE_REDIRECT_LEFT,
	SHELL_SEPARATOR_TYPE_REDIRECT_RIGHT,
	SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_LEFT,
	SHELL_SEPARATOR_TYPE_REDIRECT_DOUBLE_RIGHT,
	SHELL_STRING,
};

typedef struct	s_str
{
	char	id;
	char	*str;
	char	*mask;
}				t_str;

typedef struct	s_parsing_struct
{
	t_node_binary	**root;
	t_node_binary	*node;
	t_str			**str_root;
	t_str			*str_struct;
}					t_parse_struct;


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

typedef struct	s_block
{
	int			type;
	int			atribute;
	struct s_block		*next;
}				t_block;

#endif