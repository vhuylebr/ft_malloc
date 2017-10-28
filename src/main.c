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

//#include <stdlib.h>

void *ft_malloc(size_t size)
{
  t_link *tmp;

  if (size < 128 - sizeof(t_link))
  {
    if (data.nb_malloc_tny == 0)
    {
      printf("testt");
      data.page_tny = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
      data.tny = data.page_tny + (data.nb_malloc_tny * 128);
      data.tny->size = size;
      data.tny->isFree = MALLOQUED;
      data.tny->addr = data.page_tny + sizeof(t_link) + (data.nb_malloc_tny * 128);
      ++data.nb_malloc_tny;
      data.tny->next = NULL;
      return (data.tny->addr);
    }
    if (data.nb_malloc_tny % 256 == 0)
    {
      printf("22222");
      data.page_tny = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    }
    tmp = data.tny;
    while (tmp->next != NULL)
    {
      printf("int malloc i = %i\n", (int)tmp->next->size);
      tmp = tmp->next;
    }
    printf("coucou%i\n", (int)(data.nb_malloc_tny % 256 * 128));
    tmp->next = data.page_tny + (data.nb_malloc_tny % 256 * 128);
    tmp->next->size = size;
    tmp->next->isFree = MALLOQUED;
    tmp->next->addr = data.page_tny + sizeof(t_link) + (data.nb_malloc_tny * 128);
    ++data.nb_malloc_tny;
    tmp->next->next = NULL;
    return (tmp->addr);
  }
  return (0);
}

int main()
{
  char *result;
  //int i = -32;

  //printf("%i\n", (int)data.tny->size);
  while (1)
  {
    result = ft_malloc(12);
    result[0] = 'a';
    printf("%s\n", result);
  }
 /*while (i < 128 * 11)
  {
    printf("%i %i\n", i, result[i]);
    ++i;
  }
  i = 0;*/
  return (0);
}
