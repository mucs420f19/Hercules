#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "node_editor.h"

UMLObjectsHolder* holder = nullptr;

void
node_link::draw (node_editor* nodeedit, nk_context* ctx)
{
  Node* ni = nodeedit->find (input_id);
  Node* no = nodeedit->find (output_id);
  if (!ni || !no)
    return;
  nk_command_buffer* canvas = nk_window_get_canvas (ctx);
  float spacei = ni->bounds.h / (float)((ni->output_count) + 1);
  int inputs = (no->infinite_inputs && nodeedit->linking.active &&
                nodeedit->linking.node != no && no->input_count < MAX_INPUTS)
                 ? no->input_count + 1
                 : no->input_count;
  float spaceo = no->bounds.h / (float)((inputs) + 1);
  struct nk_vec2 l0 = nk_layout_space_to_screen (
    ctx,
    nk_vec2 (ni->bounds.x + ni->bounds.w,
             3.0f + ni->bounds.y + spacei * (float)(this->input_slot + 1)));
  struct nk_vec2 l1 = nk_layout_space_to_screen (
    ctx, nk_vec2 (no->bounds.x, 3.0f + no->bounds.y +
                                  spaceo * (float)(this->output_slot + 1)));

  l0.x -= nodeedit->scrolling.x;
  l0.y -= nodeedit->scrolling.y;
  l1.x -= nodeedit->scrolling.x;
  l1.y -= nodeedit->scrolling.y;
  nk_stroke_curve (canvas, l0.x, l0.y, l0.x + 50.0f, l0.y, l1.x - 50.0f, l1.y,
                   l1.x, l1.y, 3.0f, nk_rgb (252, 227, 3));
}


static struct node_editor nodeEditor;
char className[32] = {0};
char tempName[32] = {0};
char overwrite[32] = {0};

void
node_editor::push (Node* node, bool delete_list)
{
  Node** begin;
  Node** end;
  if (delete_list)
  {
    begin = &deleted_begin;
    end = &deleted_end;
  }
  else
  {
    begin = &this->begin;
    end = &this->end;
  }
  if (!*begin)
  {
    node->next = NULL;
    node->prev = NULL;
    *begin = node;
    *end = node;
  }
  else
  {
    node->prev = *end;
    if (*end)
      (*end)->next = node;
    node->next = NULL;
    *end = node;
  }
}

Node*
node_editor::pop (Node* node, bool delete_list)
{
  Node** begin;
  Node** end;
  if (delete_list)
  {
    begin = &this->deleted_begin;
    end = &this->deleted_end;
  }
  else
  {
    begin = &this->begin;
    end = &this->end;
  }
  if (node->next)
    node->next->prev = node->prev;
  if (node->prev)
    node->prev->next = node->next;
  if (*end == node)
    *end = node->prev;
  if (*begin == node)
    *begin = node->next;
  node->next = NULL;
  node->prev = NULL;
  return node;
}

Node*
node_editor::find (int ID)
{
  Node* iter = this->begin;
  while (iter)
  {
    if (iter->ID == ID)
      return iter;
    iter = iter->next;
  }
  return NULL;
}

void
node_editor::add (const char* name, struct nk_rect bounds,
                  struct node_data data, int in_count, int out_count,
                  node_functions ftable, bool infinite_inputs,
                  int gapped_inputs, struct nk_color gapped_color)
{
  Node* node;
  if (!this->deleted_begin)
  {
    if ((nk_size)this->node_count >= LEN (this->node_buf))
      return;
    node = &this->node_buf[this->node_count];
    node->ID = this->node_count;
    ++this->node_count;
  }
  else
  {
    node = pop (this->deleted_begin, true);
  }
  node->data = data;
  node->infinite_inputs = infinite_inputs;
  node->input_count = in_count;
  node->gapped_color = gapped_color;
  node->input_gapped = gapped_inputs;
  node->min_input_count = in_count;
  node->output_count = out_count;
  node->bounds = bounds;
  node->ftable = ftable;
  strcpy (node->name, name);
  push (node);
}

void
node_editor::link (int in_id, int in_slot, int out_id, int out_slot,
                   bool uselinking)
{
  struct node_link* link = NULL;
  Node* node = find (out_id);
  if (!node)
  {
    return;
  }
  if (uselinking && this->linking.output_id == out_id)
  {
    node_link* temp = node->inputs[this->linking.output_slot];
    if (temp)
    {
      temp->output_slot = out_slot;
    }
    node->inputs[this->linking.output_slot] = node->inputs[out_slot];
    if (node->inputs[out_slot])
    {
      node->inputs[out_slot]->output_slot = this->linking.output_slot;
    }
    node->inputs[out_slot] = temp;
  }
  if (node->inputs[out_slot] == NULL)
  {
    for (int i = 0; i < this->link_count; i++)
    {
      if (this->links[i].output_id < 0 || this->links[i].input_id < 0)
      {
        link = &this->links[i];
        break;
      }
    }
    if (!link)
    {
      if ((nk_size)this->link_count >= LEN (this->links))
      {
        return;
      }
      link = &this->links[this->link_count];
      link->id = this->link_count++;
    }
  }
  else
  {
    link = node->inputs[out_slot];
  }
  link->input_id = in_id;
  link->input_slot = in_slot;
  link->output_id = out_id;
  link->output_slot = out_slot;
  node->inputs[out_slot] = link;
  if (node->infinite_inputs && out_slot >= node->input_count)
  {
    node->input_count = out_slot + 1;
  }
}

