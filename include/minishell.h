/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: louis.demetz <louis.demetz@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:28:20 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/16 12:47:19 by louis.demet      ###   ########.fr       */
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

# define SUCCESS 1
# define FAILURE 0
# define YES 1
# define NO 0
# define NOT_BUILTIN -1

typedef struct	s_tokens
{
	char				*token;
	struct	s_tokens 	*next;
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
	int		heredoc_mode;
	char	*heredoc_delimeter;
	char	*heredoc_file;
	int		append_mode;
	int		err_code;
} t_data;

// MAIN
void	minishell(t_data *data);
int		main(int argc, char **argv);

// CORE
void	lexer(t_data *data);
int		is_operator(char c);
int		parser(t_data *data);
void	find_heredoc_delimeter(t_data *data, t_token *token_list);
void	write_heredoc(t_data *data);
void	expand_variables_and_remove_quotes(t_data *data);
int		executor(t_data *data);

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
int		export_single_var(t_data *data, char *cmd);
char 	*ft_getenv(t_data *data, char *cmd);
int		is_name_valid(char *cmd);
void	unset_single_var(t_data *data, char *cmd);

//UTILS
void	*get_last_token(t_token *lst);
void	add_token(t_token **lst, t_token *new);
void	create_token(t_data *data, char *token);
int		ft_token_lstsize(t_token *lst);
void	error_and_quit(t_data *data, int err);
int		ft_error(t_data *data, int err);
void	free_env(t_data *data);
void	free_data(t_data *data);
void	free_double_pointer(char **arr);
void	init_environment_paths(t_data *data);
t_data	*init_data();
void	reset_data(t_data *data);


#endif
