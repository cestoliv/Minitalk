/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:31:50 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/19 11:30:16 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H
# include <sys/types.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include "../libft/libft.h"
/*
void	send_char(char c, pid_t pid);
void	send_str(char *str, pid_t pid);
void	control_bit(int sig, siginfo_t *info, void *context);
*/
void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *));
#endif
