#include "includesH/declarations.h"
#include "includesH/menu.h"
#include "includesH/file.h"
#include "includesH/list.h"

int main()
{
    FILE *fp;
    carHead *head;
    
    if((fp = fopen("cart.csv" , "r")) != NULL){
        say_hello();
        head = init_head(head);
        read_file(fp , head);
        menu(head);

        clear_list(head);
        fclose(fp);
    } else {puts("Error while openning file!");}
    
    return 0;
}