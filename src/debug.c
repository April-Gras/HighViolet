#include "hv.h"

void print_text_in_rectangle(STATE *state, char *string, int x, int y) {
  SDL_Color White = {255, 255, 255};

  SDL_Surface *surfaceMessage =
      TTF_RenderText_Solid(state->font_sans, string, White);

  SDL_Texture *Message =
      SDL_CreateTextureFromSurface(state->renderer, surfaceMessage);
  int texW = 0;
  int texH = 0;
  SDL_QueryTexture(Message, NULL, NULL, &texW, &texH);
  SDL_Rect dstrect = {x, y, texW, texH};

  SDL_RenderCopy(state->renderer, Message, NULL, &dstrect);

  // Don't forget to free your surface and texture
  SDL_FreeSurface(surfaceMessage);
  SDL_DestroyTexture(Message);
}

void print_hex_to_hex_path_debug_string(STATE *state) {
  bool has_focus = state->focus_reset_target != NULL;
  bool has_hover = state->hover_reset_target != NULL;

  print_text_in_rectangle(state, "some text", 24, 24);
  print_text_in_rectangle(state, "some more text", 24, 48);
  print_text_in_rectangle(state, "lmfao good text lamoooo", 24, 72);
  return;
}

void _print_debug_infos_on_screen(STATE *state) {
  print_hex_to_hex_path_debug_string(state);
}