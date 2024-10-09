/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:35:10 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/09 19:56:06 by ptheo            ###   ########.fr       */
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


# define START_TEXT_1  "\e[0;32m          _____                    _____                    _____                    _____ 	\n"
# define START_TEXT_2  "         /\\    \\                  /\\    \\                  /\\    \\                  /\\    \\	                                        ..                              \n"
# define START_TEXT_3  "        /::\\    \\                /::\\    \\                /::\\    \\                /::\\____\\	                                    .:::::::.                           \n"
# define START_TEXT_4  "       /::::\\    \\              /::::\\    \\              /::::\\    \\              /:::/    /	                        .....     .:...:....:-.                         \n"
# define START_TEXT_5  "      /::::::\\    \\            /::::::\\    \\            /::::::\\    \\            /:::/    /	                     .........  .:....:-:....===:                       \n"
# define START_TEXT_6  "     /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/\\:::\\    \\          /:::/    /	                    .......:::.:-:...........:==--.                     \n"
# define START_TEXT_7  "    /:::/  \\:::\\    \\        /:::/__\\:::\\    \\        /:::/__\\:::\\    \\        /:::/____/	                     ......:::...::---:.....---===.                     \n"
# define START_TEXT_8  "   /:::/    \\:::\\    \\      /::::\\   \\:::\\    \\       \\:::\\   \\:::\\    \\      /::::\\    \\	                      ....::::.:-:.::--:..---=====.                     \n"
# define START_TEXT_9  "  /:::/    / \\:::\\    \\    /::::::\\   \\:::\\    \\    ___\\:::\\   \\:::\\    \\    /::::::\\    \\   _____                        ..  ...=$-=$-.:::--==-:.                        \n"
# define START_TEXT_10 " /:::/    /   \\:::\\    \\  /:::/\\:::\\   \\:::\\    \\  /\\   \\:::\\   \\:::\\    \\  /:::/\\:::\\    \\ /\\    \\	                     .:..$=$=$=...::-:.                           \n"
# define START_TEXT_11 "/:::/____/     \\:::\\____\\/:::/  \\:::\\   \\:::\\____\\/::\\   \\:::\\   \\:::\\____\\/:::/  \\:::\\    /::\\____\\	                    .::::::.-$-...::.                             \n"
# define START_TEXT_12 "\\:::\\    \\      \\::/    /\\::/    \\:::\\  /:::/    /\\:::\\   \\:::\\   \\::/    /\\::/    \\:::\\  /:::/    /	                  .:....:::::....::-:::::...                      \n"
# define START_TEXT_13 " \\:::\\    \\      \\/____/  \\/____/ \\:::\\/:::/    /  \\:::\\   \\:::\\   \\/____/  \\/____/ \\:::\\/:::/    /	                .:-:...:::.::::...::-:::::...                      \n"
# define START_TEXT_14 "  \\:::\\    \\                       \\::::::/    /    \\:::\\   \\:::\\    \\               \\::::::/    /	              -====:...::.....:-:::::::::.....                     \n"
# define START_TEXT_15 "   \\:::\\    \\                       \\::::/    /      \\:::\\   \\:::\\____\\               \\::::/    /	             .++===-........:--=-..::........                     \n"
# define START_TEXT_16 "    \\:::\\    \\                      /:::/    /        \\:::\\  /:::/    /               /:::/    /	               :-+=-=-=-::---===. .:.......                       \n"
# define START_TEXT_17 "     \\:::\\    \\                    /:::/    /          \\:::\\/:::/    /               /:::/    /	                          -+=====--===-   .........                       \n"
# define START_TEXT_18 "      \\:::\\    \\                  /:::/    /            \\::::::/    /               /:::/    /	                             -+=-====-.      .......                       \n"
# define START_TEXT_19 "       \\:::\\____\\                /:::/    /              \\::::/    /               /:::/    /	                               .====-.            ..                        \n"
# define START_TEXT_20 "        \\::/    /                \\::/    /                \\::/    /                \\::/    /	                                 :-.                                        \n"
# define START_TEXT_21 "         \\/____/                  \\/____/                  \\/____/                  \\/____/ 	\n"
# define START_TEXT_22 "\n"
# define START_TEXT_23 "        							by Iyan NAZARIAN and Theo POLGAR\e[0m\n"
# define START_TEXT_24 "\n"

typedef struct s_env_pair
{
	char	key[4096];
	char	*value;
}			t_env_pair;

typedef struct s_data
{
	char	**env;
	t_ast	*ast;
}				t_data;

/* BUILD IN */
int		builtin_pwd();
int		builtin_echo(char **arg);
int		builtin_cd(char *path);

/* PRINT */
void	print_prompt(void);
void	print_start_text(void);

#endif
