/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 18:17:33 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/12 21:52:16 by louis.demet      ###   ########.fr       */
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
		if (*p == '$' && *(p + 1) != '\0' && (ft_isalnum(*(p + 1)) || *(p + 1) == '_'))
			return (char *)p;
		p++;
	}
	return (0);
}

char *replace_variables(const char *str)
{
	char *result = strdup(str);
	char *var_start;
	while ((var_start = find_next_variable(result)) != NULL) {
		// Extract the variable name
		char *end = var_start + 1;
		while (isalnum(*end) || *end == '_') end++;

		size_t var_name_length = end - var_start - 1;
		char var_name[var_name_length + 1];
		strncpy(var_name, var_start + 1, var_name_length);
		var_name[var_name_length] = '\0';

		// Get the variable's value
		char *value = getenv(var_name);
		if (!value) value = "";

		// Replace the variable in the result string
		size_t new_length = strlen(result) - var_name_length + strlen(value) - 1;
		char *new_result = malloc(new_length + 1);
		strncpy(new_result, result, var_start - result);
		strcpy(new_result + (var_start - result), value);
		strcpy(new_result + (var_start - result) + strlen(value), end);

		free(result);
		result = new_result;
	}

	return result;
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
				data->cmds[i][j] = replace_variables(data->cmds[i][j]);
			if (data->cmds[i][j][0] == DBL_QUOTE || data->cmds[i][j][0] == SGL_QUOTE)
			{
				data->cmds[i][j] = ft_substr(data->cmds[i][j], 1, ft_strlen(data->cmds[i][j]) - 2);
				if (!data->cmds[i][j])
					error_and_quit(data, "Not enough memory to remove quotes");
			}
			j++;
		}
		i++;
	}
}
