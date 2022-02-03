#include "event_queue.hpp"

static const bool DEBUG = false;

EventQueue::EventQueue() {
    if (DEBUG) printf("EventQueue::EventQueue()");
    event_queue_ = al_create_event_queue();
    if (!event_queue_) throw "Error: failed to create event queue.";
}

EventQueue::~EventQueue() {
    if (DEBUG) printf("EventQueue::~EventQueue()");
    al_destroy_event_queue(event_queue_);
}

void EventQueue::register_event_source(ALLEGRO_EVENT_SOURCE* source) {
    al_register_event_source(event_queue_, source);
}

void EventQueue::register_event_source(ALLEGRO_DISPLAY* display) {
    al_register_event_source(event_queue_, al_get_display_event_source(display));
}

void EventQueue::register_event_source(ALLEGRO_TIMER* timer) {
    al_register_event_source(event_queue_, al_get_timer_event_source(timer));
}
