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
static  t_data_test all;

void *test_malloc(t_type *test)
{
  t_link *tmp;

  if ((*test).nb_malloc == 0)
  {
    (*test).page = mmap(0, SMALL_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    (*test).list = (*test).page + ((*test).nb_malloc * 512);
    (*test).list->size = all.size;
    (*test).list->isFree = MALLOCATED;
    (*test).list->addr = (*test).page + sizeof(t_link) + ((*test).nb_malloc * 512);
    ++(*test).nb_malloc;
    (*test).list->next = NULL;
    return ((*test).list->addr);
  }
  if ((*test).nb_malloc % 256 == 0)
  {
    (*test).page = mmap(0, SMALL_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  }
  tmp = (*test).list;
  if (tmp->isFree == 0)
  {
    tmp->isFree = MALLOCATED;
    tmp->size = all.size;
    return (tmp->addr);
  }
  while (tmp->next != NULL)
  {
    printf("%i\n", ((int)(*test).nb_malloc));
    if (tmp->next->isFree == 0)
    {
      tmp->next->size = all.size;
      tmp->next->isFree = MALLOCATED;
      return (tmp->next->addr);
    }
    tmp = tmp->next;
  }
  tmp->next = (*test).page + ((*test).nb_malloc % 256 * 512);
  tmp->next->next = NULL;
  tmp->next->size = all.size;
  tmp->next->isFree = MALLOCATED;
  tmp->next->addr = (*test).page + sizeof(t_link) + ((*test).nb_malloc % 256 * 512);
  ++(*test).nb_malloc;
  return (tmp->next->addr);
}

void *ft_malloc(size_t size)
{
  t_link *tmp;

  all.size = size;
  return (test_malloc(&all.tny));
  if (size < 128 - sizeof(t_link))
  {
    printf("tiny\n");
    return (tiny_malloc(size));
  }
  if (size < 512 - sizeof(t_link))
  {
    printf("small n=%i\n", (int)data.nb_malloc_small);
    return (small_malloc(size));
  }
  else
  {
    printf("large %i\n", (int)size);
    if (data.nb_malloc_large == 0)
    {
      data.large = mmap(0, size + sizeof(t_link), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
      data.large->size = size;
      data.large->addr = data.large + sizeof(t_link);
      data.large->next = NULL;
      return (data.large->addr);
    }
    tmp = data.small;
    while (tmp->next != NULL)
    {
      tmp = tmp->next;
    }
    tmp->next = mmap(0, size + sizeof(t_link), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    tmp->next->next = NULL;
    tmp->next->size = size;
    tmp->next->addr = tmp->next + sizeof(t_link);
    return (tmp->next->addr);
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
  //t_link *tmp;

  result = (char*)ft_malloc(12);
  result[12] = 'a';  
  result = ft_malloc(12);
  result[6] = 'a';
  ft_free(result);
  printf("fufiu\n");
  while (i < 12)
  {
    result = ft_malloc(12);
    //ft_free(result);
    i++;
  }
/*  i = 0;
  tmp = data.small;
  while (tmp != NULL)
  {
    ++i;
    printf("nombre mallocated %i\n", i);
    tmp = tmp->next;
  }
  while (i < 128 * 11)
  {
    printf("%i %i\n", i, result[i]);
    ++i;
  }
  i = 0;*/
  return (0);
}
