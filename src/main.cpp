#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

ALLEGRO_FONT* g_font = NULL;
ALLEGRO_DISPLAY* g_display = NULL;
ALLEGRO_EVENT_QUEUE* g_event_queue = NULL;
ALLEGRO_TIMER* g_frame_timer = NULL;

bool init() {
    if (!al_init()) {
        std::cout << "Error: Couldn't initialize Allegro.\n";
        return false;
    }

    if (!al_init_font_addon()) { 
        std::cout << "Error: Couldn't initialize Allegro font addon.\n";
        return false; 
    }

    if (!al_install_keyboard()) { 
        printf("Error: Couldn't initialize Allegro keyboard addon.\n"); 
        return false; 
    }

    g_font = al_create_builtin_font();
    if (!g_font) {
        printf("Error: Couldn't create font.\n"); 
        return false;
    }

    g_display = al_create_display(640, 480);
    if (!g_display) {
        printf("Error: Couldn't create display.\n");
        return false;
    }

    g_event_queue = al_create_event_queue();
    if (!g_event_queue) {
        printf("Error: Couldn't create event queue.\n"); 
        return false;
    }

    g_frame_timer = al_create_timer(1.0 / 30.0);
    if (!g_frame_timer) {
        printf("Error: Couldn't create timer.\n"); 
        return false;
    }

    al_register_event_source(g_event_queue, al_get_keyboard_event_source());
    al_register_event_source(g_event_queue, al_get_display_event_source(g_display));
    al_register_event_source(g_event_queue, al_get_timer_event_source(g_frame_timer));

    return true;
}

int main (int argc, char **argv) {
    if (!init()) {
        printf("Press any key to continue...\n");
        getchar();
        return 1;
    }

    bool play = true, redraw = true;
    ALLEGRO_EVENT event;
    al_start_timer(g_frame_timer);
    while (play) {
        al_wait_for_event(g_event_queue, &event);
        switch (event.type) {
        case ALLEGRO_EVENT_TIMER:
            redraw = true;
            break;
        case ALLEGRO_EVENT_KEY_DOWN:
        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            play = false;
            break;
        }

        if (redraw && al_is_event_queue_empty(g_event_queue)) {
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_text(g_font, al_map_rgb(255, 255, 255), 320, 240, 0, "Hello world!");
            al_flip_display();
            redraw = false;
        }
    }

    al_destroy_font(g_font);
    al_destroy_timer(g_frame_timer);
    al_destroy_event_queue(g_event_queue);
    al_destroy_display(g_display);

    return 0;
}