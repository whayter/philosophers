/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utility.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:44:05 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/22 15:02:58 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void display_status(int id, int ms, int status)
{
    char const *list[5] = {
        "died",
        "has taken a fork",
        "is eating",
        "is sleeping",
        "is thinking"};
    
    pthread_mutex_lock(&g_env.phi[id - 1].lock);
    if (g_env.run)
        printf("%*d%*s %d %s\n", 8, ms, 4, "", id, list[status]);
    pthread_mutex_unlock(&g_env.phi[id - 1].lock);
}

int display_error(char *msg)
{
    printf("Error: %s\n", msg);
    return (0);
}