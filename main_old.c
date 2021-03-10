/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seruiz <seruiz@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 13:18:34 by seruiz            #+#    #+#             */
/*   Updated: 2021/03/09 16:13:49 by seruiz           ###   ########lyon.fr   */
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
*/

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

int	main(void)
{
	char	**line;
	char	*prompt;
	int		ret;
	t_node	*node;

	ret = 0;
	node = malloc(sizeof(t_node *));
	line = malloc(sizeof(char **));
	prompt = malloc(sizeof(char) * 12);
	if (line == NULL || prompt == NULL || node == NULL)
		return (0);
	prompt = "\e[1;1H\e[2J";
	write(1, prompt, 11);
	prompt = "Minishell ~ ";
	while (ret >= 0)
	{
		write(1, prompt, 12);
		ret = get_next_line(0, line);
		ft_treat_line(*line, node);
		//ft_treat_line(line);
		free(*line);
	}
	return (1);
}
