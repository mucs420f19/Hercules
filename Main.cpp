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
	bool run = true;
	int choice;
	std::string input, input2;
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
		std::string method;
		char field [256] = {0};
		static int show_menu = nk_true;
		static int show_app_about = nk_false;

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
			if (nk_begin(ctx, "TODO SAVE FILE NAME HERE", nk_rect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT),
				NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
				NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))

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
						(holder->CreateNewClass(add));												
			//Edits a class in the holder
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, edit, sizeof(edit) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Edit Class"))
						printf("%s\n", edit);
			//Deletes a class in the holder
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, del, sizeof(del) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Delete Class"))
						(holder->DeleteUMLObject(del));

		}

		
			nk_layout_row_static(ctx, 0, 100, 2);

			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method, sizeof(method) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Add Method"))		
					printf("test");									
			nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, field, sizeof(field) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Add Field"))						
						printf("test");

		
		//Creates dropdown box that lists all created classes.  Updates dynamically when a class is added or deleted.			
		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "List Classes, Fields, and Methods", NK_TEXT_LEFT, nk_vec2(500, 200)))
			{
				nk_layout_row_dynamic(ctx, 20, 1);
					for( auto i : holder->UMLObjectReturnTitles() )
					{
						nk_label(ctx, i, NK_TEXT_LEFT);
					}
				nk_menu_end(ctx);
			}

		nk_layout_row_begin(ctx, NK_STATIC, 25, 5);
		nk_layout_row_push(ctx, 200);
		if (nk_menu_begin_label(ctx, "Add method", NK_TEXT_LEFT, nk_vec2(500, 200)))
			{
				nk_layout_row_static(ctx, 0, 100, 2);
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, add, sizeof(add) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Confirm Class Name"))	
						printf("te");
				nk_edit_string_zero_terminated(ctx, NK_EDIT_FIELD, method.c_str(), sizeof(method) - 1, nk_filter_default);
					if (nk_button_label(ctx, "Enter Method Name"))
						printf("Method Name");

					UMLMethod newMethod;
					newMethod.SetName(method);

					holder->GetUMLObject(add)->AddMethod(method);

				nk_menu_end(ctx);
			}
		
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



	UMLObjectsHolder* holder = new UMLObjectsHolder();

	bool run = true;
	int choice;
	std::string input, input2;
}
	else
	{
		std::cout << std::endl << "********************Welcome to Hercules********************" << std::endl;

		while (run)
		{
			std::cout << std::endl << "********************" << std::endl;
			std::cout << "1. View Class List" << std::endl;
			std::cout << "2. Create New Class" << std::endl;
			std::cout << "3. Delete A Class" << std::endl;
			std::cout << "4. Edit A Class" << std::endl;
			std::cout << "5. Save" << std::endl;
			std::cout << "6. Load" << std::endl;
			std::cout << "7. Exit" << std::endl;
			std::cout << "********************" << std::endl << std::endl;
			std::cout << "Which task would you like to run?" << std::endl;

			std::cin >> choice;

			switch (choice)
			{
			case 1:
			{
				std::cout << std::endl << "Class List:" << std::endl;

				holder->UMLObjectPrintContents();

				break;
			}

			case 2:
			{
				std::cout << std::endl << "Please enter the name of the new class." << std::endl;
				std::cin >> input;
				std::cout << std::endl;

				if (holder->CreateNewClass(input))
					std::cout << "Class created sucessfully." << std::endl;
				else
					std::cout << "Class creation failed." << std::endl;

				break;
			}

			case 3:
			{
				if (holder->Size())
				{
					std::cout << std::endl;

					holder->UMLObjectPrintTitles();

					std::cout << std::endl << "Please enter the number of the class you wish to delete." << std::endl;
					std::cin >> input;

					if (holder->DeleteUMLObject(input))
						std::cout << "Delete successful." << std::endl << std::endl;
					else
						std::cout << "Unable to delete class." << std::endl << std::endl;
				}
				else
					std::cout << std::endl << "You have no classes to delete." << std::endl;

				break;
			}

			case 4:
			{
				std::cout << std::endl << "Please enter the name of the class you wish to edit." << std::endl;

				std::cin >> input;

				std::cout << std::endl << "Please enter the new name for the class." << std::endl;

				std::cin >> input2;

				if (holder->EditClassTitle(input2, input))
					std::cout << "Rename successful." << std::endl << std::endl;
				else
					std::cout << "Unable to rename class." << std::endl << std::endl;

				break;
			}

			case 5:
			{
				std::cout << std::endl << "Please enter the name of the save file." << std::endl;

				std::cin >> input;

				if (SavingLoadingIO::SaveProjectToFile(holder, input) == SaveAlreadyExists)
				{
					std::cout << std::endl << "Save already exists. Overwrite? y/n: " << std::endl;
					std::cin >> input;
					if (input == "y")
					{
						SavingLoadingIO::SaveProjectToFile(holder, input, true); //for force overwrite
					}
					else
					{
						std::cout << std::endl << "Save cancelled" << std::endl;
					}
				}

				break;
			}

			case 6:
			{
				std::cout << std::endl << "Please enter the name of the file you wish to load." << std::endl;

				std::cin >> input;

				//add something in here to ask if they want to save the current project... otherwise it gets thrown out
				if (SavingLoadingIO::LoadProject(holder, input))
					std::cout << "Load successful." << std::endl << std::endl;
				else
					std::cout << "Unable to load." << std::endl << std::endl;

				break;
			}

			case 7:
			{
				run = false;

				std::cout << std::endl << "********************" << std::endl;
				std::cout << "Thank you for using Hercules!" << std::endl;
				std::cout << "********************" << std::endl << std::endl;

				break;
			}
			case 8:
			{
				std::cout << std::endl << "Please enter the name of the class you wish to edit." << std::endl;

				std::cin >> input;

				std::cout << std::endl << "Please enter the method name." << std::endl;

				std::cin >> input2;

					UMLMethod newMethod;
					newMethod.SetName(input2);

					holder->GetUMLObject(input)->AddMethod(newMethod);

				break;
			}
			case 9:
			{
				std::cout << std::endl << "Please enter the name of the class you wish to edit." << std::endl;

				std::cin >> input;

				std::cout << std::endl << "Please enter the field name." << std::endl;

				std::cin >> input2;

					UMLField newField;
					newField.SetName(input2);

					holder->GetUMLObject(input)->AddField(newField);

				break;
			}

			default:
			{
				std::cout << std::endl << "Invalid entry, please enter a number from 1 to 8." << std::endl << std::endl;
			}
			}
		}
	}
	return 0;
}