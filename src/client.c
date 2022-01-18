/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:24:25 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/18 10:44:01 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	sig_usr(int sig)
{
	static char	c = 0;
	static int	bit = -1;

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
	if (!bit && c)
		ft_putchar_fd(c, 1);
	else if (!bit && !c)
		exit(EXIT_SUCCESS);
	bit--;
}

void	init_sig(int sig)
{
	struct sigaction	susr;

	susr.sa_handler = sig_usr;
	susr.sa_flags = SA_SIGINFO;
	//sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}

int	main(int argc, char **argv)
{
	init_sig(SIGUSR1);
	init_sig(SIGUSR2);
	send_str(argv[2], ft_atoi(argv[1]));
	while (1)
		pause();
}
