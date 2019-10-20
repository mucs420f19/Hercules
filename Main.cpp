// HerculesProject.cpp : Defines the entry point for the application.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

#include "nuklear.h"
#include "nuklear_glfw_gl3.h"
#include "SavingLoadingIO.h"
#include "UMLObject.h"
#include "UMLObjectsHolder.h"
#include "style.c"
#include "REPL.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 800

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024


static void error_callback(int e, const char* d)
{
	printf("Error %d: %s\n", e, d);
}

int main(int argc, char** argv)
{
	
	//Vars for class holders
	UMLObjectsHolder* holder = new UMLObjectsHolder();
	
	if (argc == 1)
	{
		/* Platform */
		static GLFWwindow *win;
		int width = 0, height = 0;
		struct nk_context *ctx;
		struct nk_colorf bg;
		char add[256] = {0};
		char edit[256] = {0};
		char del[256] = {0};
		char save[256] = {0};
		char load[256] = {0};
		char method[256] = {0};
		char editMethod[256] = {0};
		char field [256] = {0};
		char editField[256] = {0};
		char classname [256] = {0};
		char overwrite [256] = {0};

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
			if (nk_begin(ctx, " ", nk_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
				NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
				NK_WINDOW_TITLE))

		//Begin menubar here or core dump later on		
		nk_menubar_begin(ctx);

		//Saving and Loading buttons
		{
			nk_layout_row_static(ctx, 50, 200, 2);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, save, sizeof(save) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Save"))	
					SavingLoadingIO::SaveProjectToFile(holder, save, true);		
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, load, sizeof(load) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Load"))	
					SavingLoadingIO::LoadProject(holder, load);				
		}
		//Creates Buttons for class control
		{
			nk_layout_row_static(ctx, 0, 100, 2);
			//Adds new class to holder
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Add Class"))						
						{
							(holder->CreateNewClass(add));
						}										
			//Edits a class in the holder
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, edit, sizeof(edit) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Edit Class"))
						{
							(holder->EditClassTitle(edit, add));
						}
			//Deletes a class in the holder
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, del, sizeof(del) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Delete Class"))
						{
							(holder->DeleteUMLObject(del));
						}

		}

		//Add method
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Add method", NK_TEXT_CENTERED, nk_vec2(200, 200)))
			{
				nk_layout_row_static(ctx, 0, 150, 1);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Confirm Class Name"))	
					{						
						strcpy(classname,add);
					}
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method, sizeof(method) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter Method Name")) 
					{
						UMLMethod newMethod;
						newMethod.SetName(method);
						holder->GetUMLObject(classname)->AddMethod(newMethod);
						strcpy(classname,overwrite);
					}

				nk_menu_end(ctx);
			}

		//Edit method
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Edit method", NK_TEXT_CENTERED, nk_vec2(200, 200)))
			{
				nk_layout_row_static(ctx, 0, 150, 1);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Confirm Class Name"))	
					{						
						strcpy(classname,add);
					}
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method, sizeof(method) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter Method Name")) 
					{
						
					}
					nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, editMethod, sizeof(editMethod) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter New Method Name")) 
					{
						
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
						strcpy(classname,add);
					}
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method, sizeof(method) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter Method Name")) 
					{
						holder->GetUMLObject(classname)->DeleteMethod(method);
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
						strcpy(classname,add);
					}
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter field Name")) 
					{
						UMLField newField;
						newField.SetName(field);
						holder->GetUMLObject(classname)->AddField(newField);
						strcpy(classname,overwrite);
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
						strcpy(classname,add);
					}
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter field Name")) 
					{

					}
					nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, editField, sizeof(editField) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter New Field Name")) 
					{
						
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
						strcpy(classname,add);
					}
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter Field Name")) 
					{
						holder->GetUMLObject(classname)->DeleteField(field);
					}

				nk_menu_end(ctx);
			}

		//Creates dropdown box that lists all created classes.  Updates dynamically when a class is added or deleted.			
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 405);
		if (nk_menu_begin_label(ctx, "List Classes, Fields, and Methods", NK_TEXT_CENTERED, nk_vec2(500, 200)))
			{
				nk_layout_row_dynamic(ctx, 20, 1);
					for( auto i : holder->UMLObjectReturnTitles() )
					{
						nk_label(ctx, i, NK_TEXT_LEFT);
					}
				nk_menu_end(ctx);
			}

			//nk_label(ctx, holder->UMLObjectPrintContents(), NK_TEXT_LEFT);
			
			//Close the ctx struct context
			nk_end(ctx);

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
	else
	{
		RunREPL(holder);
	}
	return 0;
}