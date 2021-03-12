/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/12 09:55:49 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_fill_mask(char *mask, char c, int len, t_str *str_struct)
{
	printf("mask len = %d\n", len);
	while (len >= 0)
	{
		mask[len] = c;
		len--;
	}
	if (str_struct->mask == NULL)
		str_struct->mask = mask;
	else
		str_struct->mask = ft_strjoin(str_struct->mask, mask);
}

void	ft_fill_str(char *line, int j, int len, t_str *str_struct)
{
	char	*s;
	int		x;

	x = 0;
	s = malloc(sizeof(char) * len);
	while (x < len)
	{
		s[x] = line[j];
		x++;
		j++;
	}
	if (str_struct->str == NULL)
		str_struct->str = s;
	else
		str_struct->str = ft_strjoin(str_struct->str, s);
}

int	ft_single_quote(char *line, int j, t_str *str_struct)
{
	int		ret;
	char	*mask;

	ret = j + 1;
	while (line[ret] && line[ret] != '\'')
		ret++;
	mask = malloc(sizeof(char) * (ret - j - 1));
	mask[ret - j - 1] = '\0';
	ft_fill_mask(mask, '1', ret - j - 2, str_struct);
	ft_fill_str(line, j + 1, ret - j - 1, str_struct);
	return (ret + 1);
}

int	ft_double_quote(char *line, int j, t_str *str_struct)
{
	int		ret;
	char	*mask;

	ret = j + 1;
	while ((line[ret] && (line[ret] != '\"' && ret - 1 >= 0))
		|| line[ret - 1] == '\\')
		ret++;
	mask = malloc(sizeof(char) * (ret - j - 1));
	mask[ret - j - 1] = '\0';
	ft_fill_mask(mask, '2', ret - j - 2, str_struct);
	ft_fill_str(line, j + 1, ret - j - 1, str_struct);
	return (ret + 1);
}

t_sep	*ft_set_sep(char *line, int j)
{
	t_sep			*sep;

	sep = malloc(sizeof(t_sep));
	if (line[j] == '&' && line[j + 1] == '&')
		sep->id = SHELL_SEPARATOR_TYPE_AND;
	else if (line[j] == '|' && line[j + 1] == '|')
		sep->id = SHELL_SEPARATOR_TYPE_OR;
	else if (line[j] == ';')
		sep->id = SHELL_SEPARATOR_TYPE_END;
	else if (line[j] == '|')
		sep->id = SHELL_SEPARATOR_TYPE_PIPE;
	return (sep);
}

t_str	*ft_new_str_struct(void)
{
	t_str	*str_struct;

	str_struct = malloc(sizeof(t_str));
	str_struct->id = 0;
	str_struct->mask = NULL;
	str_struct->str = NULL;
	return (str_struct);
}

int	ft_separator(char *line, t_node_binary **root, int j, t_str **str_root)
{
	t_node_binary	*new_node;
	t_sep			*sep;

	sep = ft_set_sep(line, j);
	if ((*root)->value == NULL)
	{
		(*root)->value = sep;
		(*root)->left = ft_binarytree_node_create(*str_root);
	}
	else
	{
		new_node = ft_binarytree_node_create(sep);
		(*root)->right = ft_binarytree_node_create(*str_root);
		new_node->left = *root;
		*root = new_node;
	}
	*str_root = ft_new_str_struct();
	if (sep->id == SHELL_SEPARATOR_TYPE_END
		|| sep->id == SHELL_SEPARATOR_TYPE_PIPE)
		return (j + 1);
	return (j + 2);
}

int	ft_is_separator(char *line, int j)
{
	if (line[j] == '&' && line[j + 1] == '&')
		return (1);
	else if (line[j] && (line[j] == ';' || line[j] == '|'))
		return (1);
	else
		return (0);
}

