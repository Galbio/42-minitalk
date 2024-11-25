/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gakarbou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:04:05 by gakarbou          #+#    #+#             */
/*   Updated: 2024/11/26 00:34:50 by gakarbou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

/*
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	send_addr(int pid, char *str, int len)
{
	char	*malloced;
	size_t	addr;

	malloced = malloc(sizeof(char) * (len + 2));
	if (!malloced)
		return ;
	malloced[len] = 0;
	malloced[len + 1] = '*';
	while (--len >= 0)
		malloced[len] = str[len];
	addr = (size_t)malloced;
	printf("addr = %p\n", malloced);
	while (++len < 64)
	{
		if (addr & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		addr = addr >> 1;
		usleep(500);
	}
}
*/

int	ft_atoi(char *str)
{
	int	sign;
	int	nb;

	nb = 0;
	sign = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*(str++) == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9')
		nb = nb * 10 + (*(str++) - '0');
	return (nb * sign);
}

void	send_character(int pid, char c)
{
	int	i;

	i = -1;
	while (++i < 8)
	{
		if (c & 1)
			kill(pid, SIGUSR2);
		else
			kill(pid, SIGUSR1);
		c = c >> 1;
		usleep(400);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	pid;

	if (argc != 3)
		exit(1);
	i = -1;
	pid = ft_atoi(argv[1]);
	while (argv[2][++i])
		send_character(pid, argv[2][i]);
	send_character(pid, argv[2][i]);
}
