#pragma once

#include "declarations.h"
#include "file.h"
#include "secondary_table.h"

void add_first(carHead *head , carNode *node); // Fucntion for adding the first element in the list
void print_list(carHead *head); // Function for printing list at the console
void add_new_card(carHead *head); // Function for adding new card in the list
void delete_card(carHead *head); // Function for deleting card from list
void delete_card_data(carNode *node); // Secondary function for deleting data about card
void inc_id(carHead *head , carNode *cur_node); // Secondary function for increasing card`s id
void dec_id(carHead *head , carNode *cur_node); // Secondary function for decreasing card`s id
void print_cur_list(carHead *head); // Secondary function for printing list in other functions
void print_node(carNode *node); // Secondary function for printing only one node
void print_best_cars(carHead *head); // Function for printing best cars int the list
void search_card(carHead *head); // Function for searching car with given query
int compare_card_and_query(carNode *node, query *user_query); // Function for comparing card and query
void edit_card(carHead *head, int id , int key); // Function for editing card in card-index
void edit_field(carHead *head , carNode *node , int key); // Secondary function for editing function
void sort_card(carHead *head, int key); // Function for sorintg card-index
void sort_number(carHead *head,int key); // Function for sorting list by integer data
void sort_alpha(carHead *head, int key); // Funtion for sorting list by string data
int get_data_int(car *data,int key); // Fucntion for getting value of data value
char *get_data_str(car *data,int key); // Fucntion for getting value of data value
query *customize_search(carHead *head); // Function for making composite queries
query *init_query(); // Function for initialising query
void clear_query(query *query); // Function for clearing memory that was allocated for query
void print_query(); // Function for printing current query
int check_query_values(int val1, int val2); // Function for checking values in queries
void swap_datas(car **data1, car **data2);// Function for swapping two node`s data
carHead *init_head(carHead *head); // Function for initialising list
void clear_list(carHead *head); // Function for clearing memory that was allocated for list
