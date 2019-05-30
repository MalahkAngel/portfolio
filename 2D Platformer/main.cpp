#include "globals.h"
#include "inputhandler.h"
#include "player.h"
#include "maphandler.h"

void forceInit(bool input, std::string name);

int main(int argc, char** argv)
{
	// system variables
	srand(time(NULL));							// seed random number generation
	bool quit = false;							// false until player quits manually
	bool redraw = true;							// true when screen needs to update
	int loadMask = 0;							// frame counter for transitional blackout
	bool loadStates[NUM_LOAD_STATES] = { 0 };	// loading flags
	bool gameStates[NUM_GAME_STATES] = { 0 };	// game state flags

	// Allegro 5 initialization
	forceInit(al_init(), "al_init()");
	forceInit(al_init_native_dialog_addon(), "al_init_native_dialog_addon()");
	forceInit(al_init_primitives_addon(), "al_init_primitives_addon()");
	forceInit(al_init_image_addon(), "al_init_image_addon()");
	forceInit(al_init_font_addon(), "al_init_font_addon()");
	forceInit(al_init_ttf_addon(), "al_init_ttf_addon()");
	forceInit(al_install_audio(), "al_install_audio()");
	forceInit(al_install_keyboard(), "al_install_keyboard()");
	forceInit(al_install_joystick(), "al_install_joystick()");

	// initialize Allegro objects
	ALLEGRO_DISPLAY* display = al_create_display(WINDOW_W, WINDOW_H);
	forceInit(display, "al_create_display()");
	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
	forceInit(queue, "al_create_event_queue()");
	ALLEGRO_TIMER* timer = al_create_timer(1.0 / 60.0);
	forceInit(timer, "al_create_timer");
	ALLEGRO_JOYSTICK* joystick = NULL;

	// check for external controller
	if (al_get_num_joysticks() != 0)
	{
		joystick = al_get_joystick(0);
		forceInit(joystick, "al_get_joystick()");
	}

	// register interrupt sources
	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_joystick_event_source());
	ALLEGRO_EVENT event;

	// prepare engine objects
	InputHandler input;
	Player player(32.0, 176.0);
	MapHandler map;
	// prepare game loop
	gameStates[G_FIELD] = true;

	// initialize screen transformation
	float xTrans = WINDOW_W / (float)SCREEN_W;
	float yTrans = WINDOW_H / (float)SCREEN_H;
	ALLEGRO_TRANSFORM trans;
	al_identity_transform(&trans);
	al_scale_transform(&trans, xTrans, yTrans);
	al_use_transform(&trans);
	
	for (int i = 0; i < NUM_MAPS; i++)
	{
		map.loadMapData(i);
	}

	map.loadNewMap();
	al_start_timer(timer);							// start game loop

	while (!quit)
	{
		al_wait_for_event(queue, &event);				// poll for interrupts
		
		switch (event.type)						// process interrupts
		{
		case ALLEGRO_EVENT_TIMER:				// timer has incremented
			if (gameStates[G_FIELD])
			{
				player.action(input, map);
				map.moveCamera(player.getPosition());
				map.updateMap();
			}

			input.releaseFieldInput(event);
			input.releaseMenuInput(event);
			redraw = true;
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			if (gameStates[G_FIELD])
			{
				if (!joystick)
				{
					input.setFieldKeysDown(event);
					input.pressFieldKeys(event);
				}
			}
			else if (gameStates[G_MENU]) if (!joystick) input.pressMenuKeys(event);
			break;
		case ALLEGRO_EVENT_KEY_UP:
			if (gameStates[G_FIELD]) if (!joystick) input.setFieldKeysUp(event);
			break;
		case ALLEGRO_EVENT_JOYSTICK_AXIS:
			if (gameStates[G_FIELD]) if (joystick) input.setFieldAxes(event);
			else if (gameStates[G_MENU]) if (joystick) input.pressMenuAxes(event);
			break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
			if (gameStates[G_FIELD])
			{
				if (joystick)
				{
					input.setFieldButtonsDown(event);
					input.pressFieldButtons(event);
				}
			}
			else if (gameStates[G_MENU]) if (joystick) input.pressMenuButtons(event);
			break;
		case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
			if(gameStates[G_FIELD]) if (joystick) input.setFieldButtonsUp(event);
			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			quit = true;
			break;
		}

		if (redraw && al_event_queue_is_empty(queue))
		{
			redraw = false;
			al_clear_to_color(al_map_rgb(0, 0, 0));		// clear screen for updating

			if (gameStates[G_FIELD])
			{
				map.drawMap();
				player.update(map);
			}

			al_flip_display();
		}
	}

	player.destroyPointers();
	map.destroyTextures();
	al_destroy_event_queue(queue);
	al_destroy_timer(timer);
	al_destroy_display(display);

	return 0;
}

void forceInit(bool input, std::string name)
{
	std::string message = "Allegro 5 function --" + name + "-- has failed.";

	if (!input)
	{
		al_show_native_message_box(al_get_current_display(), "Allegro 5 Error",
			"Initialization Falure", message.c_str(), NULL, ALLEGRO_MESSAGEBOX_ERROR);
		exit(-1);
	}
}