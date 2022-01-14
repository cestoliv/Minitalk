/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:24:25 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/14 10:26:00 by ocartier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include "libft/libft.h"

void	send_char(char c, pid_t pid)
{
	int	bit;

	bit = 8 * sizeof(c) - 1;
	while (bit >= 0)
	{
		if (c & (1 << bit))
		{
			kill(pid, SIGUSR1);
			printf("1");
		}
		else
		{
			kill(pid, SIGUSR2);
			printf("0");
		}
		bit--;
		usleep(650);
	}
/*
	for(int bit=0;bit<(sizeof(char) * 8); bit++)
	{
		printf("%i ", c & 0x01);
		c = c >> 1;
	}
	*/
	/*
	int bit = sizeof(char) * __CHAR_BIT__;
	while (bit)
	{
		printf("iter\n");
		bit--;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else if (c)
			kill(pid, SIGUSR2);
	}
	*/
}

int	main(int argc, char **argv)
{
	int	cur;

	cur = 0;
	while (argv[2][cur])
	{
		send_char(argv[2][cur], atoi(argv[1]));
		cur++;
	}
	send_char(0, atoi(argv[1]));
}
