/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 04:49:02 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/13 17:52:48 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "macros.h"
# include "analysis.h"
# include "dependencies.h"

typedef struct s_exec_data
{
	int	pipefd[2];
	int	fd_out;
	int	fd_in;
	int	old_read_fds[FD_MAX];
}		t_exec_data;

/* Entry point to the execution loop and pidwait loop */
int		exec(t_data *data);

/* This is function that will loop over each node and execute them */
int		exec_loop(t_data *data);

/* This function open the files in the correct based on the token
 * of the passed node
 * if files fails to open (open returns < 0), this function doesn't care
 * since its role is just to open
 * doesn't close anything, just opens
 * */
void	check_to_open_files(t_ast *node, t_exec_data *e_data);


/* Opens the pipe for a pipe node, and assigns them to e_data 
 * if pipe() fails, this function doesn't care since its role 
 * is only to open them
 * be sure to check afterwards */
void	check_to_open_pipe(t_ast *node, t_exec_data *e_data);



#endif
