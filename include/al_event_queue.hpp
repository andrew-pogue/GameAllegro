#pragma once
#include <stdio.h>
#include <allegro5/allegro.h>

// Wrapper for ALLEGRO_EVENT_QUEUE
struct EventQueue {
    EventQueue();
    ~EventQueue();

    void register_event_source(ALLEGRO_EVENT_SOURCE*);

    bool is_empty();
    bool is_source_registered(ALLEGRO_EVENT_SOURCE*);

    void wait_for_event(ALLEGRO_EVENT*);

    // implicit type conversion
    operator ALLEGRO_EVENT_QUEUE* ()
    { return queue_; }
private:
    ALLEGRO_EVENT_QUEUE* queue_;
};
