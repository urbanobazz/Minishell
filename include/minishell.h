/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:28:20 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/08 19:59:56 by louis.demet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>

typedef struct s_tokens
{
	char		*token;
	struct s_tokens	*next;
} t_token;

typedef struct s_data
{
	char	*user_input;
	t_token	*tokens;
} t_data;

//error.c
void	handle_error(t_data *data);

// lexer.c
void lexer(t_data *data);

//main.c
void	minishell(void);
int	main(int argc, char **argv);



#endif