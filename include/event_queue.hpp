#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_EVENT_QUEUE
struct EventQueue {
    // Assumes that the Allegro core library was already initialized.
    EventQueue();
    ~EventQueue();

    void register_event_source(ALLEGRO_EVENT_SOURCE*);
    void register_event_source(ALLEGRO_DISPLAY*);
    void EventQueue::register_event_source(ALLEGRO_TIMER*);

    // implicit type conversion
    operator ALLEGRO_EVENT_QUEUE*()
    { return event_queue_; }
private:
    ALLEGRO_EVENT_QUEUE* event_queue_;
};
