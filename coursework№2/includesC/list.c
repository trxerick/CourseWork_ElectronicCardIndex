#include "../includesH/list.h"

// ------ Addition and deleting functions ------ //

void add_first(carHead *head , carNode *node)
{
    if(head&&node){
        head->first = node;
        head->last = node;
        head->count++;
    }
}

void add_new_card(carHead *head)
{
    int uid;
    carNode *new_node , *tmp;
    CLS;

    puts("Fill information about new card:\n");
    new_node = get_node();

    if(head->count == 0) { // If the card-index is empty
        head->first = new_node;
        head->last  = new_node;
        new_node->id = 1;
        head->count++;    
        return;
    }

    puts("Enter the id after which you want to insert new card:");
    uid = safe_scanf();

    while((uid <= 0) || (uid > head->count)){
        puts("Error! There is no this id in list! Try again:\n\n");
        uid = safe_scanf();
    }

    if((uid > 0) && (uid <= head->count)){ // If id is correct
        tmp = head->first;

        while(tmp->id != uid){ // Reaching id
            tmp = tmp->next;
        }

        if(tmp->next == NULL){ // If it is the last element
            tmp->next = new_node;
            head->last = new_node;
            new_node->prev = tmp;
            new_node->id = head->count + 1;
        } else { // If it is not the last one
            new_node->next = tmp->next;
            new_node->id = tmp->id;
            tmp->next = new_node;
            new_node->prev = tmp;
            inc_id(head,new_node);
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

        number = safe_scanf();
        while((number > head->count) || (number < 0)){
            puts("Error! There is no card with this number! Try again or enter 0 to comeback to main menu\n");
            getchar();
            number = safe_scanf();
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

/* End of adding and deleting functions */

/* Searching functions and query functions */

int check_borders(int min_bord, int max_bord, int val)
{
    int res = 0;
    if((val >= min_bord) && (val <= max_bord)) res = 1; // The value belongs to the gap

    return res;
}

int compare_card_and_query(carNode *node, query *user_query)
{
    int res = 1,name = 0, company = 0, year = 0, price = 0, min_speed = 0, max_speed = 0;
    
    /* Checking what fields are going to be searched */
    if((strcmp(user_query->name, "None\0")) != 0) name = 1;
    if((strcmp(user_query->company, "None\0"))!=0 ) company = 1;
    if(user_query->low_price != -1) price = 1;
    if(user_query->low_year != -1) year = 1;
    if(user_query->low_speed_max != -1) max_speed = 1;
    if(user_query->low_speed_min != -1) min_speed = 1;

    /* Compare query and card  */
    if((name == 1) && (strcmp(user_query->name, node->data->name) != 0)) res = 0;
    if((company == 1) && (strcmp(user_query->company, node->data->company) != 0)) res = 0;
    if((price == 1) && (check_borders(user_query->low_price, user_query->max_price, node->data->price) != 1)) res = 0; 
    if((year == 1) && (check_borders(user_query->low_year, user_query->max_year, node->data->year) != 1)) res = 0;
    if((max_speed == 1) && (check_borders(user_query->low_speed_max, user_query->max_speed_max, node->data->speed[1]) != 1)) res = 0;
    if((min_speed == 1) && (check_borders(user_query->low_speed_min, user_query->max_speed_min, node->data->speed[0]) != 1)) res = 0;

    return res;
}

void search_card(carHead *head)
{
    int count = 0, i;
    char str[MAXLENGTH];
    carNode *tmp;
    query *user_query;

    /* Initialise query */
    user_query = customize_search(head);
    getchar();
    
    tmp = head->first;

    CLS;

    puts("The results: ");
    
    /* Searching */
    for(i = 0; i < head->count; i++){
        if((compare_card_and_query(tmp, user_query)) == 1){
            print_node(tmp);
            puts("");
            count++;
        }
        tmp = tmp->next;
    }

    clear_query(user_query); // Clearing memory that was allocated for query

    if(count == 0) puts("\nThere are no such cards!\n");
    puts("\nPress any key to comeback to main menu");
    getchar();
}

query *init_query(query *cur_query)
{
    cur_query = malloc(sizeof(query));
    cur_query->name = malloc(MAXLENGTH * sizeof(char));
    cur_query->company = malloc(MAXLENGTH * sizeof(char));

    strcpy(cur_query->name, "None\0");
    strcpy(cur_query->company,"None\0");
    cur_query->low_year = -1;
    cur_query->max_year = -1;
    cur_query->low_price = -1;
    cur_query->max_price = -1;
    cur_query->low_speed_min = -1;
    cur_query->max_speed_min = -1;
    cur_query->low_speed_max = -1;
    cur_query->max_speed_max = -1;

    return cur_query;
}

int check_query_values(int val1, int val2) // Need to check queries
{
    int is_Error = 0;

    if(val2 < val1) { is_Error = 1; puts("\nError! The low value is bigger than the max");getchar();getchar();}
    else if ((val2 < 0) || (val1 < 0)) { is_Error = 1; puts("\nError! Value cannot be negative!"); getchar();getchar();}

    return is_Error;
}

query *customize_search(carHead *head)
{
    short choice = 0;
    query *user_query;
    char data[MAXLENGTH];
    int param1, param2;

    user_query = init_query(user_query);

    while(choice != 7){
        CLS;
        puts("Your searching parameters (-1 means None):\n");
        print_query(user_query);

        puts("\n1 - Enter name\n2 - Enter company\n3 - Enter year\n4 - Enter price\n5 - Enter max speed\n6 - Enter min speed\n7 - Start searching");
        choice = safe_scanf();
        if(choice == 1){
            puts("\nEnter the value(Maximum is 20 symbols):");
            getchar();
            fgets(data,20,stdin);
            data[strlen(data) - 1] = '\0';
            strcpy(user_query->name, data);
        } else if (choice == 2){
            puts("\nEnter the value(Maximum is 17 symbols):");
            getchar();
            fgets(data,17,stdin);
            data[strlen(data) - 1] = '\0';
            strcpy(user_query->company, data);
        } else if (choice == 3){
            puts("Enter the low value and then max value:");
            param1 = safe_scanf(); param2 = safe_scanf();
            if((check_query_values(param1, param2)) != 1) {user_query->low_year = param1; user_query->max_year = param2;}
        } else if (choice == 4){
            puts("Enter the low value and then max value:");
            param1 = safe_scanf(); param2 = safe_scanf();
            if((check_query_values(param1, param2)) != 1) {user_query->low_price = param1; user_query->max_price = param2;}
        } else if (choice == 5){
            puts("Enter the low value and then max value:");
            param1 = safe_scanf(); param2 = safe_scanf();
            if((check_query_values(param1, param2)) != 1) {user_query->low_speed_max = param1; user_query->max_speed_max = param2;}
        } else if (choice == 6){
            puts("Enter the low value and then max value:");
            param1 = safe_scanf(); param2 = safe_scanf();
            if((check_query_values(param1, param2)) != 1) {user_query->low_speed_min = param1; user_query->max_speed_min = param2;}
        } else if ((choice < 0) || (choice > 7)) puts("Error! Try again");
    }

    return user_query;
}

void clear_query(query *user_query)
{
    free(user_query->name);
    free(user_query->company);
    free(user_query);
}
/* End of searching functions */

/* Editing functions */

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
        node->data->name = realloc(node->data->name, (strlen(new_data)+1)*sizeof(char)); // Realloc memory for new data
        strcpy(node->data->name, new_data);
    } else if (key == 2){
        puts("\nEnter new company (Max length 11 symbols):");
        getchar();
        fgets(new_data, 11 ,stdin);
        new_data[strlen(new_data) - 1] = '\0';
        node->data->company = realloc(node->data->company, (strlen(new_data)+1)*sizeof(char)); // Realloc memory for new data
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
        puts("\nEnter new Mileage:");
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

/*End of editing functions */

/* Sorting functions */

void sort_card(carHead *head , int key)
{
    void (*sort_func[2]) (carHead *head, int key) = {sort_number, sort_alpha};
    if((key != 1) && (key != 2)) sort_func[0](head,key);
    else sort_func[1](head,key);
}

void swap_datas(car **data1, car **data2)
{
    car *tmp = *data1;
    *data1 = *data2;
    *data2 = tmp;
}

void sort_number(carHead *head, int key)
{
    int i,j;
    short choice;
    carNode *cur, *indx;
    
    CLS;

    puts("Enter sort preference:");
    puts("\n1 - for Sort Descending");
    puts("2 - for Sort Ascending");
    puts("0 - Return to main menu");

    if(head->first == NULL) return;

    cur = head->first;

    choice = safe_scanf();
    if(choice == 2){
        for(cur = head->first;cur->next != NULL; cur = cur->next){
            for(indx = cur->next; indx != NULL; indx = indx->next){
                if(get_data_int(cur->data,key) > get_data_int(indx->data,key)){
                    swap_datas(&cur->data,&indx->data);
                }
            }
        }
    } else if(choice == 1){
        for(cur = head->first;cur->next != NULL; cur = cur->next){
            for(indx = cur->next; indx != NULL; indx = indx->next){
                if(get_data_int(cur->data,key) < get_data_int(indx->data,key)){
                    swap_datas(&cur->data,&indx->data);
                }
            }
        }
    }
}

void sort_alpha(carHead *head, int key)
{
    int i,j;
    short choice;
    carNode *cur, *indx;

    CLS;

    puts("Enter sort preference:");
    puts("\n1 - for Sort Descending");
    puts("2 - for Sort Ascending");
    puts("0 - Return to main menu");

    if(head->first == NULL) return;

    cur = head->first;

    choice = safe_scanf();
    if(choice == 2){
        for(cur = head->first;cur->next != NULL; cur = cur->next){
            for(indx = cur->next; indx != NULL; indx = indx->next){
                if(strcmp(get_data_str(cur->data,key),get_data_str(indx->data, key)) > 0){
                    swap_datas(&cur->data,&indx->data);
                }
            }
        }
    } else if(choice == 1){
        for(cur = head->first;cur->next != NULL; cur = cur->next){
            for(indx = cur->next; indx != NULL; indx = indx->next){
                if(strcmp(get_data_str(cur->data,key),get_data_str(indx->data, key)) < 0){
                    swap_datas(&cur->data,&indx->data);
                }
            }
        }
    }
}

/* End of sorting functions */

/* Printing functions */
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

void print_query(query *cur_query)
{
    puts("---------------------------");
    printf("|Name:%20s|\n|Company:%17s|\n|Low year:%16d|\n|Max year:%16d|\n|Low price:%15d|\n|Max price:%15d|\n|Low speed max:%11d|\n|Max speed max:%11d|\n|Low speed min:%11d|\n|Max speed min:%11d|\n",
    cur_query->name, cur_query->company,cur_query->low_year, cur_query->max_year, cur_query->low_price, cur_query->max_price,
    cur_query->low_speed_max,cur_query->max_speed_max,cur_query->low_speed_min, cur_query->max_speed_min);
    puts("---------------------------\n");
}

void print_best_cars(carHead *head)
{
    int i;
    carNode *tmp;

    CLS;

    tmp = head->first;

    for(i = 0; i < head->count; i++){
        if((fabs(tmp->data->year + tmp->data->mileage)/tmp->data->price - 1) > __FLT_EPSILON__){
            print_node(tmp);
        }
        tmp = tmp->next;
    }   

    puts("\nPress any key to come back to main menu");
    getchar();
    getchar();
}

/* End of printing functions */

/* Secondary functions */

carHead *init_head(carHead *head)
{
    if((head = malloc(sizeof(carHead))) != NULL){
        head->count = 0;
        head->first = NULL;
        head->last = NULL;
    }
    return head;
}

int get_data_int(car *data, int key)
{
    if(key == 3) return data->year;
    else if(key == 4) return data->price;
    else if(key == 5) return data->speed[0];
    else if(key == 6) return data->speed[1];
}

char* get_data_str(car *data, int key)
{
    if(key == 1) return data->name;
    else if (key == 2) return data->company;
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

void inc_id(carHead *head, carNode *cur_node)
{
    carNode *tmp;

    tmp = cur_node;

    while(tmp != NULL){
        tmp->id++;
        tmp = tmp->next;
    }
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

/* End of secondary functions */
