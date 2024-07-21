#pragma once
#include <queue>
#include "request.hpp"
#include "tile.hpp"

struct Entity : Position {
public:
    Entity() 
        : id(generate_id()), tile(nullptr)
    { }

    virtual ~Entity() { freed_ids_.push(id); }

    // The entity's identification number, they are unique; only one entity should have a
    // specific ID at any given time.
    const size_t id;
    Tile *tile;
    bool is_collider = false;
    inline static size_t count = 0;
    inline static ALLEGRO_FONT* font = nullptr; 

    operator size_t () const { return id; }

    bool operator==(size_t id) const { return this->id == id; }

    virtual void update() {}
    virtual void render(float x, float y) const {}

    void act(Request* request) {
        tile->add(request);
    }

    // Shift render position in relation to the tile its on by (x, y) pixels.
    void shift(float x, float y) { 
        rendx_ += x;
        rendy_ += y; 
    }

    // Re-adjust the render position so that it is at the center of the tile.
    void shift_reset() { 
        rendx_ = 0.0;
        rendy_ = 0.0; 
    }

protected:
    // Positioninate describing the entities position in relation to the center of the tile its on.
    float rendx_ = 0.0, rendy_ = 0.0;

private:
    static inline size_t next_id_ = 0;
    static inline std::queue<size_t> freed_ids_;

    size_t generate_id() {
        if (freed_ids_.empty()) {
            return next_id_++;
        }

        int result = freed_ids_.front();
        freed_ids_.pop();
        return result;
    }

};