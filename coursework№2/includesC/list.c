#include "../includesH/list.h"

// ------ Main list functions ------ //

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
    carNode *p;
    if(head){
        if(head->count == 0) puts("The card-index is empty!");
            else {
            if((p = head->first) != NULL){
                printf("\n|--------------------------------------------------------------------------------------------------|\n");
                printf("|%3s |%21s |%11s |%5s |%5s |%11s |%8s |%9s |%9s|\n" ,"Id", "Name" , "Company" , "Year" , "Price" , "Weight" ,
                "Mileage" , "Min speed" , "Max speed");
                printf("|--------------------------------------------------------------------------------------------------|\n");
                while(p != NULL){
                    printf("|%3d |%21s |%11s |%5d |%5d |%11.3f |%8.3f |%9d |%9d|\n" , p->id ,p->data->name , p->data->company ,
                    p->data->year, p->data->price , p->data->weight , 
                    p->data->mileage, p->data->speed[0] , p->data->speed[1]);
                    p = p->next;
                }
            }
        }
    }
    puts("\nPress any key to come back to main menu");
    getchar();
    getchar();
}

void add_new_card(carHead *head)
{
    carNode *new_node , *tmp;
    CLS;

    puts("Fill information about new card:\n");
    new_node = get_node();

    if(head->count == 0){ // If adding first node
        new_node->id = 1;
        head->first = new_node;
        head->last = new_node;
    } else { // If adding not first node
        tmp = head->first;
        while(tmp != NULL){
            if(tmp == head->last){
                head->last = new_node;
                new_node->id = tmp->id + 1;
                new_node->prev = tmp;
                tmp->next = new_node;
                tmp = NULL; 
            } else tmp = tmp->next;
        }
    }

    head->count++;
}

void delete_card(carHead *head)
{
    carNode *tmp;
    int number = -1;
    
    CLS;

    if(head->count == 0){puts("The card-index is empty! Press any key to return to main menu"); getchar();getchar(); return;}

    while((number != 0) && (head->count != 0)){
        print_cur_list(head);
        puts("\nChoose number of card to delete. Or enter 0 to come back to main menu:\n");

        scanf("%d" , &number);
        while((number > head->count) || (number < 0)){
            puts("Error! There is no card with this number! Try again or enter 0 to comeback to main menu\n");
            scanf("%d" , &number);
        }
    
        tmp = head->first;

        while(tmp != NULL){
            if(tmp->id == number){
                if(head->count == 1){ // If single element is going to be deleted
                    head->first = NULL;
                    head->last = NULL;
                } else {
                    if(tmp == head->first){ // If first element is going to be deleted
                        head->first = tmp->next;
                        head->first->prev = NULL;
                        dec_id(head, head->first);
                    } else if (tmp == head->last){ // If last element is going to be deleted
                        head->last->prev->next = NULL;
                        head->last = tmp->prev;
                    } else { // If not last and not first element is going to be deleted
                        tmp->prev->next = tmp->next;
                        tmp->next->prev = tmp->prev;
                        dec_id(head,tmp);
                    }
                }
                delete_card_data(tmp);
                tmp = NULL;
                head->count--;
            } else tmp = tmp->next;
        }
    }
}

void search_card(carHead *head , int key)
{
    void (*search_func[4]) (carHead *head) = {search_card_name , search_card_company, search_card_year, search_card_price};
    search_func[key - 1](head);
}

void edit_card(carHead *head , int id, int key)
{
    carNode *tmp;
    
    tmp = head->first;

    while(tmp != NULL){
        if(tmp->id == id){
            puts("You are going to update this card:\n");
            print_node(tmp);
            edit_field(head,tmp,key);
            tmp = NULL;
        } else tmp = tmp->next;
    }
}


// ------Secondary list functions------ //

carHead *init_head(carHead *head)
{
    if((head = malloc(sizeof(carHead))) != NULL){
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
    }
    return head;
}

void search_card_name(carHead *head)
{
    int count = 0, i;
    char str[MAXLENGTH];
    carNode *tmp;
    
    tmp = head->first;
        
    puts("\nEnter the name of car to find:");
    getchar();
    fgets(str,MAXLENGTH,stdin);
    str[strlen(str) - 1] = '\0';

    CLS;
    puts("The results: ");
    
    for(i = 0; i < head->count; i++){
        if((strcmp(tmp->data->name, str)) == 0){
            count++;
            print_node(tmp);
        }
        tmp = tmp->next;
    }

    if(count == 0) puts("\nThere are no such cards!\n");
    puts("\nPress any key to comeback to main menu");
    getchar();
}

void search_card_company(carHead *head)
{
    int count = 0, i;
    char str[MAXLENGTH];
    carNode *tmp;
    
    tmp = head->first;
        
    puts("\nEnter the company of car to find:");
    getchar();
    fgets(str,MAXLENGTH,stdin);
    str[strlen(str) - 1] = '\0';

    CLS;
    puts("\nThe results:");
    
    for(i = 0; i < head->count; i++){
        if((strcmp(tmp->data->company, str)) == 0){
            count++;
            print_node(tmp);
        }
        tmp = tmp->next;
    }
    if(count == 0) puts("\nThere are no such cards!\n");
    puts("\nPress any key to comeback to main menu");
    getchar();
}

