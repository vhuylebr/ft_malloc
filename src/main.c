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

//static  t_data_test all;

void  *first_block(t_type *test)
{
  all.tny.size_block = 128;
  all.tny.size_page = (8 * 4096);
  all.small.size_block = (512);
  all.small.size_page = (32 * 4096);
  all.small.size = 2;
  all.tny.size = 1;
  all.tny.free_list = NULL;
  all.small.free_list = NULL;
  printf("%i\n", ((int)(*test).size_page));
  (*test).page = mmap(0, (*test).size_page, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  (*test).list = (*test).page + ((*test).nb_malloc * (*test).size_block);
  (*test).list->size = (*test).size;
  (*test).list->isFree = MALLOCATED;
  (*test).list->addr = (*test).page + sizeof(t_link) + ((*test).nb_malloc * (*test).size_block);
  ++(*test).nb_malloc;
  (*test).list->next = NULL;
  return ((*test).list->addr);
}

void  *add_block(t_type *test)
{
  t_link  *tmp;

  tmp = (*test).list;
  if (tmp->isFree == 0)
  {
    tmp->isFree = MALLOCATED;
    tmp->size = all.size;
    return (tmp->addr);
  }
  // verifier la list free
  if ((*test).free_list)
  {
    printf("coucou\n");
    tmp = (*test).free_list;
    (*test).free_list = (*test).free_list->next;
    return (tmp->addr);
  }
  // si different de null retourner ce block en changeant le header
  // retirer de list free le premier maillon free = free->next
  /*while (tmp->next != NULL)
  {
    if (tmp->next->isFree == 0)
    {
      tmp->next->size = (*test).size;
      tmp->next->isFree = MALLOCATED;
      return (tmp->next->addr);
    }    
    tmp = tmp->next;
  }*/
  tmp->next = (*test).page + ((*test).nb_malloc % 256 * (*test).size_block);
  tmp->next->next = NULL;
  tmp->next->size =  (*test).size;
  tmp->next->isFree = MALLOCATED;
  tmp->next->addr = (*test).page + sizeof(t_link) + ((*test).nb_malloc % 256 * (*test).size_block);
  ++(*test).nb_malloc;
  return (tmp->next->addr);  
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

void *ft_malloc(size_t size)
{
  t_link *tmp;

  all.size = size;
  if (size < 128 - sizeof(t_link))
  {
    //printf("tiny\n");
    return (test_malloc(&all.tny));  
    //return (tiny_malloc(size));
  }
  if (size < 512 - sizeof(t_link))
  {
    //printf("small n=%i\n", (int)data.nb_malloc_small);
    return (test_malloc(&all.small));
//  return (small_malloc(size));
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
  t_link *tmp;
  // verif de la taille
  if (((char*)ptr)[-24] == 1)
  {
    printf("in free\n");
    if (all.tny.free_list == NULL)
    {
      all.tny.free_list = ptr - 32;
      all.tny.free_list->addr = ptr;      
      all.tny.free_list->next = NULL;
      return ;
    }
    tmp = all.tny.free_list;
    all.tny.free_list = ptr - 32;
    all.tny.free_list->addr = ptr;      
    all.tny.free_list->next = tmp;
    return ;
  }
  if (((char*)ptr)[-24] == 2)
  {
    if (all.small.free_list == NULL)
    {
      all.small.free_list = ptr - 32;
      all.small.free_list->addr = ptr;
      all.small.free_list->next = NULL;
      return ;      
    }
  }
  // add en debut de la list free small ou tny si la list est different de null
  // sinon remplir le premier maillon
  if (((char *)ptr)[-8] == 1)
  {
    ((char *)ptr)[-8] = 0;
  }
  ptr = 0;
}

int main()
{
  char **result;
  int i = 0;
  //t_link *tmp;

  result = (char**)ft_malloc(sizeof(char**) * 10);
  /*result[12] = 'a';  
  result = ft_malloc(13);
  result[6] = 'a';
  ft_free(result);*/
  while (i < 3)
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
    printf("free\n");
    while (i >= 0)
    {
      //result[i] = ft_malloc(12);
      //result[119] = 'a';  
      //result = ft_malloc(12);
      printf("%s\n", result[i]);
    ft_free(result[i]);
    --i;
  }
  i  = 0;
  while (i < 3)
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
    printf("free\n");
    while (i >= 0)
    {
      //result[i] = ft_malloc(12);
      //result[119] = 'a';  
      //result = ft_malloc(12);
      printf("%s\n", result[i]);
    ft_free(result[i]);
    --i;
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
