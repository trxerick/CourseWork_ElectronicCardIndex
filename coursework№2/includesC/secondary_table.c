#include "../includesH/secondary_table.h"

void print_secondary_table(carHead *head)
{
    int i;
    carNode *tmp;

    tmp = head->first;

    puts("\nSecondary table:");

    printf("\n|----------------|\n");
    printf("|%3s |%10s |", "Id", "Rating");
    printf("\n|----------------|\n");
    for(i = 0; i < head->count; i++){
        printf("|%3d |%10f |\n", tmp->id, (tmp->data->year + tmp->data->mileage)/tmp->data->price);
        tmp = tmp->next;
    }
    printf("------------------\n");

    puts("Press any key to comeback to main menu");
    getchar();
    getchar();
}