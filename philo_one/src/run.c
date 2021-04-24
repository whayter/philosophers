/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:52:14 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/24 10:55:29 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void start_simulation()
{
    int i;

    g_env.run = 1;
    get_actual_time(&g_env.t_start);
    i = 0;
    while (i < g_env.n_phi)
    {
        g_env.phi[i].t_last = g_env.t_start;
        pthread_create(&g_env.phi[i].thread, NULL, routine, &g_env.phi[i]);
        i += 2;
    }
    usleep(1000);
    i = 1;
    while (i < g_env.n_phi)
    {
        pthread_create(&g_env.phi[i].thread, NULL, routine, &g_env.phi[i]);
        i += 2;
    }
}

void evaluate_simulation()
{
    int i;
    
    while (g_env.run)
    {
        philosopher_die();
        if (g_env.rounds >= 0)
        {
            i = -1;
            while (++i < g_env.n_phi)
            {
                if (g_env.phi[i].rounds == g_env.rounds)
                    g_env.run = 0;
            }
        }
    }
}

void end_simulation()
{
    int i;

    i = -1;
    while (++i < g_env.n_phi)
        pthread_join(g_env.phi[i].thread, NULL);
    i = -1;
    printf("\n\n");
    while (++i < g_env.n_phi)
        printf("%d has eaten %d times\n", g_env.phi[i].id, g_env.phi[i].rounds);
}