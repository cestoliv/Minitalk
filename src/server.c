/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:18:01 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/19 12:00:14 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	bit_control = 3;

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
			ft_printf(" wait%d ", bit_control);
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

void	sig_usr(int sig, siginfo_t *info, void *context)
{
	static char	c = 0;
	static int	bit = -1;

	if (bit_control == 3)
	{
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
		kill(info->si_pid, sig);
		if (!bit && c)
			ft_putchar_fd(c, 1);
		else if (!bit && !c)
		{
			ft_printf("FIN");
			sleep(5);
			bit_control = 2;
			send_str("Message received !", info->si_pid);
		}
		bit--;
	}
	else
	{
		if (sig == SIGUSR1)
			bit_control = 1;
		else if (sig == SIGUSR2)
			bit_control = 0;
	}
	ft_printf(" sig%d ", bit_control);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("pid: %d", pid);
	init_sig(SIGUSR1, &sig_usr);
	init_sig(SIGUSR2, &sig_usr);
	while (1)
		pause();
}
