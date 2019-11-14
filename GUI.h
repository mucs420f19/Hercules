#pragma once
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include "REPL.h"
#include <cmath>

#include "GL/glew.h"
#include "GLFW/glfw3.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#define INCLUDE_STYLE
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#include "nuklear.h"
#include "nuklear_glfw_gl3.h"
#include "style.c"
#include "node_editor.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

void RunGUI(UMLObjectsHolder* holder);
void GUI_Label(nk_context *ctx, std::string in, std::string alignment);
void GUI_Text_Box(nk_context *ctx, char temp[256]);
int GUI_Button(nk_context *ctx, const char * name);
int GUI_Textbox_Button(nk_context *ctx, char * temp, const char * name);
void GUI_menu(nk_context *ctx, int buttons, char * temp);

static void error_callback(int e, const char* d)
{
	printf("Error %d: %s\n", e, d);
}

void RunGUI(UMLObjectsHolder* holder)
{
	/* Platform */
	static GLFWwindow *win;
	int width = 0, height = 0;
	struct nk_context *ctx;
	struct nk_colorf bg;
	char add[256] = { 0 };
	char edit[256] = { 0 };
	char del[256] = { 0 };
	char save[256] = { 0 };
	char load[256] = { 0 };
	char method[256] = { 0 };
	char editMethod[256] = { 0 };
	char tempName[256] = { 0 };
	char field[256] = { 0 };
	char editField[256] = { 0 };
	char classname[256] = { 0 };
	char overwrite[256] = { 0 };
	char type[256] = { 0 };
	static int popup_active;
	node_ftables[1].draw = &draw_info;
	static struct node_editor node1;
	static struct node_editor node2;

	/* GLFW */
	glfwSetErrorCallback(error_callback);
	if (!glfwInit())
	{
		fprintf(stdout, "[GFLW] failed to init!\n");
		exit(1);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hercules UML Editor", NULL, NULL);
	glfwMakeContextCurrent(win);
	glfwGetWindowSize(win, &width, &height);

	/* OpenGL */
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glewExperimental = 1;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to setup GLEW\n");
		exit(1);
	}

	ctx = nk_glfw3_init(win, NK_GLFW3_INSTALL_CALLBACKS);
	/* Load Fonts: if none of these are loaded a default font will be used  */
	/* Load Cursor: if you uncomment cursor loading please hide the cursor */
	{
		struct nk_font_atlas *atlas;
		nk_glfw3_font_stash_begin(&atlas);
		nk_glfw3_font_stash_end();
	}

#ifdef INCLUDE_STYLE
	set_style(ctx, THEME_DARK);
#endif	

	//Background window color
	bg.r = 0.00f, bg.g = 0.00f, bg.b = 0.00f, bg.a = 0.00f;
	while (!glfwWindowShouldClose(win))
	{
		/* Input */
		glfwPollEvents();
		nk_glfw3_new_frame();

		/* GUI */
		if (nk_begin(ctx, " ", nk_rect(0, 0, 450, WINDOW_HEIGHT),
			NK_WINDOW_BORDER | NK_WINDOW_MOVABLE | NK_WINDOW_SCALABLE |
			NK_WINDOW_TITLE))

			//Begin menubar here or core dump later on		
			nk_menubar_begin(ctx);

		//Saving and Loading buttons
		{
			nk_layout_row_static(ctx, 50, 200, 2);
			//nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, save, sizeof(save) - 1, nk_filter_default);
			//GUI_Text_Box(ctx, save);
			//if (nk_button_label(ctx, "Save"))
			//if (GUI_Button(ctx, "Save"))
			if(GUI_Textbox_Button(ctx, save, "Save"))
				SavingLoadingIO::SaveProjectToFile(holder, save, true);
			//nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, load, sizeof(load) - 1, nk_filter_default);
			//GUI_Text_Box(ctx, load);
			//if GUI_Button(ctx, "Load"))
			if (GUI_Textbox_Button(ctx, load, "Load"))
			{
				SavingLoadingIO::LoadProject(holder, load);
				for (auto & i : holder->ReturnTitles())
				{
					strcpy(add, i.c_str());
					node_editor_add(&node1, add, nk_rect(holder->GetX(i), holder->GetY(i), 180, 220), node_data(), 1, 2, node_ftables[1], true, 1);
				}
				strcpy(add, overwrite);
			}
		}
		//Creates Buttons for class control
		{
			nk_layout_row_static(ctx, 0, 100, 2);
			//Adds new class to holder
			//nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			//if (nk_button_label(ctx, "Add Class"))
			if(GUI_Textbox_Button(ctx, add, "Add Class"))
			{
				//TODO add error checking here... and for all of them after. See error handler method in REPL
				if (!(holder->CreateNewClass(add)))
				{
					node_editor_add(&node1, add, nk_rect(400, 260, 180, 220), node_data(), 1, 2, node_ftables[1], true, 1);
				}

			}
		}

		//Add method
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		GUI_menu(ctx, 2, save);
		/*
		if (nk_menu_begin_label(ctx, "Add method", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method, sizeof(method) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter Method Name"))
			{
				//TODO use MVC paradiagm instead of directly touching the model
				holder->AddMethod(classname, method, "type goes here", "private");
				//UMLMethod newMethod;
				//newMethod.SetName(method);
				//if (holder->GetUMLObject(classname)) holder->GetUMLObject(classname)->AddMethod(newMethod);
				strcpy(classname, overwrite);
			}

			nk_menu_end(ctx);
		}
		*/
		//Edit method
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Edit method", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method, sizeof(method) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter Method Name"))
			{
				strcpy(tempName, method);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, editMethod, sizeof(editMethod) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter New Method Name"))
			{
				//TODO use MVC instead
				//holder->EditMethodName(classname, tempName, editMethod);
				if (holder->GetUMLObject(classname)) holder->GetUMLObject(classname)->EditMethod(tempName, editMethod);
				strcpy(tempName, overwrite);
				strcpy(classname, overwrite);
			}

			nk_menu_end(ctx);
		}

		//Delete method
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Delete method", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method, sizeof(method) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter Method Name"))
			{
				//TODO MVC
				//holder->DeleteMethod(classname, method);
				if (holder->GetUMLObject(classname)) holder->GetUMLObject(classname)->DeleteMethod(method);
				strcpy(classname, overwrite);
			}

			nk_menu_end(ctx);
		}

		//Add field
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Add field", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter field Name"))
			{
				//TODO MVC
				holder->AddField(classname, field, "type goes here", "public");
				//UMLField newField;
				//newField.SetName(field);
				//if (holder->GetUMLObject(classname)) holder->GetUMLObject(classname)->AddField(newField);
				strcpy(classname, overwrite);
			}

			nk_menu_end(ctx);
		}

		//Edit field
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Edit field", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter Field Name"))
			{
				strcpy(tempName, field);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, editField, sizeof(editField) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter New field Name"))
			{
				//TODO MVC
				//holder->EditFieldName(classname, tempName, editField);
				if (holder->GetUMLObject(classname)) holder->GetUMLObject(classname)->EditField(tempName, editField);
				strcpy(tempName, overwrite);
				strcpy(classname, overwrite);
			}

			nk_menu_end(ctx);
		}

		//Delete field
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Delete field", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Enter Field Name"))
			{
				//TODO MVC
				//holder->DeleteField(classname, field);
				if (holder->GetUMLObject(classname)) holder->GetUMLObject(classname)->DeleteField(field);
				strcpy(classname, overwrite);
			}

			nk_menu_end(ctx);
		}
		// Add Relationship
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Add Relationship", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				holder->AddRelationship(classname, field, 0, 0, 0);
				strcpy(classname, overwrite);
			}
			nk_menu_end(ctx);
		}

		//Delete Relationship
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Delete Relationship", NK_TEXT_CENTERED, nk_vec2(200, 200)))
		{
			nk_layout_row_static(ctx, 0, 150, 1);
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				strcpy(classname, add);
			}
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
			if (nk_button_label(ctx, "Confirm Class Name"))
			{
				holder->DeleteRelationship(classname, field);
				strcpy(classname, overwrite);
			}

			nk_menu_end(ctx);
		}
		//Creates dropdown box that lists all created classes.  Updates dynamically when a class is added or deleted.			
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 405);
		if (nk_menu_begin_label(ctx, "List Classes, Fields, and Methods", NK_TEXT_CENTERED, nk_vec2(600, 200)))
		{
			nk_layout_row_dynamic(ctx, 20, 1);
			for (auto i : holder->ReturnAll())
			{
				//nk_label(ctx, i.c_str(), NK_TEXT_LEFT);
				GUI_Label(ctx, i, "left");
			}
			nk_menu_end(ctx);
		}

		//Close the ctx struct context
		nk_end(ctx);

		node_edit(ctx, &node1, "Editor 1");

		/* Draw */
		glfwGetWindowSize(win, &width, &height);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(bg.r, bg.g, bg.b, bg.a);
		/* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
		* with blending, scissor, face culling, depth test and viewport and
		* defaults everything back into a default state.
		* Make sure to either a.) save and restore or b.) reset your own state after
		* rendering the UI. */
		nk_glfw3_render(NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
		glfwSwapBuffers(win);
	}
	nk_glfw3_shutdown();
	glfwTerminate();
}

