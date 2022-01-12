/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:24:25 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/12 12:57:40 by ocartier         ###   ########.fr       */
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
	int bit = sizeof(char) * __CHAR_BIT__;
	while (bit)
	{
		bit--;
		if ((c >> bit) & 1)
			kill(pid, SIGUSR1);
		else if (c)
			kill(pid, SIGUSR2);
	}
}

int	main(int argc, char **argv)
{
	//kill(atoi(argv[1]), SIGUSR1);
	//ft_printf(int_to_bin(2));
	send_char('a', atoi(argv[1]));
}
