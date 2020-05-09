#include <stdio.h>
#include "../includesH/declarations.h"
#include "../includesH/menu.h"
#include "../includesH/list.h"

// Need to make safe protection!

void say_hello()
{
    CLS;
    puts("\n=Welcome to Eleсtronic card-index=\n");
}

void menu(carHead *head , FILE *fp)
{
    short choice = 1;
    while(choice != 7){
        CLS;
        puts("Menu:\n");
        puts("0 - Read reference");
        puts("1 - Show current card-index");
        puts("2 - Add new card in card-index");
        puts("3 - Delete card from card-index");
        puts("4 - Find cards with parameters");
        puts("5 - Sort cads with parameters");
        puts("6 - Edit existing card");
        puts("7 - Exit and save card-index \n");
        scanf("%hi" , &choice);
        if(choice == 0) print_reference();
        else if(choice == 1) print_list(head);
        else if(choice == 2) add_new_card(head);
        else if(choice == 3) delete_card(head);
        else if(choice == 4) sub_menu_search(head);
        else if(choice == 5) sub_menu_sort();
        else if(choice == 6) sub_menu_edit(head);
    }
    save_file(fp,head);
    puts("\nAll changes has been saved in cart.csv file\n\nPress any key to exit");
    getchar();
    getchar();
    CLS;
}

void sub_menu_search(carHead *head)
{
    int choice;
    CLS;
    puts("Enter the parameter to search:");
    puts("1 - Car's name");
    puts("2 - Car's company");
    puts("3 - Car's year of production");
    puts("4 - Car's price");
    puts("0 - Go back to main menu");
    scanf("%d" , &choice);
    if(choice != 0) search_card(head , choice);
}

void sub_menu_sort()
{
    short choice;
    CLS;
    puts("Enter the parameter to sort:");
    puts("1 - Car's name");
    puts("2 - Car's company");
    puts("3 - Car's year of production");
    puts("4 - Car's price");
    puts("5 - Cars's weight");
    puts("6 - Cars's mileage");
    puts("7 - Cars's min speed in 5 seconds");
    puts("8 - Cars's max speed in 5 seconds");
    puts("0 - Go back to main menu\n");
    scanf("%hi" , &choice);
}

void sub_menu_edit(carHead *head)
{
    short choice;
    int id;
    CLS;
    puts("\nInput id of the element to edit:");
    scanf("%d" , &id);
    if((id > 0) && (id <= head->count)){
        puts("\nEnter the field to edit:");
        puts("\n1 - Name");
        puts("2 - Company");
        puts("3 - Year of production");
        puts("4 - Price");
        puts("5 - Weight");
        puts("6 - Mileage");
        puts("7 - Min speed");
        puts("8 - Max speed");
        puts("0 - Go back to main menu");
        scanf("%hi" , &choice);
        if(choice != 0) edit_card(head , id ,choice);
    } else {
        puts("\nError! There is no card with this id");
        getchar();
    }
    puts("\n\nPress any key to return to main menu");
    getchar();
}

void print_reference()
{
    CLS;
    puts("\nReference:\n");
    puts("This is an electronic file cabinet designed to store cards with cars.");
    puts("Possible file cabinet manipulations can be viewed in the main menu.");
    puts("Each operation can be used several times."); 
    puts("Enter numbers from 1 to 7 to interact with the menu.");
    puts("\n\nPress any key to return to main menu");
    getchar();
    getchar();
    CLS;
}