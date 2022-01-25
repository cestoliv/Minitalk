/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ocartier <ocartier@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 09:24:25 by ocartier          #+#    #+#             */
/*   Updated: 2022/01/25 10:49:16 by ocartier         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	send_char(char p_c, pid_t p_pid)
{
	static int		bit = -1;
	static char		c;
	static pid_t	pid;

	if (p_pid)
	{
		c = p_c;
		pid = p_pid;
	}
	if (bit < 0)
		bit = __CHAR_BIT__ * sizeof(c) - 1;
	if (kill(pid, 0) < 0)
	{
		ft_printf("ERROR : cant send sig to pid : %d\n", pid);
		exit(EXIT_FAILURE);
	}
	if (c & (1 << bit))
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	bit--;
	return (bit);
}

void	send_str(char *p_str, pid_t p_pid)
{
	static int		cur = 0;
	static char		*str;
	static pid_t	pid;
	static int		bit = -1;

	if (p_pid)
	{
		str = p_str;
		pid = p_pid;
	}
	if (bit < 0)
	{
		if (str[cur])
		{
			bit = send_char(str[cur], pid);
			cur++;
		}
		else
			bit = send_char(0, pid);
	}
	else
	{
		bit = send_char(0, 0);
	}
}

void	sig_usr(int sig)
{
	if (sig == SIGUSR1)
		send_str("", 0);
	else if (sig == SIGUSR2)
		exit(EXIT_SUCCESS);
}

int	main(int argc, char **argv)
{
	pid_t	pid;

	if (argc != 3)
	{
		ft_printf("Usage : ./client <pid> <string to send>\n");
		exit(EXIT_FAILURE);
	}
	signal(SIGUSR1, &sig_usr);
	signal(SIGUSR2, &sig_usr);
	pid = ft_atoi(argv[1]);
	if (!pid)
	{
		ft_printf("%s is an invalid pid\n", argv[1]);
		exit(EXIT_FAILURE);
	}
	send_str(argv[2], pid);
	while (1)
		sleep(1);
}
