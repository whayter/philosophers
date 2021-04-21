/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 10:52:14 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/21 12:15:55 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void start_simulation()
{
    int i;

    g_env.run = 1;
    i = 0;
    while (i < g_env.n_phi)
    {
        get_actual_time(&g_env.phi[i].t_start);
        pthread_create(&g_env.phi[i].thread, NULL, routine, &g_env.phi[i]);
        i += 2;
    }
    usleep(1000);
    i = 1;
    while (i < g_env.n_phi)
    {
        get_actual_time(&g_env.phi[i].t_start);
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