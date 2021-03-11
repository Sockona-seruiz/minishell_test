/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/11 11:53:15 by seruiz           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
int	ft_add_spaces(char *s, int x, char c, char v)
{
	s[x] = ' ';
	s[x + 1] = c;
	if (v != '\0')
	{
		s[x + 2] = v;
		s[x + 3] = ' ';
		return (x + 3);
	}
	else
		s[x + 2] = ' ';
	return (x + 2);
}

char	*ft_get_blocks(char *line, int i, int compt, int n)
{
	int		j;
	char	*s;
	int		x;

	x = 0;
	j = i + compt * 2;
	s = malloc(sizeof(char) * (j + 1));
	if (s == NULL)
		return (0);
	while (n <= i)
	{
		if (line[n] == '|')
		{
			if (n < i - 1 && line[n + 1] == '|')
			{
				x = ft_add_spaces(s, x, '|', '|');
				n++;
			}
			else
				x = ft_add_spaces(s, x, '|', '\0');
		}
		else if (line[n] == '&')
		{
			if (n < i - 1 && line[n + 1] == '&')
			{
				x = ft_add_spaces(s, x, '&', '&');
				n++;
			}
		}
		else if (line[n] == ';')
			x = ft_add_spaces(s, x, line[n], '\0');
		else
			s[x] = line[n];
		x++;
		n++;
	}
	//s[x] = '\0';
	return (s);
}

char	*ft_test(char *line, int i)
{
	int		j;
	int		compt;
	int		n;

	n = 0;
	compt = 0;
	j = 0;
	while (j < i)
	{
		if (line[j] == '|')
		{
			if (j < i - 1 && line[j + 1] == '|')
				j += 2;
			else
				j++;
			compt += 1;
		}
		else if (line[j] == '&')
		{
			if (j < i - 1 && line[j + 1] == '&')
				j += 2;
			else
				j++;
			compt += 1;
		}
		else if (line[j] == ';')
			compt += 1;
		j++;
	}
	printf("found %d separators\n", compt);
	return (ft_get_blocks(line, i, compt, n));
}

int	ft_treat_line(char **line)
{
	int	i;
	int	j;
	char	**test;
	char	*s;

	j = 0;
	i = ft_strlen(*line);
	s =ft_test(*line, i);
	//printf("line len = %d\n", i);
	test = ft_split(s, ' ');
	while (test[j])
	{
		printf("%s\n", test[j]);
		j++;
	}
	return (1);
}

int	ft_treat_quotes(char *line, int i, int j, int ret)
{
	
}

int	ft_treat_sep(char *line, int i, int j, t_node *node)
{
	int ret;
	t_sep	*separator;

	ret = j;
	separator = malloc(sizeof(t_sep));
	while (ret < i)
	{
		if (line[ret] == '\'' || line[ret] == '\"')
			return (ret + ft_treat_quotes(line, i, j, ret));
		else if (line[ret] == '|' || line[ret] == ';' || line[ret] == '&')
		{
			if (ret + 1 < i && line[ret + 1] == '|')
			{
				
			}
		}
	}
}

int ft_treat_line(char *line, t_node *node)
{
	int	i;
	int	j;
	int	ret;

	i = ft_strlen(line);
	j = 0;
	while (j < i)
	{
		ret = ft_treat_sep(line, i, j, node);
		if (ret > 0)
			j += ret;
		else
		{
			ret = ft_treat_command(line, i, j, node);
			if (ret > 0)
				j += ret;
		}
		//printf("%c", line[j]);
		//j++;
	}
	printf("\n");
}
*/

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
	printf("mask = %s\n", str_struct->mask);
}

void	ft_fill_str(char *line, int j, int len, t_str *str_struct)
{
	char *s;
	int x;

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
	printf("str = %s\n", str_struct->str);
}

int	ft_single_quote(char *line, t_node_binary *node, int j, t_str *str_struct)
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

int	ft_double_quote(char *line, t_node_binary *root, int j, t_str *str_struct)
{
	int		ret;
	char	*mask;

	ret = j + 1;
	while ((line[ret] && (line[ret] != '\"' && ret - 1 >= 0)) || line[ret - 1] == '\\')
		ret++;
	mask = malloc(sizeof(char) * (ret - j - 1));
	mask[ret - j - 1] = '\0';
	ft_fill_mask(mask, '2', ret - j - 2, str_struct);
	ft_fill_str(line, j + 1, ret - j - 1, str_struct);
	return (ret + 1);
}

