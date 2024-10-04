/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ptheo <ptheo@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:09:45 by inazaria          #+#    #+#             */
/*   Updated: 2024/10/04 21:17:43 by ptheo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_MANAGER_H
# define ERROR_MANAGER_H

# define STRINGIFY(x) #x
# define TOSTRING(x) STRINGIFY(x)

// Debug Helping
# define DBG(reason) reason " at line " \
TOSTRING(__LINE__) " in file " __FILE__ "\n"

// Freeing functions


// Error Handling


// Debugging
void		debug(char *str);

#endif