int	ft_no_quote(char *line, int j, t_str *str_struct)
{
	int		ret;
	char	*mask;

	ret = j;
	while (line[ret] && line[ret] != '\"' && line[ret] != '\''
		&& ft_is_separator(line, ret) == 0)
	{
		if (line[ret] == '\\')
			ret++;
		ret++;
	}
	mask = malloc(sizeof(char) * (ret - j));
	mask[ret - j] = '\0';
	ft_fill_mask(mask, '0', ret - j - 1, str_struct);
	ft_fill_str(line, j, ret - j, str_struct);
	return (ret);
}

int	ft_show_tree(t_node_binary *root)
{
	char			node_type;
	t_node_binary	**buff;

	printf("\n\nSHOW TREE :\n\n");
	buff = &root;
	while (buff[0] != NULL)
	{
		node_type = *((char*)(buff[0]->value));
		printf("\nNodetype = %d\n", *((char*)(buff[0]->value)));
		if (*((char*)(buff[0]->value)) == 0)
			printf("\nNode str = %s\n", (((t_str *)(buff[0]->value))->str));
		if (buff[0]->left != NULL)
		{
			printf("\nLeft_Nodetype = %d\n", *((char*)(buff[0]->left->value)));
			printf("\nRight_Nodetype = %d\n", *((char*)(buff[0]->right->value)));
			if (*((char*)(buff[0]->left->value)) == 0)
				printf("\nstr left = %s\n", (((t_str *)(buff[0]->left->value))->str));
			if (*((char*)(buff[0]->right->value)) == 0)
				printf("\nstr right= %s\n", (((t_str *)(buff[0]->right->value))->str));
			buff = &buff[0]->left;
		}
		else
			buff[0] = NULL;
	}
	return (0);
}

t_parse_struct	*ft_setup_parse_struct(void)
{
	t_parse_struct	*ret;

	ret = malloc(sizeof(t_parse_struct));
	ret->str_struct = malloc(sizeof(t_str));
	ret->str_struct->id = 0;
	ret->str_struct->mask = NULL;
	ret->str_struct->str = NULL;
	ret->root = malloc(sizeof(t_node_binary *));
	ret->str_root = malloc(sizeof(t_str *));
	ret->node = ft_binarytree_node_create(NULL);
	ret->str_root[0] = ret->str_struct;
	ret->root[0] = ret->node;
	return (ret);
}

t_node_binary	*ft_treat_line(char *line)
{
	int				i;
	int				j;
	t_parse_struct	*s;

	s = ft_setup_parse_struct();
	i = ft_strlen(line);
	j = 0;
	while (line[j])
	{
		if (ft_is_separator(line, j) == 1)
			j = ft_separator(line, s->root, j, s->str_root);
		if (line[j] != '\'' && line[j] != '\"')
			j = ft_no_quote(line, j, s->str_root[0]);
		else if (line[j] == '\'')
			j = ft_single_quote(line, j, s->str_root[0]);
		else if (line[j] == '\"')
			j = ft_double_quote(line, j, s->str_root[0]);
	}
	if ((s->root[0])->value == NULL)
		(s->root[0])->value = (s->str_root[0]);
	else if ((s->root[0])->right == NULL)
		(s->root[0])->right = ft_binarytree_node_create((s->str_root[0]));
	return (s->root[0]);
}

int	main(void)
{
	char			**line;
	char			*prompt;
	int				ret;
	t_node_binary	*root;

	ret = 0;
	line = malloc(sizeof(char **));
	prompt = malloc(sizeof(char) * 12);
	if (line == NULL || prompt == NULL)
		return (0);
	prompt = "\e[1;1H\e[2J";
	write(1, prompt, 11);
	prompt = "Minishell ~ ";
	while (ret >= 0)
	{
		write(1, prompt, 12);
		ret = get_next_line(0, line);
		root = ft_treat_line(*line);
		ft_show_tree(root);
		free(*line);
	}
	return (1);
}
