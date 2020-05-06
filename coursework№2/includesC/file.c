#include "../includesH/declarations.h"
#include "../includesH/file.h"
#include "../includesH/list.h"

void read_file(FILE *fp , carHead *head)
{
    carNode *tmp , *cur_node;
    char **arr = NULL;
    char buf[MAXLENGTH];
    int flag = 1 , id = 1;

    if(head){
        while(((fgets(buf, MAXLENGTH , fp)) != NULL) && (flag)){
            if((arr = split(arr , buf , ";")) != NULL){
                if((tmp = arr_to_node(arr,id)) != NULL){
                   if(head->count == 0){
                       add_first(head, tmp);
                       cur_node = tmp;
                   } else {
                       fill_from_file(head,tmp,cur_node);
                       cur_node = tmp;
                   }
                   id++;
                } else flag = 0;
                clear_array(arr , 7);
            } else{
                flag = 0;
                puts("There was an error while reading data from file!");
            }
        }
        head->last = tmp;
    }
}

carNode *arr_to_node(char **arr, int id)
{
    carNode *res;

    if((res = malloc(sizeof(carNode))) != NULL){
        if((res->data = malloc(sizeof(car))) != NULL){
            res->data->name = malloc((strlen(arr[0])+1)*sizeof(char));
            res->data->company = malloc((strlen(arr[1])+1)*sizeof(char));
            if(res->data->name && res->data->company){
                strcpy(res->data->name,arr[0]);
                strcpy(res->data->company,arr[1]);
                res->data->year = atoi(arr[2]);
                res->data->price = atoi(arr[3]);
                res->data->weight = atof(arr[4]);
                res->data->mileage = atof(arr[5]);
                arr = split(arr,arr[6]," ");
                res->data->speed[0] = atoi(arr[0]);
                res->data->speed[1] = atoi(arr[1]);
                clear_array(arr , 2);
                res->id = id;
                res->next = NULL;
                res->prev = NULL;
            } else {
                free(res->data); 
                free(res);
                res = NULL;
            }
        } else {
            free(res);
            res = NULL;
        }
    }
    return res;
}

void fill_from_file(carHead *head , carNode* node , carNode *cur_node)
{
    if(head && node && cur_node){
        cur_node->next = node;
        node->prev= cur_node;
    }
    head->count++;
}

carNode *get_node()
{
    carNode *new_node = NULL;
    if((new_node = (carNode*)malloc(sizeof(carNode))) != NULL){
        if((new_node->data = (car*)malloc(sizeof(car))) != NULL){
            new_node->data->company = (char*)malloc(MAXLENGTH*sizeof(char));
            new_node->data->name = (char*)malloc(MAXLENGTH*sizeof(char));
            if(new_node->data->company && new_node->data->name){
                getchar();
                puts("Enter the name(Max length is 512 chars!):");
                fgets(new_node->data->name , MAXLENGTH , stdin);
                new_node->data->name[strlen(new_node->data->name) - 1] = '\0';
                puts("Enter the company(Max length is 512 chars!):");
                fgets(new_node->data->company , MAXLENGTH , stdin);
                new_node->data->company[strlen(new_node->data->company) - 1] = '\0';
                puts("Enter the year of production:");
                scanf("%d" , &new_node->data->year);
                puts("Enter the price:");
                scanf("%d" , &new_node->data->price);
                puts("Enter the weight:");
                scanf("%f" , &new_node->data->weight);
                puts("Enter the mileage");
                scanf("%f" , &new_node->data->mileage);
                puts("Enter min and max speed");
                scanf("%d %d" , &new_node->data->speed[0] , &new_node->data->speed[1]);
                getchar();
            } else {
                new_node = NULL;
            }
        } else {
            new_node = NULL;
        }
        new_node->next = NULL;
        new_node->prev = NULL;
    }
    return new_node;
}

char **split(char **text , char *string , char *sep)
{
    int count = 0 , i , k = 0, flag = 1,count_to_clear = 0;
    char *res;

    for(i = 0; i < strlen(string); i++){
        if(string[i] == (*sep)){
            count++;
        }
    }

    if((text = malloc((count + 1)*sizeof(char*))) != NULL){
        res = strtok(string , sep);
        if((text[k] = malloc((strlen(res) + 1)*sizeof(char))) != NULL){
            strcpy(text[k] , res);
            count_to_clear++;
            k++;
            while(((res = strtok(NULL , sep)) != NULL) && (flag != 0)){
                if((text[k] = malloc((strlen(res) + 1)*sizeof(char))) != NULL){
                strcpy(text[k] , res);
                count_to_clear++;
                k++;
            } else {
                flag = 0;
                clear_array(text,count_to_clear);
                text = NULL;
            }
        }
        } else {
            clear_array(text,count_to_clear);
            text = NULL;
        }
    }
    return text;
}

void clear_array(char **arr, int count)
{
    int i;
    for(i = 0; i < count; i++){
        free(arr[i]);
        arr[i] = NULL;
    }
    free(arr);
    arr = NULL;
}