/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:28:20 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/15 11:55:42 by louis.demet      ###   ########.fr       */
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
	char	**env;
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
	char	*heredoc_delimeter;
	int		append_mode;
} t_data;

// MAIN
void	minishell(t_data *data);
int		main(int argc, char **argv);

// CORE
void	lexer(t_data *data);
int		is_operator(char c);
void	parser(t_data *data);
void	find_heredoc_delimeter(t_data *data, t_token *token_list);
char	*write_heredoc(t_data *data);
void	expand_variables_and_remove_quotes(t_data *data);
void	executor(t_data *data);

// BUILTINS
int		find_and_trigger_builtin(t_data *data, char **cmds);
int		is_builtin(char *cmd);
void	ft_exit(t_data *data);
int		ft_cd(t_data *data, char **cmds);
int		ft_pwd(t_data *data, char **cmds);
int		ft_echo(char **cmds);
int		ft_env(t_data *data);
int		ft_unset(t_data *data, char **cmds);
int		ft_export(t_data *data, char **cmds);
void	export_single_var(t_data *data, char *cmd);

//UTILS
void	*get_last_token(t_token *lst);
void	add_token(t_token **lst, t_token *new);
void	create_token(t_data *data, char *token);
int		ft_token_lstsize(t_token *lst);
void	error_and_quit(t_data *data, char *message);
void	error_and_restart(t_data *data, char *message);
void	free_env(t_data *data);
void	free_data_and_restart(t_data *data);
void	free_data(t_data *data);
void	free_double_pointer(char **arr);
void	init_environment_paths(t_data *data);
t_data	*init_data();
void	reset_data(t_data *data);

#endif
