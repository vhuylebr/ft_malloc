/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:59:25 by vhuylebr          #+#    #+#             */
/*   Updated: 2017/10/28 12:59:29 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"

#include <stdlib.h>

void    *ft_malloc(size_t size)
{
    static size_t   nb_malloc_tny;

    if (size <= 96)
    {
        ++nb_malloc_tny;
        if (nb_malloc_tny == 1 || nb_malloc_tny % 256 == 0)
        {
            data.tny = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        }
    }
    return(0);
}

int main() 
{
    char    *result;

    result = ft_malloc(12);
    return (0);
}