//I have a feeling the loop inside this function can be optimized
void
node_editor::clear_gaps ()
{
  for (int i = 0; i < this->node_count; i++)
  {
    Node* node = &this->node_buf[i];
    if (!node->infinite_inputs)
      continue;
    //TC needed to prevent the loop from staying infinite
    int tc = 0;
    for (int o = node->input_gapped; o < node->input_count; o++)
    {
      if (tc < node->input_count &&
          (!node->inputs[o] || node->inputs[o]->output_id < 0 ||
           node->inputs[o]->input_id < 0))
      {
        for (int u = o + 1; u < node->input_count; u++)
        {
          node->inputs[u - 1] = node->inputs[u];
          if (node->inputs[u] && node->inputs[u]->output_id >= 0 &&
              node->inputs[u]->input_id >= 0)
            node->inputs[u]->output_slot--;
          node->inputs[u] = NULL;
        }
        o--;
        tc++;
      }
      else
        tc = o;
    }
    node->input_count = node->min_input_count - 1;
    if (node->input_count < node->input_gapped)
      node->input_count = node->input_gapped;
    if (node->input_count < 0)
      node->input_count = 0;
    while (node->input_count < MAX_INPUTS && node->inputs[node->input_count] &&
           node->inputs[node->input_count]->output_id >= 0 &&
           node->inputs[node->input_count]->input_id >= 0)
      node->input_count++;
  }
}

void
node_editor::clean_links ()
{
  Node* tnode = this->begin;
  do
  {
    if (!tnode)
      break;
    int LIMIT = (tnode->infinite_inputs ? MAX_INPUTS : tnode->input_count);
    for (int o = 0; o < LIMIT; o++)
    {
      if (!tnode->inputs[o] || !find (tnode->inputs[o]->input_id))
      {
        if (tnode->inputs[o])
        {
          tnode->inputs[o]->output_id = -1;
        }
        tnode->inputs[o] = NULL;
      }
    }
    tnode = tnode->next;
  } while (tnode);

  tnode = this->deleted_begin;
  do
  {
    if (!tnode)
    {
      break;
    }
    int LIMIT = (tnode->infinite_inputs ? MAX_INPUTS : tnode->input_count);
    for (int o = 0; o < LIMIT; o++)
    {
      if (tnode->inputs[o])
      {
        tnode->inputs[o]->output_id = -1;
      }
      tnode->inputs[o] = NULL;
    }
    tnode = tnode->next;
  } while (tnode);
}

static const char* DELETE_MENU_OPTION = "Delete";

void
contextual_menu (struct node_editor* nodeEditor, struct nk_context* ctx,
                 const char* title)
{
  if (nk_window_is_active (ctx, title) &&
           nk_contextual_begin (ctx, 0, nk_vec2 (200, 220),
                                nk_window_get_bounds (ctx)))
  {
    nodeEditor->popupOpened = true;
    nk_layout_row_dynamic (ctx, 25, 1);
    if (nk_contextual_item_label (ctx, DELETE_MENU_OPTION, NK_TEXT_CENTERED))
    {
      nodeEditor->pop (nodeEditor->hovered);
      holder->DeleteClass (nodeEditor->hovered->name);
      nodeEditor->push (nodeEditor->hovered, true);
      nodeEditor->clean_links ();
      nodeEditor->clear_gaps ();
    }

    nk_layout_row_static (ctx, 0, 100, 2);
    nk_edit_string_zero_terminated (ctx, NK_EDIT_FIELD, tempName,
                                    sizeof (tempName) - 1, nk_filter_default);
    if (nk_contextual_item_label (ctx, "Edit", NK_TEXT_CENTERED))
    {
      if (!(holder->CreateNewClass (tempName)))
      {
        holder->DeleteClass (nodeEditor->hovered->name);
        holder->EditClassTitle (tempName, nodeEditor->hovered->name);
      }
      strcpy (nodeEditor->hovered->name, tempName);
      strcpy (tempName, overwrite);
    }
    nk_contextual_end (ctx);
  }
  else if (nk_window_is_active (ctx, title))
  {
    nodeEditor->hovered = NULL;
    nodeEditor->popupOpened = false;
  }
}

