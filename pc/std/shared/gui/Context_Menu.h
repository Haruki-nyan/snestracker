#pragma once
#include "Clickable_Text.h"

struct Context_Menu_Item
{
  Context_Menu_Item(const char *str="", bool is_visible=false, int (*action)(void *)=NULL, void *data=NULL);
  Clickable_Text clickable_text;
  bool is_visible;
};

struct Context_Menu
{
	/* Let's use this like a TextEditRect currently_editing_ter. if it's a
	 * valid pointer, then there's an active context menu present and we can
	 * react appropriately in external event handler code */
	static Context_Menu *currently_active_context_menu;

  bool is_activated();
  bool toggle_activate();
  void activate();
  void deactivate();

  void hover_highlight(bool yesno);
  void highlight_currently_selected_item(bool yesno);

  bool receive_event(const SDL_Event &ev);

  SDL_Rect created_at;  // the mouse coordinate when context menu was created
  Context_Menu(Context_Menu_Item *array,  bool isActive=false, bool isStatic=false);
  void preload(int &x, int &y, bool use_cache=false);
  void draw(SDL_Surface *screen);
  bool do_thing(void *data=NULL);
  Context_Menu_Item *items=NULL;
  
  bool is_active=false;
  bool is_static=false;
  int greatest_length=0, visible_items=0;
  Context_Menu_Item *highlighted_item=NULL;

  // V2
  bool should_highlight_hover=true;
  bool should_highlight_currently_selected_item=false;
  Context_Menu_Item *currently_selected_item=NULL;
  int currently_selected_item_index=0;
};
