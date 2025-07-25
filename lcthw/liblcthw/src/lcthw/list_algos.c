#include "list_algos.h"


int List_bubble_sort(List *list, List_compare compfn){
    if(list->first == NULL){
        return 0;
    }
    ListNode *curr, *next=NULL, *last_sorted, *last_node;
    for(curr=list->first; curr!=NULL; curr=curr->next){
        last_node = curr;
    }

    last_sorted = last_node;
    while(last_sorted != list->first){
        for(curr=list->first; curr!=last_sorted; curr=curr->next){
            if(curr->next){
                next = curr->next;
                if(compfn(curr->value, next->value) > 0 ){
                    void *tmp = curr->value;
                    curr->value = next->value;
                    next->value = tmp;
                }
            }
            last_node = curr;
        }
        last_sorted = last_node;
    }
    return 0;


}

ListNode* ListMid(List *list){
    if(list == NULL){
        return NULL;
    }
    if(list->first == NULL){
        return list->first;
    }
    ListNode *fast = NULL, *slow = NULL;
    fast = list->first;
    slow = list->first;
    int i = 0;
    while(fast != NULL){
        fast = fast->next;
        i++;
        if(i%2 == 0){
            slow = slow->next;
        }
    }
    return slow;
}

// split list to two part.
static List *List_split(List *list){
    ListNode *mid = ListMid(list);
    ListNode *next = NULL;
    if(mid == NULL){
        return List_create();
    }
    List *right = List_create();
    while(mid != NULL){
        next = mid->next;
        List_push(right, mid->value);
        List_remove(list, mid);
        mid = next;
    }

    return right;

}

static List *List_merge(List *list1, List *list2, List_compare compfn){
    List *res = List_create();
    
    ListNode *node1=list1->first, *node2=list2->first;

    while(1){
        if(node1 && node2){
            if(compfn(node1->value, node2->value) < 0){
                List_push(res, node1->value);
                node1 = node1->next;
            }else{
                List_push(res, node2->value);
                node2 = node2->next;
            }
        }else if(node1){
            List_push(res, node1->value);
            node1 = node1->next;           
        }else if(node2){
            List_push(res, node2->value);
            node2 = node2->next;             
        }else{
            break;
        }
    }
    return res;
}

List *List_merge_sort(List *list,  List_compare compfn){
    if(list == NULL){
        return List_create();
    }
    if(list->first == NULL){
        return List_create();
    }
    if(list->first->next == NULL){
        List *res = List_create();
        List_push(res, list->first->value);
        return res;
    }
    List *left, *right;
    right = List_split(list);
    left = list;
    List *sorted_left = List_merge_sort(left, compfn);
    List *sorted_right = List_merge_sort(right, compfn);

    return List_merge(sorted_left, sorted_right, compfn);
}