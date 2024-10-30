/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:30:29 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/25 18:41:45 by inazaria         ###   ########.fr       */
/*   Updated: 2024/10/24 14:49:56 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_readline(void)
{
	rl_bind_key('!', rl_insert);
	using_history();
}

int	minishell(void)
{
	char	*cmd;
	int		history_count;
	t_lexer	lex;

	history_count = 0;
	init_readline();
	ft_bzero(&lex, sizeof(t_lexer));
	while (history_count < 20)
	{
		printf("\n");
		print_prompt();
		cmd = readline(PROMPT_LINE);
		if (!cmd)
			break ;
		lexer(&lex, cmd);
		free_lex(&lex);
		ft_bzero(&lex, sizeof(t_lexer));
		add_history(cmd);
		history_count++;
		free(cmd);
	}
	clear_history();
	return (0);
}

int	main(void)
{
	int	minishell_status;

	minishell_status = minishell();
	return (minishell_status);
}
