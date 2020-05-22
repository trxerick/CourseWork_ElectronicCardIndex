#include "../includesH/secondary_table.h"

void print_secondary_table(carHead *head)
{
    char is_good;
    int i,chooce;
    carNode *tmp;

    tmp = head->first;

    puts("\nSecondary table:");

    printf("\n|----------------|\n");
    printf("|%3s |%10s |", "Id", "Good");
    printf("\n|----------------|\n");
    for(i = 0; i < head->count; i++){
        if((fabs(tmp->data->year + tmp->data->mileage)/tmp->data->price - 1) > __FLT_EPSILON__) is_good = 'Y'; // If difference mote than epsilon than its good car
        else is_good = 'N';
        printf("|%3d |%10c |\n", tmp->id, is_good);
        tmp = tmp->next;
    }
    printf("------------------\n");

    puts("\nPrint the best cars?\n1 - Yes\n2 - No");

    chooce = safe_scanf();

    if(chooce == 1) print_best_cars(head);
    else {
        puts("Press any key to comeback to main menu");
        getchar();
        getchar();
    }

}