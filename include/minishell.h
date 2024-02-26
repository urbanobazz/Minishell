/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubazzane <ubazzane@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 18:28:20 by louis.demet       #+#    #+#             */
/*   Updated: 2024/02/26 15:19:32 by ubazzane         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <string.h>
# include "libft.h"
# include <fcntl.h>

# ifdef __linux__
#  include <bits/sigaction.h>
#  include <bits/types/siginfo_t.h>
# endif

# define SUCCESS 1
# define FAILURE 0
# define YES 1
# define NO 0
# define NOT_BUILTIN -1
# define COMMAND_SUCCESS 0

extern int	g_end_heredoc;

typedef struct s_tokens
{
	char				*token;
	struct s_tokens		*next;
}	t_token;

typedef struct s_data
{
	char	**env;
	int		exit_status;
	char	**env_paths;
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
	pid_t	*processes;
	int		heredoc_mode;
	t_list	*heredoc_delimiters;
	char	*heredoc_file;
	int		append_mode;
}	t_data;

// MAIN
void	minishell(t_data *data);
int		main(int argc, char **argv);

// CORE
int		lexer(t_data *data);
int		is_operator(char c);
int		parser(t_data *data);
void	find_heredoc_delimiter(t_data *data, t_token *token_list);
int		write_heredoc(t_data *data);
void	expand_variables_and_remove_quotes(t_data *data);
void	remove_quotes(char *str, char **output);
int		executor(t_data *data);
void	interactive_signals(void);
void	non_interactive_signals(void);
void	heredoc_interrupt_signal(void);
void	init_pipes(t_data *data);
int		init_redirections(t_data *data);
void	close_all_pipes(t_data *data);
void	get_input_output(t_data *data, int i, int io[2]);
void	process_segment(t_data *data, char *str, size_t *i, int len);
char	*ft_get_next_word(char *str);
void	cycle_command_paths(t_data *data, int i);
int		find_command_paths(t_data *data);
int		backup_redirection(t_data *data, int i, int io[2], int tmp_fd[2]);
void	restore_redirection(t_data *data, int i, int io[2], int tmp_fd[2]);

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
char	*ft_getenv(t_data *data, char *cmd);
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
void	free_triple_pointer(char ***arr);
void	free_tokens(t_token **tokens, void (*del)(void*));
void	free_pipes(t_data *data, int **arr);
void	init_environment_paths(t_data *data);
t_data	*init_data(void);
void	reset_data(t_data *data);
char	**split_commands(char *str, t_data *data);

#endif
