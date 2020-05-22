#include <stdio.h>
#include "../includesH/declarations.h"
#include "../includesH/menu.h"
#include "../includesH/list.h"

void say_hello()
{
    puts("╔═══╗╔╗───╔═══╗╔═══╗╔════╗╔═══╗╔═══╗╔═╗─╔╗╔══╗╔═══╗     ╔═══╗╔═══╗╔═══╗");     
    puts("║╔══╝║║───║╔══╝║╔═╗║║╔╗╔╗║║╔═╗║║╔═╗║║║╚╗║║╚╣─╝║╔═╗║     ║╔═╗║║╔═╗║║╔═╗║");  
    puts("║╚══╗║║───║╚══╗║║─╚╝╚╝║║╚╝║╚═╝║║║─║║║╔╗╚╝║─║║─║║─╚╝     ║║─╚╝║║─║║║╚═╝║");    
    puts("║╔══╝║║─╔╗║╔══╝║║─╔╗──║║──║╔╗╔╝║║─║║║║╚╗║║─║║─║║─╔╗     ║║─╔╗║╚═╝║║╔╗╔╝");    
    puts("║╚══╗║╚═╝║║╚══╗║╚═╝║──║║──║║║╚╗║╚═╝║║║─║║║╔╣─╗║╚═╝║     ║╚═╝║║╔═╗║║║║╚╗");  
    puts("╚═══╝╚═══╝╚═══╝╚═══╝──╚╝──╚╝╚═╝╚═══╝╚╝─╚═╝╚══╝╚═══╝     ╚═══╝╚╝─╚╝╚╝╚═╝\n\n");
}

void menu(carHead *head , FILE *fp)
{
    int choice = 1;
    void (*menu_func[9])(carHead *head) = {print_reference,print_list,add_new_card,delete_card,sub_menu_search,sub_menu_sort,sub_menu_edit, swap_cards, print_secondary_table};
    while(choice != 9){
        CLS;
        say_hello();
        puts("Menu:\n");
        puts("0 - Read reference");
        puts("1 - Show current card-index");
        puts("2 - Add new card in card-index");
        puts("3 - Delete card from card-index");
        puts("4 - Find cards with parameters");
        puts("5 - Sort cards with parameters");
        puts("6 - Edit existing card");
        puts("7 - Swap two cards");
        puts("8 - Print Rating of cars");
        puts("9 - Exit and save card-index \n");
        choice = safe_scanf();
        if(choice == 0) print_reference();
        else if (choice != 9) menu_func[choice](head);
    }
    save_file(fp,head);
    puts("\nAll changes has been saved in cart.csv file\n\nPress any key to exit");
    getchar();
    getchar();
    CLS;
}

void sub_menu_search(carHead *head)
{
    CLS;
    search_card(head);
}

void sub_menu_sort(carHead *head)
{
    short choice;
    CLS;
    puts("Enter the parameter to sort:");
    puts("1 - Car's name");
    puts("2 - Car's company");
    puts("3 - Car's year of production");
    puts("4 - Car's price");
    puts("5 - Cars's min speed in 5 seconds");
    puts("6 - Cars's max speed in 5 seconds");
    puts("0 - Go back to main menu\n");
    choice = safe_scanf();
    if((choice != 0) && (choice >=1) && (choice <=6)) sort_card(head,choice);
    else {puts("Press any key to return to main menu");getchar();getchar();}
}

void sub_menu_edit(carHead *head)
{
    short choice;
    int id;
    CLS;
    print_cur_list(head);
    puts("\nInput id of the element to edit:");
    id = safe_scanf();
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
        choice = safe_scanf();
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
    puts("\nElectronic card-index\n");
    puts("Author: Epifantsev Egor");
    puts("Student of 9305 group");
    puts("\nReference:\n");
    puts("This is an electronic file cabinet designed to store cards with cars.");
    puts("Possible file cabinet manipulations can be viewed in the main menu.");
    puts("Each operation can be used several times."); 
    puts("Enter numbers from 1 to 8 to interact with the menu.");
    puts("Program supports compound queries for searching. It means that you can personilise your query before searching.");
    puts("If you start searching with empty query , you will get the whole card-index");
    puts("Also there is secondary table in card-index that consists of rating of each car");
    puts("You can watch this rating by choosing 8 in main menu");
    puts("Y means that car is good for it`s price and N means that car is bad");
    puts("Also you can search card via rating (by the secondary table)");
    puts("\n\nPress any key to return to main menu");
    getchar();
    getchar();
    CLS;
}