int	ft_separator(char *line, t_node_binary **root, int j, t_str *str_struct)
{
	t_node_binary	*new_node;
	t_sep			*sep;

	sep = malloc(sizeof(t_sep));
	sep->id = 1;

	if (root[0]->value == NULL)
	{
		printf("Node value == NULL\n");
		root[0]->value = sep;
		printf("\nFirst Nodetype = %c\n", *((char*)(root[0]->value)));
		root[0]->left = ft_binarytree_node_create(str_struct);
		printf("\nFirst Nodetype left = %c\n", *((char*)(root[0]->left->value)));
	}

	else
	{
		printf("cree un nouveau noeud au dessus\n");
		new_node = ft_binarytree_node_create(sep);
		root[0]->right = ft_binarytree_node_create(str_struct);
		new_node->left = *root;
		printf("Adresse new_node = %p\nAdresse old_node = %p\n", &new_node, &*root);
		root = &new_node;
		printf("Nouvelle adresse root = %p\n", &*root);
	}

	printf("\nNodetype = %c\n", *((char*)(root[0]->value)));

	free(str_struct);
	str_struct = malloc(sizeof(t_str));
	str_struct->id = 0;
	str_struct->mask = NULL;
	str_struct->str = NULL;

	//new_node = ft_binarytree_node_create(str_struct);
	
	/*
	if (node->left != NULL && node->right != NULL && node->value != NULL)
	{
		new_node->left = node;
		new_node->value = sep;
		node = new_node;
		node->right = str_struct;
	}
	else if (node->right == NULL && node->left != NULL)
	{
		new_node->value = str_struct;
		node->right = new_node;
	}
	else //cas où c'est le premier node
	{
		node->value = sep;
		new_node->value = str_struct;
		node->right = new_node;
		node = new_node;
	}
	*/
	//Fill l'arbre binaire ICI
	/*
	if (node->left == NULL)
		node->left = new_node;
	else if (node->right == NULL)
		node->right = new_node;
	else
		//il faut remonter dans l'arbre et raccrocher l'ancien maillon à "left" du nouveau
	*/


	//str_struct->str = NULL;
	//str_struct->mask = NULL;
	if ((line[j] == '&' && line[j + 1] == '&') || (line[j] == '|' && line[j + 1] == '|'))
	{
		printf("double sep\n");
		return (j + 2);
	}
	else if (line[j] && (line[j] == ';' || line[j] == '|'))
	{
		printf("single sep\n");
		return (j + 1);
	}
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

int	ft_no_quote(char *line, t_node_binary *node, int j, t_str *str_struct)
{
	int		ret;
	char	*mask;

	ret = j;
	while (line[ret] && line[ret] != '\"' && line[ret] != '\'' && ft_is_separator(line, ret) == 0) //Ajouter condition pour checker les separateurs
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

int	ft_show_tree(t_node_binary **root)
{
	char	node_type;

	node_type = *((char*)(root[0]->value));
	printf("\nNodetype = %d\n", node_type);


	/*
	if (node_type == SHELL_INSTRUCTION_COMMAND)
		return (instruction_command(context, node));
	else if (node_type == SHELL_INSTRUCTION_BUILTIN)
		return (instruction_builtin(context, node));
	else if (node_type == SHELL_INSTRUCTION_UNKNOWN)
		return (404);
	else
		return (run_separator(context, node_type, node));
	*/
	return (0);
}

int	ft_treat_line(char *line)
{
	int				i;
	int				j;
	t_node_binary	**root;
	t_node_binary	*node;
	t_str			*str_struct;

	str_struct = malloc(sizeof(t_str));
	str_struct->id = 0;
	str_struct->mask = NULL;
	str_struct->str = NULL;
	root = malloc(sizeof(t_node_binary *));
	node = ft_binarytree_node_create(NULL);
	root[0] = node;
	printf("First Adress = %p\n", &root[0]);
	i = ft_strlen(line);
	j = 0;
	while (line[j])
	{
		if (ft_is_separator(line, j) == 1)
			j = ft_separator(line, root, j, str_struct);
		if (line[j] != '\'' && line[j] != '\"')
		{
			printf("No Quotes :\n");
			j = ft_no_quote(line, *root, j, str_struct);
			printf("exit j = %d\n", j);
		}
		else if (line[j] == '\'')
		{
			printf("Single Quotes :\n");
			j = ft_single_quote(line, *root, j, str_struct);
			printf("exit j = %d\n", j);
		}
		else if (line[j] == '\"')
		{
			printf("Double Quotes :\n");
			j = ft_double_quote(line, *root, j, str_struct);
			printf("exit j = %d\n", j);
		}
	}
	if (root[0]->value == NULL)
		root[0]->value = str_struct;
	printf("line = %s\n", line);
	ft_show_tree(root);
}

int	main(void)
{
	char	**line;
	char	*prompt;
	int		ret;

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
		ft_treat_line(*line);
		free(*line);
	}
	return (1);
}
