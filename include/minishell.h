/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:28:20 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/14 13:17:52 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <stdlib.h>
# include "libft.h"
# include <fcntl.h>

typedef struct	s_tokens
{
	char	*token;
	struct	s_tokens *next;
} t_token;

typedef struct	s_data
{
	char	*user_input;
	t_token	*tokens;
	int		command_count;
	char	***cmds;
	char	**cmd_paths;
	char	*std_input;
	char	*std_output;
	int		infile_fd;
	int		outfile_fd;
	int		**pipes;
	char	**env_paths;
	pid_t	*processes;
	int		heredoc_mode; // probably not needed
	char	*heredoc_delimeter;
	char	*heredoc_file;
	int		append_mode;
} t_data;

// error.c
void	error_and_quit(t_data *data, char *message);
void	free_data(t_data *data);
void	free_split(char **arr);
void	free_data_and_restart(t_data *data);
void	error_and_restart(t_data *data, char *message);

// lexer.c
void	lexer(t_data *data);
int		is_operator(char c);

// parser.c
void	parser(t_data *data);

// expander.c
void	expand_variables_and_remove_quotes(t_data *data);

// executor.c
void	executor(t_data *data);

// utils.c
void	*get_last_token(t_token *lst);
void	add_token(t_token **lst, t_token *new);
void	create_token(t_data *data, char *token);
int		ft_token_lstsize(t_token *lst);

//free_data.c
void	free_data(t_data *data);
void	free_double_poiter(char **arr);

//heredoc.c
void	find_heredoc_delimeter(t_data *data, t_token *token_list);
void	write_heredoc(t_data *data);

// main.c
void	minishell(void);
int		main(int argc, char **argv);

#endif
