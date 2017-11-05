
#include "ft_malloc.h"


void  first_malloc(t_link **tmp, size_t size, void *page)
{
  (*tmp) = page;
  (*tmp)->size = size;
  (*tmp)->isFree = MALLOCATED;
  (*tmp)->addr = page + sizeof(t_link);
  (*tmp)->next = NULL;
}

/*void add_block(t_link **tmp, size_t size, void *page, size_t nb_malloc)
{
  (*tmp)->next->next = NULL;
  (*tmp)->next->size = size;
  (*tmp)->next->isFree = MALLOCATED;
  (*tmp)->next->addr = page + sizeof(t_link) + (data.nb_malloc % 256 * 128);
}*/

void *tiny_malloc(size_t size)
{
  printf("%i\n", (int)size);
  t_link *tmp;

  if (data.nb_malloc_tny == 0)
  {
    data.tny_page = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    first_malloc(&data.tny, size, data.tny_page);
    ++data.nb_malloc_tny;
    return (data.tny->addr);
  }
  printf("fcdscsdcsd\n");
  if (data.nb_malloc_tny % 256 == 0)
  {
    data.tny_page = mmap(0, TNY_MAX, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
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
      tmp->next->size = size;
      tmp->next->isFree = MALLOCATED;
      return (tmp->next->addr);
    }
    tmp = tmp->next;
  }
  tmp->next = data.tny_page + (data.nb_malloc_tny % 256 * 128);
  tmp->next->next = NULL;
  tmp->next->size = size;
  tmp->next->isFree = MALLOCATED;
  tmp->next->addr = data.tny_page + sizeof(t_link) + (data.nb_malloc_tny % 256 * 128);
  ++data.nb_malloc_tny;
  return (tmp->next->addr);
}
