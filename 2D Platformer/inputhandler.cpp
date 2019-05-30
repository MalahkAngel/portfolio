#include "inputhandler.h"

InputHandler::InputHandler() {}
InputHandler::~InputHandler() {}

// field input processing
void InputHandler::setFieldKeysDown(ALLEGRO_EVENT event)		// keys held down
{
	switch (event.keyboard.keycode)
	{
	case ALLEGRO_KEY_LEFT:
		fieldInput[FB_LEFT] = true;
		break;
	case ALLEGRO_KEY_RIGHT:
		fieldInput[FB_RIGHT] = true;
		break;
	case ALLEGRO_KEY_UP:
		fieldInput[FB_UP] = true;
		break;
	case ALLEGRO_KEY_DOWN:
		fieldInput[FB_DOWN] = true;
		break;
	case ALLEGRO_KEY_Z:
		fieldInput[FB_JUMP] = true;
		break;
	case ALLEGRO_KEY_SPACE:
		fieldInput[FB_BOOST] = true;
		break;
	case ALLEGRO_KEY_RSHIFT:
		fieldInput[FB_IMBUE] = true;
		break;
	case ALLEGRO_KEY_ALT:
		fieldInput[FB_MAGIC] = true;
		break;
	}
}

void InputHandler::setFieldButtonsDown(ALLEGRO_EVENT event)		// buttons held down
{
	switch (event.joystick.button)
	{
	case DS4_CROSS:
		fieldInput[FB_JUMP] = true;
		break;
	case DS4_L1:
		fieldInput[FB_IMBUE] = true;
		break;
	case DS4_L2:
		fieldInput[FB_MAGIC] = true;
		break;
	case DS4_R2:
		fieldInput[FB_BOOST] = true;
		break;
	}
}

void InputHandler::setFieldKeysUp(ALLEGRO_EVENT event)			// held keys released
{
	switch (event.keyboard.keycode)
	{
	case ALLEGRO_KEY_LEFT:
		fieldInput[FB_LEFT] = false;
		break;
	case ALLEGRO_KEY_RIGHT:
		fieldInput[FB_RIGHT] = false;
		break;
	case ALLEGRO_KEY_UP:
		fieldInput[FB_UP] = false;
		break;
	case ALLEGRO_KEY_DOWN:
		fieldInput[FB_DOWN] = false;
		break;
	case ALLEGRO_KEY_Z:
		fieldInput[FB_JUMP] = false;
		break;
	case ALLEGRO_KEY_SPACE:
		fieldInput[FB_BOOST] = false;
		break;
	case ALLEGRO_KEY_RSHIFT:
		fieldInput[FB_IMBUE] = false;
		break;
	case ALLEGRO_KEY_ALT:
		fieldInput[FB_MAGIC] = false;
		break;
	}
}

void InputHandler::setFieldButtonsUp(ALLEGRO_EVENT event)		// held buttons released
{
	switch (event.joystick.button)
	{
	case DS4_CROSS:
		fieldInput[FB_JUMP] = false;
		break;
	case DS4_L1:
		fieldInput[FB_IMBUE] = false;
		break;
	case DS4_L2:
		fieldInput[FB_MAGIC] = false;
		break;
	case DS4_R2:
		fieldInput[FB_BOOST] = false;
		break;
	}
}

void InputHandler::setFieldAxes(ALLEGRO_EVENT event)
{
	switch (event.joystick.stick)
	{
	case DS4_STICKS:
		if (event.joystick.axis == 0)
		{
			if (event.joystick.pos < 0)
			{
				fieldInput[FB_LEFT] = true;
				fieldInput[FB_RIGHT] = false;
			}
			else if (event.joystick.pos == 0)
			{
				fieldInput[FB_LEFT] = false;
				fieldInput[FB_RIGHT] = false;
			}
			else if (event.joystick.pos > 0)
			{
				fieldInput[FB_LEFT] = false;
				fieldInput[FB_RIGHT] = true;
			}
		}
		else if (event.joystick.axis == 1)
		{
			if (event.joystick.pos < 0)
			{
				fieldInput[FB_UP] = true;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos == 0)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos > 0)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = true;
			}
		}

		break;
	case DS4_DPAD:
		if (event.joystick.axis == 0)
		{
			if (event.joystick.pos == -1)
			{
				fieldInput[FB_LEFT] = true;
				fieldInput[FB_RIGHT] = false;
			}
			else if (event.joystick.pos == 0)
			{
				fieldInput[FB_LEFT] = false;
				fieldInput[FB_RIGHT] = false;
			}
			else if (event.joystick.pos == 1)
			{
				fieldInput[FB_LEFT] = false;
				fieldInput[FB_RIGHT] = true;
			}
		}
		else if (event.joystick.axis == 1)
		{
			if (event.joystick.pos == -1)
			{
				fieldInput[FB_UP] = true;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos == 0)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos == 1)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = true;
			}
		}

		break;
	}
}

