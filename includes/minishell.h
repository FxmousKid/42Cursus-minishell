/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:35:10 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/18 19:33:37 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"
# include "error_manager.h"
# include "lexer.h"

# define RED_TXT		"\e[0;31m"
# define GREEN_TXT		"\e[0;32m"
# define YELLOW_TXT		"\e[0;33m"
# define BLUE_TXT		"\e[0;34m"
# define PURPLE_TXT		"\e[0;35m"
# define CYAN_TXT		"\e[0;36m"
# define GREY_TXT		"\e[0;37m"
# define WHITE_TXT		"\e[0;39m"
# define BOLD_TXT		"\e[1m"
# define UNDERLINE_TXT	"\e[4m"
# define REVERSE_TXT	"\e[7m"
# define HIDDEN_TXT		"\e[8m"
# define END_TXT		"\e[0m"

# define PROMPT "\e[0;35m❯\e[0m "
# define SH_NAME "cash"
# define PROMPT_SH_NAME "\e[0;32mca\e[0m@\e[0;32msh\e[0m"
# define MAX_PATH 4096
# define MAX_CMD 256
# define MAX_ARG 4096
# define MAX_TOKEN 4096

typedef struct s_env_pair
{
	char	*key[4096];
	char	**value;
}			t_env_pair;

typedef struct s_data
{
	t_env_pair	*env;
	t_ast		*ast;
	int			pipe[2];
	int			cmd_count;
	int			*tab_fd;
	int			fd[2];
	char		**envir;
	char		**path_arg;
}				t_data;

/* BUILD IN */
int		builtin_pwd(void);
int		builtin_echo(char **arg);
int		builtin_cd(char *path);

/* PRINT */
void	print_prompt(void);
void	print_start_text(void);

/* EXEC */
int		exec_cmd(t_data *data, t_ast *cmd);
int		create_path(t_data *data);
t_ast	*test_cmd(t_data *data, t_ast *ast);
void	print_ast(t_ast *ast);
char	*find_access(t_data *data, char *cmd);

/* PROCESS */
int		cmd_process(t_data *data, t_ast *cmd);
int		find_process(t_data *data, t_ast *pro);
int		pipe_process(t_data *data, t_ast *pipe);
int		or_process(t_data *data, t_ast *or);
int		and_process(t_data *data, t_ast *and);

#endif