int
node_edit (struct nk_context* ctx, struct node_editor* nodeedit, const char* title)
{
  int n = 0;
  struct nk_rect total_space;
  const struct nk_input* in = &ctx->input;
  struct nk_command_buffer* canvas;
  Node* updated = 0;
  struct node_editor* nodedit = &nodeEditor;

  if (!nodeEditor.initialized)
  {
    //node_editor_init (&nodeEditor);
    nodeEditor.initialized = 1;
  }

  if (nk_begin (ctx, title, nk_rect (450, 0, 800, WINDOW_HEIGHT),
                NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE))
  {
    /* allocate complete window space */
    canvas = nk_window_get_canvas (ctx);
    total_space = nk_window_get_content_region (ctx);
    nk_layout_space_begin (ctx, NK_STATIC, total_space.h, nodeedit->node_count);
    {
      Node* it = nodeedit->begin;
      struct nk_rect size = nk_layout_space_bounds (ctx);

      bool drawLink = false;
      struct nk_vec2 link_l0;
      struct nk_vec2 link_l1 = in->mouse.pos;

      /* draw each link */
      for (n = 0; n < nodeedit->link_count; ++n)
      {
        struct node_link* link = &nodeedit->links[n];
        link->draw (nodeedit, ctx);
        // TODO
      }

      /* execute each node as a movable group */
      struct nk_panel* node;
      while (it)
      {
        /* calculate scrolled node window position and size */
        nk_layout_space_push (ctx,
                              nk_rect (it->bounds.x - nodeedit->scrolling.x,
                                       it->bounds.y - nodeedit->scrolling.y,
                                       it->bounds.w, it->bounds.h));
        holder->SetX (it->name, it->bounds.x);
        holder->SetY (it->name, it->bounds.y);
        /* execute node window */
        if (nk_group_begin (ctx, it->name,
                            NK_WINDOW_MOVABLE | NK_WINDOW_BORDER |
                              NK_WINDOW_TITLE | NK_WINDOW_SCALABLE))
        {
          /* always have last selected node on top */

          node = nk_window_get_panel (ctx);
          if (updated != nodeedit->end && hovering_in_node (in, node->bounds) &&
              (!(it->prev &&
                 hovering_in_node (
                   in, nk_layout_space_rect_to_screen (ctx, node->bounds)))))
          {
            updated = it;
          }
          /* contextual menu */
          if (!nodeedit->popupOpened && hovering_in_node (in, node->bounds))
            nodeedit->hovered = it;

          /* ================= NODE CONTENT =====================*/
          for (auto i : holder->GetUMLObject (it->name)->ReturnMethodsRaw ())
          {
            nk_layout_row_begin (ctx, NK_STATIC, 25, 3);
            nk_layout_row_push (ctx, 100);
            nk_label (ctx, i.return_type.c_str (), NK_TEXT_LEFT);
            nk_label (ctx, i.name.c_str (), NK_TEXT_LEFT);
          }

          nk_layout_row_begin (ctx, NK_STATIC, 25, 5);
          nk_layout_row_push (ctx, 155);
          {
            nk_label (ctx, "________________________", NK_TEXT_LEFT);
          }

          for (auto i : holder->GetUMLObject (it->name)->ReturnFieldsRaw ())
          {
            nk_layout_row_begin (ctx, NK_STATIC, 25, 5);
            nk_layout_row_push (ctx, 100);
            nk_label (ctx, i.name.c_str (), NK_TEXT_LEFT);
            nk_label (ctx, i.type.c_str (), NK_TEXT_LEFT);
          }
          /* ====================================================*/
          nk_group_end (ctx);
        }
        {
          /* node connector and linking */
          float space;
          struct nk_rect bounds;
          bounds = nk_layout_space_rect_to_local (ctx, node->bounds);
          bounds.x += nodeedit->scrolling.x;
          bounds.y += nodeedit->scrolling.y;
          it->bounds = bounds;

          /* output connector */
          space = node->bounds.h / (float)((it->output_count) + 1);
          for (n = 0; n < it->output_count; ++n)
          {
            struct nk_rect circle;
            circle.x = node->bounds.x + node->bounds.w - 4;
            circle.y = node->bounds.y + space * (float)(n + 1);
            circle.w = 15;
            circle.h = 15;
            nk_fill_circle (canvas, circle, nk_rgb (252, 186, 3));

            /* start linking process */
            if (nk_window_is_active (ctx, title) &&
                nk_input_has_mouse_click_down_in_rect (in, NK_BUTTON_LEFT,
                                                       circle, nk_true))
            {
              nodeedit->linking.active = nk_true;
              nodeedit->linking.node = it;
              nodeedit->linking.input_id = it->ID;
              nodeedit->linking.input_slot = n;
              nodeedit->linking.output_id = -1;
            }

            if (nodeedit->linking.active && nodeedit->linking.node == it &&
                nodeedit->linking.input_slot == n)
            {
              link_l0 = nk_vec2 (circle.x + 3, circle.y + 3);
              drawLink = true;
            }
          }

          int inputs =
            (it->infinite_inputs && nodeedit->linking.active &&
             nodeedit->linking.node != it && it->input_count < MAX_INPUTS)
              ? it->input_count + 1
              : it->input_count;
          /* input connector */
          space = node->bounds.h / (float)(inputs + 1);
          for (n = 0; n < inputs; ++n)
          {
            struct nk_rect circle;
            circle.x = node->bounds.x - 4;
            circle.y = node->bounds.y + space * (float)(n + 1);
            circle.w = 15;
            circle.h = 15;
            nk_fill_circle (canvas, circle,
                            n < it->input_gapped ? it->gapped_color
                                                 : nk_rgb (252, 186, 3));

            /* start linking process */
            if (nk_window_is_active (ctx, title) &&
                nk_input_has_mouse_click_down_in_rect (in, NK_BUTTON_LEFT,
                                                       circle, nk_true) &&
                it->inputs[n])
            {
              Node* target = nodeedit->find (it->inputs[n]->input_id);
              if (target)
              {
                nodeedit->linking.active = nk_true;
                nodeedit->linking.node = target;
                nodeedit->linking.input_id = target->ID;
                nodeedit->linking.input_slot = it->inputs[n]->input_slot;
                nodeedit->linking.output_id = it->ID;
                nodeedit->linking.output_slot = n;
                it->inputs[n]->input_id = -1;
              }
            }
            if (nk_input_is_mouse_hovering_rect (in, circle) &&
                (!nodeedit->linking.active || nodeedit->linking.node != it))
              link_l1 = nk_vec2 (circle.x + 3, circle.y + 3);

            if (nk_input_is_mouse_released (in, NK_BUTTON_LEFT) &&
                nk_input_is_mouse_hovering_rect (in, circle) &&
                nodeedit->linking.active && nodeedit->linking.node != it)
            {
              nodeedit->linking.active = nk_false;
              nodeedit->link (nodeedit->linking.input_id,
                              nodeedit->linking.input_slot, it->ID, n, true);
              nodeedit->clear_gaps ();
            }
          }
        }
        it = it->next;
      }

      /* draw curve from linked node slot to mouse position */
      if (drawLink)
        nk_stroke_curve (canvas, link_l0.x, link_l0.y, link_l0.x + 50.0f,
                         link_l0.y, link_l1.x - 50.0f, link_l1.y, link_l1.x,
                         link_l1.y, 3.0f, nk_rgb (252, 227, 3));

      /* reset linking connection */
      if (nodeedit->linking.active &&
          nk_input_is_mouse_released (in, NK_BUTTON_LEFT))
      {
        nodeedit->linking.active = nk_false;
        nodeedit->linking.node = NULL;
        nodeedit->clear_gaps ();
        fprintf (stdout, "linking failed\n");
      }

      if (updated)
      {
        /* reshuffle nodes to have least recently selected node on top */
        nodeedit->pop (updated);
        nodeedit->push (updated);
      }

      /* node selection */
      if (nk_window_is_active (ctx, title) &&
          nk_input_is_mouse_down (in, NK_BUTTON_LEFT) &&
          hovering_in_node (in, nk_layout_space_bounds (ctx)))
      {
        it = nodeedit->begin;
        nodeedit->selected = NULL;
        nodeedit->bounds = nk_rect (in->mouse.pos.x, in->mouse.pos.y, 100, 200);
        while (it)
        {
          struct nk_rect b = nk_layout_space_rect_to_screen (ctx, it->bounds);
          b.x -= nodeedit->scrolling.x;
          b.y -= nodeedit->scrolling.y;
          if (hovering_in_node (in, b))
            nodeedit->selected = it;
          it = it->next;
        }
      }

      /* contextual menu */
      contextual_menu (nodeedit, ctx, title);
    }
    nk_layout_space_end (ctx);

    /* window content scrolling */
    if (nk_window_is_active (ctx, title) &&
        nk_input_is_mouse_down (in, NK_BUTTON_MIDDLE))
    {
      nodeedit->scrolling.x -= in->mouse.delta.x;
      nodeedit->scrolling.y -= in->mouse.delta.y;
    }
  }
  nk_end (ctx);
  return !nk_window_is_closed (ctx, title);
}

void
node_holder (UMLObjectsHolder* temp)
{
  holder = temp;
}

void
draw_info (Node* cnode, struct nk_context* ctx)
{
}