void search_card_year(carHead *head)
{
    int count = 0,param,i;
    carNode *tmp;
    
    tmp = head->first;
        
    puts("\nEnter the year of production to find:");
    scanf("%d" , &param);

    CLS;
    puts("\nThe results:");
    
    for(i = 0; i < head->count; i++){
        if(tmp->data->year == param){
            count++;
            print_node(tmp);
        }
        tmp = tmp->next;
    }
    getchar();
    if(count == 0) puts("\nThere are no such cards!\n");
    puts("\nPress any key to comeback to main menu");
    getchar();
}

void search_card_price(carHead *head)
{
    int count = 0, param, i;
    carNode *tmp;
    
    tmp = head->first;
        
    puts("\nEnter the price of car to find:");
    scanf("%d" , &param);

    CLS;
    puts("\nThe results: ");
    
    for(i = 0; i < head->count; i++){
        if(tmp->data->price == param){
            count++;
            print_node(tmp);
        }
        tmp = tmp->next;
    }
    getchar();
    if(count == 0) puts("\nThere are no such cards!\n");
    puts("\nPress any key to comeback to main menu");
    getchar();
}

void edit_field(carHead *head, carNode *node, int key)
{
    char new_data[21];
    int new_data_int;
    float new_data_float;

    if(key == 1){
        puts("\nEnter new name (Max length 21 symbols):");
        getchar();
        fgets(new_data, 21 ,stdin);
        new_data[strlen(new_data) - 1] = '\0';
        strcpy(node->data->name, new_data);
    } else if (key == 2){
        puts("\nEnter new company (Max length 11 symbols):");
        getchar();
        fgets(new_data, 11 ,stdin);
        new_data[strlen(new_data) - 1] = '\0';
        strcpy(node->data->company, new_data);
    } else if(key == 3){
        puts("\nEnter new year:");
        scanf("%d" , &new_data_int);
        node->data->year = new_data_int;
    } else if(key == 4){
        puts("\nEnter new price:");
        scanf("%d" , &new_data_int);
        node->data->price = new_data_int;
    } else if(key == 5){
        puts("\nEnter new weight:");
        scanf("%f" , &new_data_float);
        node->data->weight = new_data_float;
    } else if (key == 6){
        puts("\nEnter new MIleage:");
        scanf("%f" , &new_data_float);
        node->data->mileage = new_data_float;
    } else if (key == 7){
        puts("\nEnter new min speed:");
        scanf("%d" , &new_data_int);
        node->data->speed[0] = new_data_int;
    } else if(key == 8){
        puts("\nEnter new max speed:");
        scanf("%d" , &new_data_int);
        node->data->speed[1] = new_data_int;
    }
    puts("\nThe updated card:\n");
    print_node(node);
}

void delete_card_data(carNode *node)
{
    free(node->data->name);
    free(node->data->company);
    free(node->data);
    free(node);
}

void dec_id(carHead *head , carNode *cur_node)
{
    carNode *tmp;

    tmp = cur_node;

    while(tmp != NULL){
        tmp->id--;
        tmp = tmp->next;
    }
}

void print_cur_list(carHead *head)
{
    CLS;
    carNode *p;
    if(head){
        if(head->count == 0) puts("The card-index is empty!");
            else {
            if((p = head->first) != NULL){
                printf("\n|--------------------------------------------------------------------------------------------------|\n");
                printf("|%3s |%21s |%11s |%5s |%5s |%11s |%8s |%9s |%9s|\n" ,"Id", "Name" , "Company" , "Year" , "Price" , "Weight" ,
                "Mileage" , "Min speed" , "Max speed");
                printf("|--------------------------------------------------------------------------------------------------|\n");
                while(p != NULL){
                    printf("|%3d |%21s |%11s |%5d |%5d |%11.3f |%8.3f |%9d |%9d|\n" , p->id ,p->data->name , p->data->company ,
                    p->data->year, p->data->price , p->data->weight , 
                    p->data->mileage, p->data->speed[0] , p->data->speed[1]);
                    p = p->next;
                }
            }
        }
    }
}

void print_node(carNode *node)
{
    printf("\n|--------------------------------------------------------------------------------------------------|\n");
    printf("|%3s |%21s |%11s |%5s |%5s |%11s |%8s |%9s |%9s|\n" ,"Id", "Name" , "Company" , "Year" , "Price" , "Weight" ,
    "Mileage" , "Min speed" , "Max speed");
    printf("|--------------------------------------------------------------------------------------------------|\n");
    printf("|%3d |%21s |%11s |%5d |%5d |%11.3f |%8.3f |%9d |%9d|\n" , node->id ,node->data->name , node->data->company ,
                    node->data->year, node->data->price , node->data->weight , 
                    node->data->mileage, node->data->speed[0] , node->data->speed[1]);
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