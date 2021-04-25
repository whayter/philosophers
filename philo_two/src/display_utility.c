/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:44:05 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/25 16:40:47 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	display_status(int id, int ms, int status)
{
	char const *list[5] = {
		"died",
		"has taken a fork",
		"is eating",
		"is sleeping",
		"is thinking"};

	if (g_env.run)
	{
		sem_wait(g_env.syslock);
		printf("%*d%*s %d %s\n", 8, ms, 4, "", id, list[status]);
		sem_post(g_env.syslock);
	}
}

int		display_error(char *msg)
{
	printf("Error: %s\n", msg);
	return (0);
}
