/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inazaria <inazaria@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/10 22:42:14 by inazaria          #+#    #+#             */
/*   Updated: 2024/11/13 14:38:05 by inazaria         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <signal.h>
#include <unistd.h>

extern int g_signal_received;

void	restore_signals(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

static void	signal_handler(int signo)
{
	g_signal_received = signo;
	if (signo == SIGINT)
	{
		if (isatty(STDIN_FILENO))
		{
			rl_replace_line("", 0);
			rl_on_new_line();
			ft_err("\n");
			ft_err("\n");
			print_formatted_cwd();		
			rl_redisplay();
		}
		else
			ft_err("^C");
	}
	else if (signo == SIGQUIT)
	{
		if (isatty(STDIN_FILENO))
		{
			printf("\n");
			rl_on_new_line();
			rl_redisplay();
		}
			
	}
}

void	setup_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGQUIT, &sa, NULL);
	sigaction(SIGINT, &sa, NULL); }
