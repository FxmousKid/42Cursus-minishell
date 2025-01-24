/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 04:42:05 by inazaria          #+#    #+#             */
/*   Updated: 2025/01/24 16:30:19 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/* The goal is to function in these 3 steps for the execution :
 * 1) iterate over all the nodes / execute them
 * 2) looping while waitpid'ing over each pid spawned
 * 3) Closing and cleaning exec related stuffproperly before 
 *    prompting user again
 */

int	wait_loop(t_data *data)
{
	int	idx;
	int	stat_loc;

	idx = 0;
	while (idx < data->cmd_count)
	{
		waitpid(data->pids[idx], &stat_loc, 0);
		printf("\n\n");
		printf("%d == Process %d exited with status %d\n",getpid(),  data->pids[idx], WEXITSTATUS(stat_loc));
		if (WIFEXITED(stat_loc))
			data->exit_code = WEXITSTATUS(stat_loc);
		idx++;
	}
	return (true);
}


int	exec(t_data *data)
{
	if (!exec_loop(data))
		return (debug(DBG("Failed to exec_loop()")), false);

	if (!wait_loop(data))
		return (debug(DBG("Failed to wait_loop()")), false);

	return (true);
}
