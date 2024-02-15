/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:17:33 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/15 12:22:59 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char	*find_next_variable(const char *str)
{
	const char	*p;

	p = str;
	while (*p)
	{
		if (*p == '$' && *(p + 1) != '\0' && (ft_isalnum(*(p + 1)) 
			|| *(p + 1) == '_'))
			return (char *)p;
		p++;
	}
	return (0);
}

char	*get_variable_value(t_data *data, char *var_start, int var_name_length)
{
	char	*var_name;
	char	*value;

	var_name = ft_substr(var_start + 1, 0, var_name_length);
	value = ft_getenv(data, var_name);
	if (!value)
		value = "";
	free(var_name);
	return (value);
}

char *replace_next_variable(char *result, char *value, char *var_end, char *var_start)
{
	char	*new_result;

	new_result = ft_substr(result, 0, var_start - result);
	new_result = ft_strjoin(new_result, value);
	new_result = ft_strjoin(new_result, var_end);
	return (new_result);
}

char *replace_variables(t_data *data, const char *str)
{
	char	*result;
	char	*var_start;
	char	*var_end;
	char	*value;

	result = strdup(str);
	while (find_next_variable(result))
	{
		var_start = find_next_variable(result);
		var_end = var_start + 1;
		while (isalnum(*var_end) || *var_end == '_')
			var_end++;
		value = get_variable_value(data, var_start, var_end - var_start - 1);
		result = replace_next_variable(result, value, var_end, var_start);
	}

	return (result);
}

void expand_variables_and_remove_quotes(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (i < data->command_count)
	{
		j = 0;
		while (data->cmds[i][j])
		{
			if (data->cmds[i][j][0] != SGL_QUOTE)
				data->cmds[i][j] = replace_variables(data, data->cmds[i][j]);
			if (data->cmds[i][j][0] == DBL_QUOTE || data->cmds[i][j][0] == SGL_QUOTE)
			{
				data->cmds[i][j] = ft_substr(data->cmds[i][j],
											1, 
											ft_strlen(data->cmds[i][j]) - 2);
				if (!data->cmds[i][j])
					error_and_quit(data, "Not enough memory to remove quotes");
			}
			j++;
		}
		i++;
	}
}