void InputHandler::pressFieldKeys(ALLEGRO_EVENT event)			// single press keys
{
	switch (event.keyboard.keycode)
	{
	case ALLEGRO_KEY_X:
		if(!fieldInput[FB_M_ATK]) fieldInput[FB_M_ATK] = true;
		break;
	case ALLEGRO_KEY_A:
		if (!fieldInput[FB_SHOOT]) fieldInput[FB_SHOOT] = true;
		break;
	case ALLEGRO_KEY_LSHIFT:
		if (!fieldInput[FB_EVADE]) fieldInput[FB_EVADE] = true;
		break;
	case ALLEGRO_KEY_1:
		if (!fieldInput[FB_ITEM]) fieldInput[FB_ITEM] = true;
		break;
	case ALLEGRO_KEY_RSHIFT:
		if (!fieldInput[FB_MAP]) fieldInput[FB_MAP] = true;
		break;
	case ALLEGRO_KEY_TAB:
		if (!fieldInput[FB_MENU]) fieldInput[FB_MENU] = true;
		break;
	}
}

void InputHandler::pressFieldButtons(ALLEGRO_EVENT event)		// single press buttons
{
	switch (event.joystick.button)
	{
	case DS4_SQUARE:
		if (!fieldInput[FB_M_ATK]) fieldInput[FB_M_ATK] = true;
		break;
	case DS4_TRIANGLE:
		if (!fieldInput[FB_SHOOT]) fieldInput[FB_SHOOT] = true;
		break;
	case DS4_CIRCLE:
		if (!fieldInput[FB_EVADE]) fieldInput[FB_EVADE] = true;
		break;
	case DS4_R1:
		if (!fieldInput[FB_ITEM]) fieldInput[FB_ITEM] = true;
		break;
	case DS4_OPTIONS:
		if (!fieldInput[FB_MAP]) fieldInput[FB_MAP] = true;
		break;
	case DS4_TOUCH:
		if (!fieldInput[FB_MENU]) fieldInput[FB_MENU] = true;
		break;
	}
}

void InputHandler::releaseFieldInput(ALLEGRO_EVENT event)		// release all single press buttons
{
	if (fieldInput[FB_M_ATK]) fieldInput[FB_M_ATK] = false;
	if (fieldInput[FB_SHOOT]) fieldInput[FB_SHOOT] = false;
	if (fieldInput[FB_EVADE]) fieldInput[FB_EVADE] = false;
	if (fieldInput[FB_ITEM]) fieldInput[FB_ITEM] = false;
	if (fieldInput[FB_MAP]) fieldInput[FB_MAP] = false;
	if (fieldInput[FB_MENU]) fieldInput[FB_MENU] = false;

}

// menu input processing
void InputHandler::pressMenuKeys(ALLEGRO_EVENT event)			// single press keys
{
	switch (event.keyboard.keycode)
	{
	case ALLEGRO_KEY_UP:
		if (!menuInput[MB_UP]) menuInput[MB_UP] = true;
		break;
	case ALLEGRO_KEY_DOWN:
		if (!menuInput[MB_DOWN]) menuInput[MB_DOWN] = true;
		break;
	case ALLEGRO_KEY_ENTER:
		if (!menuInput[MB_CONFIRM]) menuInput[MB_CONFIRM] = true;
		break;
	case ALLEGRO_KEY_ESCAPE:
		if (!menuInput[MB_UP]) menuInput[MB_UP] = true;
		break;
	}
}

void InputHandler::pressMenuButtons(ALLEGRO_EVENT event)		// single press buttons
{
	switch (event.keyboard.keycode)
	{
	case DS4_CROSS:
		if (!menuInput[MB_CONFIRM]) menuInput[MB_CONFIRM] = true;
		break;
	case DS4_CIRCLE:
		if (!menuInput[MB_UP]) menuInput[MB_UP] = true;
		break;
	}
}

void InputHandler::pressMenuAxes(ALLEGRO_EVENT event)
{
	switch (event.joystick.stick)
	{
	case DS4_STICKS:
		if (event.joystick.axis == 1)
		{
			if (event.joystick.pos == -1)
			{
				fieldInput[FB_UP] = true;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos == 0)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos == 1)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = true;
			}
		}

		break;
	case DS4_DPAD:
		if (event.joystick.axis == 1)
		{
			if (event.joystick.pos == -1)
			{
				fieldInput[FB_UP] = true;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos == 0)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = false;
			}
			else if (event.joystick.pos == 1)
			{
				fieldInput[FB_UP] = false;
				fieldInput[FB_DOWN] = true;
			}
		}

		break;
	}
}

void InputHandler::releaseMenuInput(ALLEGRO_EVENT event)		// release all single press buttons
{
	if (menuInput[MB_UP]) menuInput[MB_UP] = false;
	if (menuInput[MB_DOWN]) menuInput[MB_DOWN] = false;
	if (menuInput[MB_CONFIRM]) menuInput[MB_CONFIRM] = false;
	if (menuInput[MB_CANCEL]) menuInput[MB_CANCEL] = false;
}