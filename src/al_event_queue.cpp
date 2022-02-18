#include "al_event_queue.hpp"

static const bool DEBUG = true;

EventQueue::EventQueue() 
    : queue_(nullptr)
{
    if (DEBUG) printf("EventQueue::EventQueue()\n");
    queue_ = al_create_event_queue();
    if (!queue_) throw "Error: failed to create event queue.";
}

EventQueue::~EventQueue() {
    if (DEBUG) printf("EventQueue::~EventQueue()\n");
    al_destroy_event_queue(queue_);
}

void EventQueue::register_event_source(ALLEGRO_EVENT_SOURCE* source) {
    if (DEBUG) printf("EventQueue::register_event_source(ALLEGRO_EVENT_SOURCE*)\n");
    al_register_event_source(queue_, source);
}

bool EventQueue::is_empty() {
    return al_is_event_queue_empty(queue_);
}

bool EventQueue::is_source_registered(ALLEGRO_EVENT_SOURCE* source) {
    return al_is_event_source_registered(queue_, source);
}

void EventQueue::wait_for_event(ALLEGRO_EVENT* event) {
    return al_wait_for_event(queue_, event);
}