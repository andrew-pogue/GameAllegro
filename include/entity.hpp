#pragma once
#include <queue>
#include "request.hpp"
#include "tile.hpp"

struct Entity {
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

    operator size_t () const { return id; }

    bool operator==(size_t id) const { return this->id == id; }

    virtual void update() {}
    virtual void render(float x, float y) const {}

    // Support for commands:
    virtual void move(const Direction& direction) const
    { tile->enqueue(new Move(id, direction)); }

    void shift(float x, float y) { 
        x_ += x;
        y_ += y; 
    }

    void shift_reset() { 
        x_ = 0.0;
        y_ = 0.0; 
    }

protected:
    // Coordinate describing the entities position in relation to the center of the tile its on.
    float x_ = 0.0, y_ = 0.0;

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

void move(Entity *e, const Direction& dir) {
    
    e->tile->enqueue(new Move(e->id, dir));
    
}