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

/*int main()
{
  char *result;
  int i = 0;
  t_link *tmp;

  result = ft_malloc(120);
  result[120] = 'a';  
  result = ft_malloc(12);
  result[6] = 'a';
  ft_free(result);
  printf("fufiu\n");
  while (i < 1200)
  {
    result = ft_malloc(120);
    ft_free(result);
    i++;
  }
  i = 0;
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
  i = 0;
  return (0);
}*/
