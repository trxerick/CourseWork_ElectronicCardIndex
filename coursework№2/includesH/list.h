#pragma once

#include "declarations.h"
#include "file.h"

void add_first(carHead *head , carNode *node); // Fucntion for adding the first element in the list
void print_list(carHead *head); // Function for printing list at the console
void add_new_card(carHead *head); // Function for adding new card in the list
void delete_card(carHead *head); // Function for deleting card from list
void delete_card_data(carNode *node); // Secondary function for deleting data about card
void dec_id(carHead *head , carNode *cur_node); // Secondary function for decreasing card`s id
void print_cur_list(carHead *head); // Secondary function for printing list in other functions
void print_node(carNode *node); // Secondary function for printing only one node
void search_card(carHead *head, int key); // Function for searching card in card-index
void search_card_str(carHead *head,int key); // Function for searching car with given name
void search_card_int(carHead *head, int key); // Function for searching car with given companys
void edit_card(carHead *head, int id , int key); // Function for editing card in card-index
void edit_field(carHead *head , carNode *node , int key); // Secondary function for editing function
void sort_card(carHead *head, int key); // Function for sorintg card-index
void sort_number(carHead *head,int key); // Function for sorting list by integer data
void sort_alpha(carHead *head, int key); // Funtion for sorting list by string data
int get_data_int(car *data,int key); // Fucntion for getting value of data value
char *get_data_str(car *data,int key); // Fucntion for getting value of data value
void swap_datas(car **data1, car **data2); // Function for swapping two node`s data
carHead *init_head(carHead *head); // Function for initialising list
void clear_list(carHead *head); // Function for clearing memory that was allocated for list
