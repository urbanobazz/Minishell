/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:28:20 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/09 20:17:02 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>

typedef struct s_tokens
{
	char			*token;
	struct s_tokens	*next;
} t_token;

typedef struct s_data
{
	char		*user_input;
	t_token		*tokens;
	int			command_count;
	char		**commands;
	char		*std_input;
	char		*std_output;
	int			infile_fd;
	int			outfile_fd;
	int			**pipes;
	pid_t		*processes;
} t_data;

// error.c
void	handle_error(t_data *data);
void	free_data(t_data *data);

// lexer.c
void	lexer(t_data *data);
int		is_operator(char c);

// parser.c
void	parser(t_data *data);

//executor.c
void	executor(t_data *data);

// main.c
void	minishell(void);
int		main(int argc, char **argv);

#endif
