/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:17:33 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/24 20:57:32 by louis.demet      ###   ########.fr       */
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
				|| *(p + 1) == '_' || *(p + 1) == '?'))
			return ((char *)p);
		p++;
	}
	return (FAILURE);
}

char	*get_variable_value(t_data *data, char *var_start, int var_name_length)
{
	char	*var_name;
	char	*value;

	var_name = ft_substr(var_start + 1, 0, var_name_length);
	if (var_name[0] == '?')
		value = ft_itoa(data->exit_status);
	else
		value = ft_strdup(ft_getenv(data, var_name));
	if (!value)
		value = ft_calloc(sizeof(char *), 1);
	if (!value)
		error_and_quit(data, 2);
	free(var_name);
	return (value);
}

char	*replace_next_variable(char *result, char *value, char *var_end,
	char *var_start)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_substr(result, 0, var_start - result);
	tmp2 = ft_strjoin(tmp1, value);
	free(tmp1);
	tmp1 = ft_strjoin(tmp2, var_end);
	free(tmp2);
	return (tmp1);
}

char	*replace_variables(t_data *data, char **str)
{
	char	*result;
	char	*var_start;
	char	*var_end;
	char	*value;
	char	*tmp;

	result = ft_strdup(*str);
	free(*str);
	while (find_next_variable(result))
	{
		var_start = find_next_variable(result);
		var_end = var_start + 1;
		if (*var_end == '?')
			var_end++;
		else
		{
			while (isalnum(*var_end) || *var_end == '_')
				var_end++;
		}
		value = get_variable_value(data, var_start, var_end - var_start - 1);
		tmp = result;
		result = replace_next_variable(tmp, value, var_end, var_start);
		free(tmp);
		free(value);
	}
	return (result);
}

void	expand_variables_and_remove_quotes(t_data *data)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (i < data->command_count)
	{
		j = 0;
		while (data->cmds[i][j])
		{
			if (data->cmds[i][j][0] != SGL_QUOTE)
				data->cmds[i][j] = replace_variables(data, &data->cmds[i][j]);
			if (data->cmds[i][j][0] == DBL_QUOTE
				|| data->cmds[i][j][0] == SGL_QUOTE)
			{
				tmp = remove_quotes(data->cmds[i][j]);
				if (!tmp)
					error_and_quit(data, 2);
				free(data->cmds[i][j]);
				data->cmds[i][j] = tmp;
			}
			j++;
		}
		i++;
	}
}

char	*remove_quotes(char *str)
{
	char	*tmp;
	char	*output;
	char	*c;

	output = ft_strdup("");
	while (*str)
	{
		if (*str != SGL_QUOTE && *str != DBL_QUOTE)
		{
			c = ft_substr(str, 0, 1);
			tmp = ft_strjoin(output, c);
			free(output);
			free(c);
			output = tmp;
		}
		str++;
	}
	return (output);
}
