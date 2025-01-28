/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 04:49:02 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/26 02:24:28 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "macros.h"
# include "analysis.h"
# include "dependencies.h"

typedef struct s_exec_data
{
	int		pipefd[2];
	int		fd_out;
	int		fd_in;
	int		old_read_fds[FD_MAX];
	char	curr_cmd_path[4096];
}		t_exec_data;

/* Entry point to the execution loop and pidwait loop */
int		exec(t_data *data);

/* This is function that will loop over each node and execute them */
int		exec_loop(t_data *data);

int		handle_pipe(t_ast *node, t_data *data, t_exec_data *e_data);

int		correct_pipe_dup(t_ast *node, t_data *data, t_exec_data *e_data);

int		open_files(t_ast *node, t_exec_data *e_data);

int		handle_redir(t_data *data, t_ast *node, t_exec_data *e_data);

int		dup_or_cut_tree(t_ast *node, t_exec_data *e_data);

void	exec_cmd(t_ast *cmd_node, t_data *data, t_exec_data *e_data);

void	custom_name_error(char *file, char *text);

void	custom_name_perror(char *file);

void	exit_from_child(char *debug_text, t_data *data);

void	emergency_close_files(t_exec_data *e_data);

void	close_e_data(t_exec_data *e_data);

void	close_prev_command_fds(t_exec_data *e_data);

bool	write_dup_heredoc_stdin(t_ast *cmd_node, t_exec_data *e_data);

// BUILT-INS

int		check_if_builtin(t_ast *cmd_node);

int		check_and_exec_builtin(t_ast *cmd_node, t_data *data);

int		builtin_export(t_data *data, t_ast *node);

int		builtin_pwd(t_data *data, t_ast *node);

int		builtin_unset(t_data *data, t_ast *node);

void	builtin_exit(t_data *data, t_ast *cmd_node);

int		builtin_echo(t_data *data, t_ast *node);

int		builtin_cd(t_data *data, t_ast *node);

#endif
