/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhuylebr <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/28 12:59:14 by vhuylebr          #+#    #+#             */
/*   Updated: 2017/10/28 12:59:16 by vhuylebr         ###   ########.fr       */
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

#define MALLOQUED 1
typedef struct s_link
{
  struct s_link *next;
  size_t size;
  void *addr;
  char isFree;
} t_link;

typedef struct s_data
{
  t_link *tny;
  size_t nb_malloc_tny;
  t_link *small;
  size_t nb_small;
  t_link *large;
  void *page_tny;
  void *small_page;
} t_data;

t_data data;
#endif /* FT_MALLOC_H */

/*    int i = 0;
while (1) 
            {
                printf("i %i %c\n", i, ((char*)addr)[i]);
                ++i;
            }*/