#include "ft_malloc.h"

void *small_malloc(size_t size)
{
  t_link *tmp;  

  if (data.nb_malloc_small == 0)
  {
    data.small_page = mmap(0, SMALL_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    data.small = data.small_page + (data.nb_malloc_small * 512);
    data.small->size = size;
    data.small->isFree = MALLOCATED;
    data.small->addr = data.small_page + sizeof(t_link) + (data.nb_malloc_small * 512);
    ++data.nb_malloc_small;
    data.small->next = NULL;
    printf("%i\n", (int)size);
    return (data.small->addr);
  }
  if (data.nb_malloc_small % 256 == 0)
  {
    data.small_page = mmap(0, SMALL_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
  }
  tmp = data.small;
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
      printf("free small\n");
      break;
    }
    tmp = tmp->next;
  }
  if (tmp->next == NULL)
  {
    tmp->next = data.small_page + (data.nb_malloc_small % 256 * 512);
    tmp->next->next = NULL;
    tmp->next->size = size;
    tmp->next->isFree = MALLOCATED;
    tmp->next->addr = data.small_page + sizeof(t_link) + (data.nb_malloc_small % 256 * 512);
    ++data.nb_malloc_small;
    return (tmp->next->addr);
  }
  else
  {
    tmp->next->size = size;
    tmp->next->isFree = MALLOCATED;
    return (tmp->next->addr);
  }
}