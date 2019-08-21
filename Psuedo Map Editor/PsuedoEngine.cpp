#include "PsuedoEngine.h"

PsuedoEngine::PsuedoEngine()
{
	display.window = NULL;

	flow.queue = NULL;
	flow.timer = NULL;
	flow.quit = false;
	flow.update = false;

	appState = STATE_TYPEEDIT;
}

PsuedoEngine::~PsuedoEngine()
{
	al_destroy_display(display.window);
	al_destroy_event_queue(flow.queue);
	al_destroy_timer(flow.timer);
}

void PsuedoEngine::initAllegro()
{
	init(al_init(), "Allegro 5 initialization failed.");
	init(al_init_native_dialog_addon(), "Native Dialog initialization failed.");
	init(al_init_primitives_addon(), "Primitive Drawing initialization failed.");
	init(al_init_font_addon(), "Bitmap Font Support initialization failed.");
	init(al_init_ttf_addon(), "True-Type Font Support initialization failed.");
	init(al_install_mouse(), "Mouse initialization failed.");
	init(editor.loadFonts(), "Font loading failed.");
}

void PsuedoEngine::createDisplay()
{
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);
	display.window = al_create_display(WINDOW_W, WINDOW_H);
}

void PsuedoEngine::createGameFlow()
{
	flow.queue = al_create_event_queue();
	flow.timer = al_create_timer(FPS);
	al_register_event_source(flow.queue, al_get_display_event_source(display.window));
	al_register_event_source(flow.queue, al_get_timer_event_source(flow.timer));
	al_register_event_source(flow.queue, al_get_mouse_event_source());
	al_start_timer(flow.timer);
}

bool PsuedoEngine::processEvents()
{
	ALLEGRO_EVENT ev;
	al_wait_for_event(flow.queue, &ev);

	switch (ev.type)
	{
	case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
		appState = editor.updateScreen(appState, ev, display.window);
		break;
	case ALLEGRO_EVENT_DISPLAY_CLOSE:
		flow.quit = true;
		break;
	case ALLEGRO_EVENT_TIMER:
		flow.update = true;
		break;
	}

	return flow.quit;
}

void PsuedoEngine::updateScreen()
{
	flow.update = false;
	al_clear_to_color(al_map_rgb(0, 0, 0));

	editor.drawScreen(appState);

	al_flip_display();
}
