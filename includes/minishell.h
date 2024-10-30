/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:35:10 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/27 16:09:29 by inazaria         ###   ########.fr       */
/*   Updated: 2024/10/24 14:46:36 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "dependencies.h"
# include "error_manager.h"
# include "analysis.h"

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

# define SH_NAME "cash"
# define SH_NAME_FANCY GREEN_TXT"ca"END_TXT"@"GREEN_TXT"sh 💵 "END_TXT
# define PS1 SH_NAME_FANCY PURPLE_TXT"❯ "END_TXT

# define PATH_MAX 4096
# define ENV_MAX 4096
# define CMD_MAX 256
# define ARG_MAX 4096

typedef struct s_env_pair
{
	char	*key;
	char	*value;
}			t_env_pair;

typedef struct s_env
{
	t_env_pair	env_pairs[ENV_MAX];
	int			env_len;
}				t_env;

typedef struct s_ast t_ast;

typedef struct s_data
{
	t_env		*env;
	t_ast		*ast;
	int			pipe[2];
	int			cmd_count;
	int			*tab_fd;
	int			fd[2];
	char		**envir;
	char		**path_arg;
}				t_data;

/* Utils functions */
bool	is_occ(char *str, char *sep);
bool	is_occ_aux(char c, char *sep);
void	print_split(char **split);
int		count_words_mod(char *str, char *sep);
int		strcmp_ex(const char *s1, const char *s2);

// Environnement

/* fills up out custom made structure with the system provided env */
bool	init_env(t_env *data_env, char *env[]);

/* Free the key and value of each env entry in the passed t_env */
void	free_env(t_env *env);

/* Returns the ptr to the value of the key if found, else returns NULL */
char	*access_env_value(t_env *env, char *key);

/* if key already is a env entry key, then overwrites existing value with 
 * passed value, leaves total entry count the same
 * else append a new env entry, allocated for key and value with MALLOC, and
 * increments the total entry counts by 1 */
void	add_env_entry(t_env *env, char *key, char *value);

/* Takes a key, and removes that entry, and shift everything on the right
 * of that entry 1 place to the left, to remain contiguous.
 * Does nothing if key isn't found / valid */
void	remove_env_entry(t_env *env, char *key);

/* Pretty prints the current state of the passed t_env structure */
void	print_env(t_env env);


// Built in functions

int		builtin_pwd(void);
int		builtin_echo(char **arg);
int		builtin_cd(char *path);

/* printing */
void	print_formatted_cwd(void);
void	print_start_text(void);

/* execution */
int		exec_cmd(t_data *data, t_ast *cmd);
int		create_path(t_data *data);
t_ast	*test_cmd(t_data *data, t_ast *ast);
void	print_ast(t_ast *ast);
char	*find_access(t_data *data, char *cmd);

/* processes */
int		cmd_process(t_data *data, t_ast *cmd);
int		find_process(t_data *data, t_ast *pro);
int		pipe_process(t_data *data, t_ast *pipe);
int		or_process(t_data *data, t_ast *or);
int		and_process(t_data *data, t_ast *and);

/* signal */
void	sig_handler(int signum);
void	sigint_handler(int signum);
void	sigpipe_handler(int signum);

#endif
