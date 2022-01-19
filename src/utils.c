/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 10:26:41 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/19 11:31:23 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"
/*
int	bit_control = 2;

void	send_char(char c, pid_t pid)
{
	int	bit;

	bit = __CHAR_BIT__ * sizeof(c) - 1;
	while (bit >= 0)
	{
		bit_control = 2;
		if (c & (1 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		bit--;
		usleep(100);
		while (bit_control == 2)
		{
			sleep(1);
			ft_printf(" wait = %d ", pid);
		}
	}
}

void	send_str(char *str, pid_t pid)
{
	int	cur;

	cur = 0;
	while (str[cur])
	{
		send_char(str[cur], pid);
		cur++;
	}
	send_char(0, pid);
}

void	control_bit(int sig, siginfo_t *info, void *context)
{
	if (sig == SIGUSR1)
		bit_control = 1;
	else if (sig == SIGUSR2)
		bit_control = 0;
	ft_printf(" contrl = %d ", info->si_pid);
}
*/
void	init_sig(int sig, void (*handler)(int, siginfo_t *, void *))
{
	struct sigaction	susr;

	susr.sa_sigaction = handler;
	susr.sa_flags = SA_SIGINFO;
	//sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}
