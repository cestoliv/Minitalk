/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:18:01 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/18 10:44:00 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	sig_usr(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = -1;

	if (bit < 0)
	{
		bit = __CHAR_BIT__ * sizeof(c) - 1;
		if (!c)
			ft_printf("\nClient say : ");
	}
	if (sig == SIGUSR1)
		c |= 1 << bit;
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c)
		ft_putchar_fd(c, 1);
	else if (!bit && !c)
		send_str("Message received !", info->si_pid);
	bit--;
}

void	init_sig(int sig)
{
	struct sigaction	susr;

	susr.sa_sigaction = sig_usr;
	susr.sa_flags = SA_SIGINFO;
	//sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("pid: %d", pid);
	init_sig(SIGUSR1);
	init_sig(SIGUSR2);
	while (1)
		pause();
}
