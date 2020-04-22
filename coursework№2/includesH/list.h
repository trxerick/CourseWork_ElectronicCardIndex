#pragma once

#include "declarations.h"

carHead *init_head(carHead *head); // Function for initialising list
void add_first(carHead *head , carNode *node); // Fucntion for adding the first element in the list
void print_list(carHead *head); // Function for printing list at the console
void clear_list(carHead *head); // Function for clearing memory that was allocated for list
