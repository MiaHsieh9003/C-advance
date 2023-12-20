#include "ui.h"
#include "list.h"

int main(void){  
    tNumStorHead *list = (tNumStorHead *) malloc (sizeof(tNumStorHead));
    list = initial_list(list);
    while(1){
        ui_main_menu(list);
    }
}