#include "alcpp_event_queue.hpp"

static const bool DEBUG = true;

EventQueue::EventQueue() 
    : event_queue_(nullptr)
{
    if (DEBUG) printf("EventQueue::EventQueue()\n");
    event_queue_ = al_create_event_queue();
    if (!event_queue_) throw "Error: failed to create event queue.";
}

EventQueue::~EventQueue() {
    if (DEBUG) printf("EventQueue::~EventQueue()\n");
    al_destroy_event_queue(event_queue_);
}

void EventQueue::register_event_source(ALLEGRO_EVENT_SOURCE* source) {
    if (DEBUG) printf("EventQueue::register_event_source(ALLEGRO_EVENT_SOURCE*)\n");
    al_register_event_source(event_queue_, source);
}

void EventQueue::register_event_source(ALLEGRO_DISPLAY* display) {
    if (DEBUG) printf("EventQueue::register_event_source(ALLEGRO_DISPLAY*)\n");
    al_register_event_source(event_queue_, al_get_display_event_source(display));
}

void EventQueue::register_event_source(ALLEGRO_TIMER* timer) {
    if (DEBUG) printf("EventQueue::register_event_source(ALLEGRO_TIMER*)\n");
    al_register_event_source(event_queue_, al_get_timer_event_source(timer));
}
