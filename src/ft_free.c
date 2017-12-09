#include "ft_malloc.h"

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
    while (tmp != NULL)
    {
      printf("ptr %s %s\n", (char*)tmp->addr, (char*)ptr);
      tmp = tmp->next;
    }
    printf("ccc");
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
