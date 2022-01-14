/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:18:01 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/14 11:17:24 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"

void	sig_usr(int sig)
{
	static char	c = 0;
	static int	bit = -1;
	int			char_size;

	char_size = 8 * sizeof(c) - 1;
	if (bit < 0)
	{
		bit = char_size;
		if (!c)
			ft_putstr_fd("  - ST\n", 1);
		c = 127;
	}
	if (sig == SIGUSR1)
		c |= 1 << bit;
	else if (sig == SIGUSR2)
		c &= ~(1 << bit);
	if (!bit && c)
		ft_putchar_fd(c, 1);
	else if (!bit && !c)
		ft_putstr_fd("\n  - ET\n", 1);
	bit--;
}

void	init_sig(int sig)
{
	struct sigaction susr;
	
	susr.sa_handler = sig_usr;
	susr.sa_flags = SA_RESTART;
	sigemptyset(&susr.sa_mask);
	if (sig == SIGUSR1)
		sigaction(SIGUSR1, &susr, 0);
	else if (sig == SIGUSR2)
		sigaction(SIGUSR2, &susr, 0);
}

int	main(void)
{
	pid_t pid = getpid();
	ft_printf("pid: %d\n", pid);
	init_sig(SIGUSR1);
	init_sig(SIGUSR2);
	while (1) {}
}
