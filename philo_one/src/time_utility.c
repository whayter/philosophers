/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utility.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hwinston <hwinston@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:03:17 by hwinston          #+#    #+#             */
/*   Updated: 2021/04/24 18:08:30 by hwinston         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int     get_ms_from_tv(struct timeval tv)
{
    return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void    get_actual_time(struct timeval *tv)
{
    gettimeofday(tv, NULL);
}

int     get_time_since(struct timeval reference)
{
    struct timeval  now;
    struct timeval  res;

    get_actual_time(&now);
    res.tv_sec = now.tv_sec - reference.tv_sec;
    res.tv_usec = now.tv_usec - reference.tv_usec;
    return (get_ms_from_tv(res));
}

void    wait_for(int ms)
{
    struct  timeval now;
    int     ref;

    gettimeofday(&now, NULL);
    ref = get_ms_from_tv(now) + ms;
    while (get_ms_from_tv(now) <= ref)
    {
        usleep(10);
        gettimeofday(&now, NULL);
    }
}
