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
#include "parser.h"
#include "utils.h"

// Every return code starting from here and down, will signify a exit code

int	minishell(char *readline_input, t_env *data_env, int *exit_code_dspl)
{
	static t_data	data = {0};

	data.env = data_env;
	if (!readline_input || !*readline_input || !data.env)
		return (debug(DBG("Received null in readline")), 0);
	if (data.env->global_cmd_number == 0)
		free_and_init_data(&data, NULL);
	data.env->global_cmd_number++;
	lexer(&data.lex, readline_input);
	if (!parser(&data, &data.lex))
	{
		*exit_code_dspl = data.exit_code;
		return (debug(DBG("Failed to parser()")), 0);
	}
	if (!exec(&data))
	{
		free_and_init_data(&data, readline_input);
		*exit_code_dspl = data.exit_code;
		return (debug(DBG("Failed to exec()")), 0);
	}
	data.prev_exit_code = data.exit_code;
	*exit_code_dspl = data.exit_code;
	return (free_and_init_data(&data, readline_input), 0);
}

int	launch_minishell(char *env[])
{
	t_env	*data_env;
	char	*input;
	int		status;
	int		exit_code_display;

	data_env = ft_calloc(sizeof(t_env), 1);
	init_env(data_env, env);
	input = read_command(0);
	while (input)
	{
		exit_code_display = 0;
		add_history(input);
		status = minishell(input, data_env, &exit_code_display);
		if (status)
			break ;
		input = read_command(exit_code_display);
	}
	printf("exit\n");
	return (free_env(data_env), 0);
}

int		g_signal_received = 0;

// extern int	rl_catch_signals;
// to check when veryging singnals

int	main(int argc, char *argv[], char *env[])
{
	int	minishell_status;

	rl_catch_signals = 0;
	(void) argc;
	(void) argv;
	init_readline();
	setup_signals();
	minishell_status = launch_minishell(env);
	return (minishell_status);
}

int	main(void)
{
	int	minishell_status;

	minishell_status = minishell();
	return (minishell_status);
}
