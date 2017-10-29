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

void *ft_malloc(size_t size)
{
  t_link *tmp;

  if (size < 128 - sizeof(t_link))
  {
    if (data.nb_malloc_tny == 0)
    {
      data.page_tny = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
      data.tny = data.page_tny + (data.nb_malloc_tny * 128);
      data.tny->size = size;
      data.tny->isFree = MALLOCATED;
      data.tny->addr = data.page_tny + sizeof(t_link) + (data.nb_malloc_tny * 128);
      ++data.nb_malloc_tny;
      data.tny->next = NULL;
      return (data.tny->addr);
    }
    if (data.nb_malloc_tny % 256 == 0)
    {
      data.page_tny = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    }
    tmp = data.tny;
    if (tmp->isFree == 0)
    {
      tmp->isFree = MALLOCATED;
      tmp->size = size;
      return (tmp->addr);
    }
    while (tmp->next != NULL)
    {
      if (tmp->next->isFree == 0)
      {
        printf("free\n");
        break;
      }
      tmp = tmp->next;
    }
    if (tmp->next == NULL)
    {
      tmp->next = data.page_tny + (data.nb_malloc_tny % 256 * 128);
      tmp->next->next = NULL;
      tmp->next->size = size;
      tmp->next->isFree = MALLOCATED;
      tmp->next->addr = data.page_tny + sizeof(t_link) + (data.nb_malloc_tny % 256 * 128);
      ++data.nb_malloc_tny;
      return (tmp->next->addr);
    }
    else
    {
      tmp->next->size = size;
      tmp->next->isFree = MALLOCATED;
      return (tmp->next->addr);
    }
  }
  return (0);
}

void ft_free(void *ptr)
{
  if (((char *)ptr)[-8] == 1)
  {
    ((char *)ptr)[-8] = 0;    
  }
  ptr = 0;
}

int main()
{
  char *result;
  int i = 0;
  t_link *tmp;

  //printf("%i\n", (int)data.tny->size);
  result = ft_malloc(12);
  result = ft_malloc(12);
  ft_free(result);
  while (i < 1200)
  {
    result = ft_malloc(12);
    ft_free(result);
    i++;
  }
  i = 0;
  tmp = data.tny;
  while (tmp != NULL)
  {
    ++i;
    printf("nombre mallocated %i\n", i);
    tmp = tmp->next;
  }
  /*while (i < 128 * 11)
  {
    printf("%i %i\n", i, result[i]);
    ++i;
  }
  i = 0;*/
  return (0);
}