void GUI_Label(nk_context *ctx, std::string in, std::string alignment)
{
	if (alignment == "left")
	{
		nk_label(ctx, in.c_str(), NK_TEXT_LEFT);
	}
	else if (alignment == "right")
	{
		nk_label(ctx, in.c_str(), NK_TEXT_RIGHT);
	}
	else if (alignment == "center")
	{
		nk_label(ctx, in.c_str(), NK_TEXT_CENTERED);
	}
}

void GUI_Text_Box(nk_context *ctx, char * temp)
{
	nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, temp, 255, nk_filter_default);
}

int GUI_Button(nk_context *ctx, const char * name)
{
	return nk_button_label(ctx, name);
}

 int GUI_Textbox_Button(nk_context *ctx, char * temp, const char * name)
 {
	 nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, temp, 255, nk_filter_default);
	 return nk_button_label(ctx, name);
 }
 void GUI_menu(nk_context *ctx ,int buttons, char * temp)
 {
	 if (nk_menu_begin_label(ctx, "test", NK_TEXT_CENTERED, nk_vec2(200, 200)))
	 {
		 for (int i = 0; i < buttons; ++i)
		 {
			 nk_layout_row_static(ctx, 0, 150, 1);
			 GUI_Textbox_Button(ctx, temp, "Save");
		 }
		 nk_menu_end(ctx);
	 }
 }