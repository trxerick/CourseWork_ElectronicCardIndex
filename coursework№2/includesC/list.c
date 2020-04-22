#include "../includesH/list.h"

carHead *init_head(carHead *head)
{
    if((head = malloc(sizeof(carHead))) != NULL){
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
    }

    return head;
}

void add_first(carHead *head , carNode *node)
{
    if(head&&node){
        head->first = node;
        head->last = node;
        head->count++;
    }
}

void print_list(carHead *head)
{
    CLS;
    carNode *tmp;
    if(head){
        tmp = head->first;
        while(tmp != NULL){
            printf("%s\n", tmp->data->name);
            tmp = tmp->next;
        }
    }
    puts("\nPress any key to come back to main menu");
    getchar();
    getchar();
}

void clear_list(carHead *head)
{
    carNode *tmp, *tmp1;
    if(head){
        tmp = head->first;
        while(tmp != NULL){
            tmp1 = tmp->next;
            free(tmp->data->name);
            free(tmp->data->company);
            free(tmp->data);
            free(tmp);
            tmp = tmp1;
        }
        free(head);
        head = NULL;
    }
}