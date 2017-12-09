/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:59:25 by vhuylebr          #+#    #+#             */
/*   Updated: 2017/11/25 16:57:33 by vhuylebr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_malloc.h"
#include <stdio.h>
#include <unistd.h>

void  *first_block(t_type *test)
{
  all.tny.size_block = 128;
  all.tny.size_page = (8 * 4096);
  all.small.size_block = (512);
  all.small.size_page = (32 * 4096);
  all.small.size = 2;
  all.tny.size = 1;
  (*test).page = mmap(0, (*test).size_page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  (*test).list = (*test).page + ((*test).nb_malloc * (*test).size_block);
  (*test).list->size = (*test).size;
  (*test).list->addr = (*test).page + sizeof(t_link) + ((*test).nb_malloc * (*test).size_block);
  ++(*test).nb_malloc;
  (*test).list->next = NULL;
  (*test).end = (*test).list;
  return ((*test).list->addr);
}

void  *add_block(t_type *test)
{
  t_link  *tmp;
  if ((*test).free_list)
  {
    tmp = (*test).free_list;
    (*test).free_list = (*test).free_list->next;
    return (tmp->addr);
  }
  tmp = (*test).end;
  tmp->next = (*test).page + ((*test).nb_malloc % 256 * (*test).size_block);
  tmp->next->next = NULL;
  tmp->next->size =  (*test).size;
  tmp->next->addr = (*test).page + sizeof(t_link) + ((*test).nb_malloc % 256 * (*test).size_block);
  (*test).end = tmp->next;
  ++(*test).nb_malloc;
  tmp = (*test).list;
  return ((*test).end->addr);  
}

void *test_malloc(t_type *test)
{
/*if ((*test).size_block == 128)
    printf("tny %zu\n", (*test).nb_malloc);
  if ((*test).size_block > 128)
    printf("small %zu\n", (*test).nb_malloc);*/
  if ((*test).nb_malloc == 0)
  {
    return (first_block(test));
  }
  if ((*test).nb_malloc % 256 == 0)
  {
    (*test).page = mmap(0, (*test).size_page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  }
  return (add_block(test));
}

void free(void *ptr)
{
  //write(1, "free\n", 5);
  if (!ptr)
	{
    return ;
  }
  t_link *tmp;
  /*  i = 1;
  while ((unsigned int)i < sizeof(t_link))
  {
    printf("in free %i %i\n", ((char*)ptr)[-i], i);
    ++i;
  }*/
  if (((char*)ptr)[-16] == 1)
  {
    if (all.tny.free_list == NULL)
    {
      all.tny.free_list = ptr - sizeof(t_link);
      all.tny.free_list->addr = ptr;      
      all.tny.free_list->next = NULL;
      return ;
    }
    //tmp = all.tny.free_list;
    tmp = ptr - sizeof(t_link);
    tmp->addr = ptr;
    tmp->next = all.tny.free_list;
    all.tny.free_list = tmp;
    return ;
  }
  if (((char*)ptr)[-16] == 2)
  {
    if (all.small.free_list == NULL)
    {
      all.small.free_list = ptr - sizeof(t_link);
      all.small.free_list->addr = ptr;
      all.small.free_list->next = NULL;
      return ;      
    }
    tmp = all.small.free_list;
    all.small.free_list = ptr - sizeof(t_link);
    all.small.free_list->addr = ptr;      
    all.small.free_list->next = tmp;
	  return ;
  }
  // add en debut de la list free small ou tny si la list est different de null
  // sinon remplir le premier maillon
  //ptr = 0;
}
void *malloc(size_t size)
{
  if (!size)
  return (0);
   t_link *tmp;
  all.size = size;
  if (size < 128 - sizeof(t_link))
  {
    write(1, "tny\n", 4);
    return (test_malloc(&all.tny));  
  }
  if (size < 512 - sizeof(t_link))
  {
    write(1, "small\n", 6);
    return (test_malloc(&all.small));
  }
  else
  {
    if (data.nb_malloc_large == 0)
    {
      data.large = mmap(0, size + sizeof(t_link), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
      data.large->size = 3;
      data.large->addr = data.large + sizeof(t_link);
      data.large->next = NULL;
      ++data.nb_malloc_large;
      printf("Large\n");
      return (data.large->addr);
    }
    tmp = data.large;
    tmp->next = mmap(0, size + sizeof(t_link), PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    tmp->next->next = NULL;
    tmp->next->size = (char)3;
    tmp->next->addr = tmp->next + sizeof(t_link);
    return (tmp->next->addr);
  }
  return (0);
}

void  *realloc(void *ptr, size_t size)
{
  if (size == 0 && ptr)
  {
    free(ptr);
  }
  if (size > 0 && !ptr)
  {
    return (malloc(size));
  }
  if (size == 0 && !ptr)
  {
    return (NULL);
  }
  free(ptr);
  write(1, "realloc\n", 8);
  printf("%zu\n", size);
  return (malloc(size));
}

void  *calloc(size_t nmemb, size_t size)
{
  write(1, "calloc\n", 7);  
  if (!nmemb || !size)
  {
    return (NULL);
  }
  return (malloc(nmemb * size));
}
