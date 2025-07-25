#include "list.h"

typedef int (*List_compare)(void *, void *);

int List_bubble_sort(List *list, List_compare compfn);

List *List_merge_sort(List *list,  List_compare compfn);