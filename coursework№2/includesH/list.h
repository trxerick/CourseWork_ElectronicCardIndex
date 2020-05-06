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
carHead *init_head(carHead *head); // Function for initialising list
void clear_list(carHead *head); // Function for clearing memory that was allocated for list
