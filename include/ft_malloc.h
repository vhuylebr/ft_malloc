/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:59:14 by vhuylebr          #+#    #+#             */
/*   Updated: 2017/11/05 19:43:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H

#include <stdio.h>
#include <sys/mman.h>

#define TNY 128
#define TNY_PAGE_MAX 8
#define TNY_MAX (8 * 4096)

#define SMALL 512
#define SMALL_PAGE_MAX 32
#define SMALL_MAX (32 * 4096)

#define MALLOCATED 1
typedef struct s_link
{
  struct s_link *next;
  char size;
  void *addr;
} t_link;

typedef struct s_type
{
  t_link  *list;
  void    *page;
  size_t  size_page;
  size_t  size_block;
  size_t  nb_malloc;
  char    size;
  t_link  *end;
  t_link  *free_list;
} t_type;

typedef struct s_data_test
{
  t_type  tny;
  t_type  small;
  size_t  size;
} t_data_test;

typedef struct s_data
{
  t_link *tny;
  size_t nb_malloc_tny;
  t_link *small;
  size_t nb_malloc_small;
  t_link *large;
  size_t nb_malloc_large;  
  void *small_page;
  void *tny_page;

} t_data;

/*void  *tiny_malloc(size_t size);
void  *small_malloc(size_t size);*/
void  free(void *ptr);
void *malloc(size_t size);

t_data  data;
static  t_data_test all;
int i;
/*all.tny.size_block = 128;
all.tny.size_page = (8 * 4096);
all.small.size_block = (512);
all.small.size_page = (32 * 4096);*/

#endif /* FT_MALLOC_H */

/*    int i = 0;
while (1) 
            {
                printf("i %i %c\n", i, ((char*)addr)[i]);
                ++i;
            }*/