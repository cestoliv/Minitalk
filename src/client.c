/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:24:25 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/19 12:02:36 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

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
				ft_printf("Server say : ");
		}
		if (sig == SIGUSR1)
			c |= 1 << bit;
		else if (sig == SIGUSR2)
			c &= ~(1 << bit);
		kill(info->si_pid, sig);
		ft_printf(" sendback%d ", info->si_pid);
		if (!bit && c)
			ft_putchar_fd(c, 1);
		else if (!bit && !c)
			exit(EXIT_SUCCESS);
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

int	main(int argc, char **argv)
{
	ft_printf("pid: %d\n", getpid());
	init_sig(SIGUSR1, &sig_usr);
	init_sig(SIGUSR2, &sig_usr);
	send_str(argv[2], ft_atoi(argv[1]));
	bit_control = 3;
	while (1)
		pause();
}
