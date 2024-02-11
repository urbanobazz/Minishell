/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:17:33 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/11 22:13:21 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_variables(char	*str)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == '$')
			count++;
		str++;
	}
	return (count);
}

int	*get_variable_positions(t_data *data, char *str)
{
	int	i;
	int	j;
	int	*pos;
	int	var_count;

	i = 0;
	j = 0;
	var_count = count_variables(str);
	pos = malloc(sizeof(int) * (var_count + 1));
	if (!pos)
		error_and_quit(data, "Not enough memory to expand variables");
	while (j < var_count)
	{
		if (*str != '$')
			i++;
		while (*str && *str != '$')
			str++;
		if (*str == '$')
		{
			pos[j++] = i++;
			str++;
		}
	}
	pos[j] = 0;
	return (pos);
}

char	*find_variable(char **paths, char *var)
{
	
}

void	join_variables(t_data *data, char **arr, char **str)
{
	
}

void	expand_variables(t_data *data, char **str)
{
	char	**arr;
	int		i;
	int		*pos;
	char	*tmp;

	i = 0;
	pos = get_variable_positions(data, *str);
	arr = ft_split(*str, '$');
	if (!arr)
		error_and_quit(data, "Not enough memory to expand variables");
	while(pos[i] != -1)
	{
		tmp = arr[pos[i]];
		arr[i] = find_variable(data->env_paths, tmp);
		free(tmp);
		i++;
	}
	join_variables(data, arr, str);
	free_split(arr);
}

void expand_variables_and_remove_quotes(t_data *data)
{
	int i;
	int j;
	char *tmp;

	i = 0;
	while (i < data->command_count)
	{
		j = 0;
		while (data->cmds[i][j])
		{
			tmp = data->cmds[i][j];
			if (tmp[0] == DBL_QUOTE)
				expand_variables(&data->cmds[i][j]);
			if (tmp[0] == DBL_QUOTE || tmp[0] == SGL_QUOTE)
			{
				data->cmds[i][j] = ft_substr(tmp, 1, ft_strlen(tmp) - 2);
				if (!data->cmds[i][j])
					error_and_quit(data, "Not enough memory to remove quotes");
				free(tmp);
			}
			j++;
		}
		i++;
	}
}
