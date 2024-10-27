/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:15:11 by ptheo             #+#    #+#             */
/*   Updated: 2024/10/24 14:55:36 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signum)
{
	if (signum == SIGINT)
		return (sigint_handler(signum));
	if (signum == SIGPIPE)
		return (sigpipe_handler(signum));
}

void	sigint_handler(int signum)
{
	(void)signum;
	printf("exit cash\n");
	exit(1);
}

void	sigpipe_handler(int signum)
{
	(void)signum;
	fprintf(stdout, "catch SIGPIPE\n");
}