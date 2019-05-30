#pragma once

#include "globals.h"

class InputHandler
{
	private:
		bool fieldInput[NUM_FIELD_BUTTONS] = { 0 };
		bool menuInput[NUM_MENU_BUTTONS] = { 0 };
	public:
		InputHandler();
		~InputHandler();

		// field input management
		void setFieldKeysDown(ALLEGRO_EVENT event);
		void setFieldButtonsDown(ALLEGRO_EVENT event);
		void setFieldKeysUp(ALLEGRO_EVENT event);
		void setFieldButtonsUp(ALLEGRO_EVENT event);
		void setFieldAxes(ALLEGRO_EVENT event);
		void pressFieldKeys(ALLEGRO_EVENT event);
		void pressFieldButtons(ALLEGRO_EVENT event);
		void releaseFieldInput(ALLEGRO_EVENT event);

		// menu input management
		void pressMenuKeys(ALLEGRO_EVENT event);
		void pressMenuButtons(ALLEGRO_EVENT event);
		void pressMenuAxes(ALLEGRO_EVENT event);
		void releaseMenuInput(ALLEGRO_EVENT event);

		// input accessors
		bool getFieldInput(int index) { return fieldInput[index]; }
		bool getMenuInput(int index) { return menuInput[index]; }
};

