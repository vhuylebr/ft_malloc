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
    t_link            *tmp;

    if (size < 96)
    {
        if (nb_malloc_tny == 0 || nb_malloc_tny % 256 == 0)
        {
            data.page_tny = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
        }
        tmp = data.tny;
        while (tmp != 0)
        {
            tmp = tmp->next;
        }
        tmp = data.page_tny + (nb_malloc_tny * 128);
        tmp->size = size;
        tmp->addr = data.page_tny + sizeof(t_link) + (nb_malloc_tny * 128);
        tmp->isFree = MALLOQUED;
        
        ++nb_malloc_tny;
        return (data.tny->addr);
    }
    return(0);
}

int main() 
{
    char    *result;
    // int i = 0;

    result = ft_malloc(12);
    /*while (i < 12)
    {
        printf("%p\n%i\n", &result[i], ((int*)data.tny)[i]);
        ++i;
    }
    i = 0;
    result = ft_malloc(12);
    while (i < 12)
    {
        printf("%p\n%i\n", &result[i], ((int*)data.tny)[i]);
        ++i;
    }
    return (0);*/
}
