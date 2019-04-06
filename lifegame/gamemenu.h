#ifndef _MENU_EXEMPLE
#define _MENU_EXEMPLE

#include "menu.h"
#include "Board.h"

class ExempleMenu : public Menu
{
	Board *x;
  public:
    ExempleMenu(Board &s);
    void executerOption(const string &nom,bool &fin);
    void play();
	void save();
	void load();
};


#endif
