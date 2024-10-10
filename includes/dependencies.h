/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dependencies.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 15:36:36 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/10 02:01:37 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEPENDENCIES_H
# define DEPENDENCIES_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <signal.h>
# include <dirent.h>
# include <limits.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <sys/ioctl.h>
# include <termios.h>

# define START_TEXT1 "\e[0;32m          _____                    _____      "
# define START_TEXT2 "              _____                    _____ 		\n"
# define START_TEXT3 "         /\\    \\                  /\\    \\         "
# define START_TEXT4 "         /\\    \\                  /\\    \\	         "
# define START_TEXT5 "                               ..                \n"
# define START_TEXT6 "        /::\\    \\                /::\\    \\       "
# define START_TEXT7 "         /::\\    \\                /::\\____\\	      "
# define START_TEXT8 "                              .:::::::. 				\n"
# define START_TEXT9 "       /::::\\    \\              /::::\\    \\       "
# define START_TEXT10 "       /::::\\    \\              /:::/    /	          "
# define START_TEXT11 "              .....     .:...:....:-.  				\n"
# define START_TEXT12 "      /::::::\\    \\            /::::::\\    \\      "
# define START_TEXT13 "      /::::::\\    \\            /:::/    /	          "
# define START_TEXT14 "           .........  .:....:-:....===:              \n"
# define START_TEXT15 "     /:::/\\:::\\    \\          /:::/\\:::\\    \\   "
# define START_TEXT16 "       /:::/\\:::\\    \\          /:::/    /	      "
# define START_TEXT17 "              .......:::.:-:...........:==--.        \n"
# define START_TEXT18 "    /:::/  \\:::\\    \\        /:::/__\\:::\\    \\  "
# define START_TEXT19 "      /:::/__\\:::\\    \\        /:::/____/	          "
# define START_TEXT20 "           ......:::...::---:.....---===.            \n"
# define START_TEXT21 "   /:::/    \\:::\\    \\      /::::\\   \\:::\\    \\"
# define START_TEXT22 "       \\:::\\   \\:::\\    \\      /::::\\    \\	  "
# define START_TEXT23 "                    ....::::.:-:.::--:..---=====.\n"
# define START_TEXT24 "  /:::/    / \\:::\\    \\    /::::::\\   \\:::\\    \\"
# define START_TEXT25 "    ___\\:::\\   \\:::\\    \\    /::::::\\    \\   ___"
# define START_TEXT26 "__                        ..  ...=$-=$-.:::--==-:. \n /"
# define START_TEXT27 ":::/    /   \\:::\\    \\  /:::/\\:::\\   \\:::\\    \\"
# define START_TEXT28 "  /\\   \\:::\\   \\:::\\    \\  /:::/\\:::\\    \\ /\\"
# define START_TEXT29 "    \\	                     .:..$=$=$=...::-:.\n"
# define START_TEXT30 "/:::/____/     \\:::\\____\\/:::/  \\:::\\   \\:::\\____"
# define START_TEXT31 "\\/::\\   \\:::\\   \\:::\\____\\/:::/  \\:::\\    /::\\"
# define START_TEXT32 "____\\	                    .::::::.-$-...::.       \n"
# define START_TEXT33 "\\:::\\    \\      \\::/    /\\::/    \\:::\\  /:::/    "
# define START_TEXT34 "/\\:::\\   \\:::\\   \\::/    /\\::/    \\:::\\  /:::/  "
# define START_TEXT35 "  /	                  .:....:::::....::-:::::...   \n"
# define START_TEXT36 " \\:::\\    \\      \\/____/  \\/____/ \\:::\\/:::/    /"
# define START_TEXT37 "  \\:::\\   \\:::\\   \\/____/  \\/____/ \\:::\\/:::/   "
# define START_TEXT38 " /	                .:-:...:::.::::...::-:::::...   \n"
# define START_TEXT39 "  \\:::\\    \\                       \\::::::/    /    "
# define START_TEXT40 "\\:::\\   \\:::\\    \\               \\::::::/    /	 "
# define START_TEXT41 "             -====:...::.....:-:::::::::.....         \n"
# define START_TEXT42 "   \\:::\\    \\                       \\::::/    /     "
# define START_TEXT43 " \\:::\\   \\:::\\____\\               \\::::/    /	 "
# define START_TEXT44 "            .++===-........:--=-..::........          \n"
# define START_TEXT45 "    \\:::\\    \\                      /:::/    /       "
# define START_TEXT46 " \\:::\\  /:::/    /               /:::/    /	       "
# define START_TEXT47 "        :-+=-=-=-::---===. .:.......                \n"
# define START_TEXT48 "     \\:::\\    \\                    /:::/    /        "
# define START_TEXT49 "  \\:::\\/:::/    /               /:::/    /	         "
# define START_TEXT50 "                 -+=====--===-   .........            \n"
# define START_TEXT51 "      \\:::\\    \\                  /:::/    /         "
# define START_TEXT52 "   \\::::::/    /               /:::/    /	           "
# define START_TEXT53 "                  -+=-====-.      .......             \n"
# define START_TEXT54 "       \\:::\\____\\                /:::/    /          "
# define START_TEXT55 "    \\::::/    /               /:::/    /	           "
# define START_TEXT56 "                    .====-.            ..             \n"
# define START_TEXT57 "        \\::/    /                \\::/    /            "
# define START_TEXT58 "    \\::/    /                \\::/    /	             "
# define START_TEXT59 "                    :-.                               \n"
# define START_TEXT60 "         \\/____/                  \\/____/             "
# define START_TEXT61 "     \\/____/                  \\/____/ 	\n"
# define START_TEXT62 "\n"
# define START_TEXT63 "        							by Iyan NAZARIAN and "
# define START_TEXT64 "Theo POLGAR\e[0m\n"
# define START_TEXT65 "\n"

#endif
