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
# include "analysis.h"
# include "error_manager.h"
# include "macros.h"
# include "env.h"
# include "utils.h"

typedef struct s_ast t_ast;
typedef struct s_env t_env;

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






// Built in functions

int		builtin_pwd(void);
int		builtin_echo(char **arg);
int		builtin_cd(char *path);


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

#endif
