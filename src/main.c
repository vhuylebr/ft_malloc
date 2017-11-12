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

void  *first_block(t_type *test)
{
  all.tny.size_block = 128;
  all.tny.size_page = (8 * 4096);
  all.small.size_block = (512);
  all.small.size_page = (32 * 4096);
  all.small.size = 2;
  all.tny.size = 1;
  //all.tny.free_list = NULL;
  
  //all.small.free_list = NULL;
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

void ft_free(void *ptr)
{
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
    /*while (tmp != NULL)
    {
      printf("ptr %s %s\n", (char*)tmp->addr, (char*)ptr);
      tmp = tmp->next;
    }
    printf("ccc");*/
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
  ptr = 0;
}

void *ft_malloc(size_t size)
{
  t_link *tmp;

  all.size = size;
  if (size < 128 - sizeof(t_link))
  {
    return (test_malloc(&all.tny));  
  }
  if (size < 512 - sizeof(t_link))
  {
    return (test_malloc(&all.small));
  }
  else
  {
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

int main()
{
  char **result;
  int i = 0;
  //t_link *tmp;

  result = (char**)ft_malloc(sizeof(char**) * 10000);
  /*result[12] = 'a';  
  result = ft_malloc(13);
  result[6] = 'a';
  ft_free(result);*/
  //while (1)
  //{
  i = 0;
  while (i < 3000)
  {
    result[i] = ft_malloc(12);
    if (i == 0)
      result[i][0] = 'a';
    if (i == 1)
      result[i][0] = 'b';
    if (i == 2)
      result[i][0] = 'c';
      //result = ft_malloc(12);
      //result[11] = 'a';  
      //ft_free(result);
      i++;
    }
    --i;
    //printf("free %s\n", result[0]);
    while (i >= 0)
    {
      //result[i] = ft_malloc(12);
      //result[119] = 'a';  
      //result = ft_malloc(12);
      //if (i == 1 || i == 2 || i == 0)
        //printf("1 2 3 %s\n", result[i]);
    ft_free(result[i]);
    --i;
  }
  i  = 0;
  while (i < 230)
  {
    result[i] = ft_malloc(12);
    if (i == 0)
      result[i][0] = 'e';
    if (i == 1)
      result[i][0] = 'f';
    if (i == 2)
      result[i][0] = 'g';
      //result = ft_malloc(12);
      //result[11] = 'a';  
      //ft_free(result);
      i++;
    }
    --i;
   // printf("free\n");
    while (i >= 0)
    {
      //result[i] = ft_malloc(12);
      //result[119] = 'a';  
      //result = ft_malloc(12);
      //printf("%s\n", result[i]);
    ft_free(result[i]);
    --i;
  }
//}
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
