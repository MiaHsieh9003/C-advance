#include "ui.h"
#include "list.h"

int new_num=0;

void ui_main_menu(tNumStorHead *list){    
    int intNum;
    printf("1. Add a number or 2. Delete a number: "); //input a number to this list
    scanf("%d",&intNum);
    ui_add_menu(list,intNum);     
}

void ui_add_menu(tNumStorHead *list, int intNum){

    if (intNum == 1)    //Add a number
    {           
        ui_get_add_location(list);
        printf("count: %d\n",list->counts);
        list_print(list);
    }   
    else if(intNum == 2){      //Delete a number
        ui_del_menu(list);
        printf("count: %d\n",list->counts);
        list_print(list);            
    }
    else{
        printf("No such choose !\n");
    }
}

void ui_get_add_location(tNumStorHead *list){
    int tar_location =0, tar_loc_num=0; //target number location 
    int print_choo=0;
    tNumStorage *new_ptr = (tNumStorage *)malloc (sizeof(tNumStorage)); //new node
    tNumStorage *tar_ptr = NULL;
    new_ptr->next = NULL;
    new_ptr->bef = NULL;

    printf(" Add a number: ");
    scanf("%d",&new_ptr->number);
    
    if(list->counts == 0){  //add the first number
        list->counts ++;    //list number add 1
        list->head = new_ptr;
        list->tail = new_ptr;   
    }else{
        printf("    Specify a target location: ");
        scanf("%d",&tar_location);
        if(tar_location > list->counts || tar_location < 1){  //out of range in list
            printf("Out of range, please try again!\n");
        }else{            
            list->counts ++;    //list number add 1
            tar_ptr = list->head;
            for(int i=1 ; i<(tar_location) ; ++i){  //找到目標target number
                tar_ptr = tar_ptr->next;     
            }
            tar_loc_num = tar_ptr->number;  //tar_ptr目前指向target location
            
            printf("    1.Before or 2. After the location '%d': ", tar_loc_num);
            scanf("%d", &tar_location);        
            printf("\n");
            if(tar_location == 1 || tar_location == 2)
            { 
                list_add_node(list, tar_ptr, new_ptr, tar_location);
            }else{
                list->counts --;
                printf("Number '%d' is not a correct choose, please try again!\n", tar_location);
            }
        }
    }
}

void ui_del_menu(tNumStorHead *list){
    int choose_tar =0; //choose the action   

    choose_tar = ui_get_del_location();
    if(choose_tar>list->counts || choose_tar<1){
        printf("Not an exist number!\n");
    }else{
        list_del_node(list, choose_tar);
    }

}
int ui_get_del_location(){
    int input;
    printf("    Specify a target location: ");
    scanf("%d",&input);   
    return input;
}