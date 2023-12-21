
#ifndef _UI_H_
#define _UI_H_

#include <stdio.h>
#include <stdlib.h>

#include "list.h"

void ui_main_menu(tNumStorHead *list);

void ui_add_menu(tNumStorHead *list, int intNum);
void ui_get_add_location(tNumStorHead *list);

void ui_del_menu(tNumStorHead *list);
int ui_get_del_location();

#endif 