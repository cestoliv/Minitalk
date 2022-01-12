/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:18:01 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/12 12:59:51 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"



void sig_usr(int sig)
{
	static int	bit = 0;
	static char	c;
	int			cur_c;

	if (sig == SIGUSR1)
		cur_c = 0;
	else if (sig == SIGUSR2)
		cur_c = 1;

	c &= (~(1 << (bit)));

	//c |= cur_c << bit;

	ft_printf("%d", cur_c);
	/*
	if (bit == 3)
		ft_printf("%c ", c);
		*/
	//bit++;
}

int	main(void)
{
	pid_t pid = getpid();
	ft_printf("pid: %d\n", pid);

	struct sigaction susr1;
	susr1.sa_handler = sig_usr;
	susr1.sa_flags = SA_RESTART;
	sigemptyset(&susr1.sa_mask);
	sigaction(SIGUSR1, &susr1, 0);

	struct sigaction susr2;
	susr2.sa_handler = sig_usr;
	susr2.sa_flags = SA_RESTART;
	sigemptyset(&susr2.sa_mask);
	sigaction(SIGUSR2, &susr2, 0);

	//signal(SIGUSR1, sig_usr1);
	//signal(SIGUSR2, sig_usr2);

	while (1) {}
}
