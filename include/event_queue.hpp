#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_EVENT_QUEUE
struct EventQueue {
    EventQueue::EventQueue() : queue_(nullptr) {
        queue_ = al_create_event_queue();
        if (!queue_) throw "Error: failed to create event queue.";
    }

    EventQueue::~EventQueue() {
        al_destroy_event_queue(queue_);
    }

    void EventQueue::register_source(ALLEGRO_EVENT_SOURCE* source) {
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

    // implicit type conversion
    operator ALLEGRO_EVENT_QUEUE* ()
    { return queue_; }
private:
    ALLEGRO_EVENT_QUEUE* queue_;
};
