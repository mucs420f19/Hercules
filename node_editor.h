#pragma once

#include "nuklear_config.h"
#include "UMLObjectsHolder.h"

#ifndef NDE_MAX_FUNCS
#define NDE_MAX_FUNCS 32
#endif

#define hovering_in_node(in, bounds) \
  nk_input_is_mouse_hovering_rect (  \
    in, nk_rect (bounds.x, bounds.y - 35.f, bounds.w, bounds.h + 35.f))

#ifndef NDE_RETURN
#define NDE_RETURN struct nk_color
#endif

#ifndef LEN
#define LEN(a) (sizeof (a) / sizeof (a)[0])
#endif

#ifndef MAX_INPUTS
#define MAX_INPUTS 32
#endif

struct node_data
{
  struct nk_color color;

  node_data ()
  {
    color = nk_rgb (255, 0, 0);
  }
};

struct Node;

typedef void (*NodeDrawFn) (Node*, struct nk_context*);
typedef NDE_RETURN (*NodeCalcFn) (Node*, struct node_editor*);

struct node_functions
{
  NodeDrawFn draw;
  NodeCalcFn calc;
};

struct Node
{
  int ID;
  char name[32];
  struct nk_rect bounds;
  float value;
  struct node_data data;
  struct node_link* inputs[MAX_INPUTS];
  struct nk_color gapped_color;
  int input_gapped;
  int min_input_count;
  int input_count;
  bool infinite_inputs;
  int output_count;
  Node* next;
  Node* prev;
  char method[32];
  char field[32];
  char relationship[32];

  node_functions ftable;
};

struct node_link
{
  int input_id;
  int input_slot;
  int output_id;
  int output_slot;
  int id;
  struct nk_vec2 in;
  struct nk_vec2 out;

  void
  draw (node_editor* editor, struct nk_context* ctx);
};


struct node_linking
{
  int active;
  Node* node;
  int input_id;
  int input_slot;
  int output_id;
  int output_slot;
};


struct node_editor
{
  int initialized;
  char name[64];
  Node node_buf[64];
  struct node_link links[256];
  Node* begin;
  Node* end;
  Node* deleted_begin;
  Node* deleted_end;
  Node* hovered;
  bool popupOpened;
  int node_count;
  int link_count;
  struct nk_rect bounds;
  Node* selected;
  struct nk_vec2 scrolling;
  struct node_linking linking;

  void
  push (Node* node, bool delete_list = false);

  Node*
  pop (Node* node, bool delete_list = false);

  Node*
  find (int ID);

  void
  add (const char* name, struct nk_rect bounds, struct node_data data,
       int in_count, int out_count, node_functions ftable,
       bool infinite_inputs = false, int gapped_inputs = 0,
       struct nk_color gapped_color = nk_rgb (252, 227, 3));

  void
  link (int in_id, int in_slot, int out_id, int out_slot,
                     bool uselinking = false);

  void
  clear_gaps ();

  void
  clean_links ();
};

static struct node_functions node_ftables[NDE_MAX_FUNCS];

int
node_edit (struct nk_context* ctx, struct node_editor* nodeedit, const char* title);

void
contextual_menu (struct node_editor* nodeEditor, struct nk_context* ctx,
                 const char* title);

void
node_holder (UMLObjectsHolder* temp);

void
draw_info (Node* cnode, struct nk_context* ctx);
