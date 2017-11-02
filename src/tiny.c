#include "ft_malloc.h"

void  *tiny_malloc(size_t size)
{
  printf("%i\n", (int)size);
  t_link *tmp;
  
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
      printf("free tiny\n");
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