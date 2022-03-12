#pragma once
#include "entity.hpp"

struct Request {
    void run(Tile* tile) { run(std::make_shared<Tile>(tile)); }
    virtual void run(std::shared_ptr<Tile> source) = 0;
};

struct MoveRequest : Request {
    const size_t id;
    const Direction direction;

    MoveRequest(size_t id, Direction dir)
        : id(id), direction(dir), entity_()
    {}

    MoveRequest(const MoveRequest& other)
        : id(other.id), direction(other.direction), frame_(other.frame_), entity_(other.entity_)
    {}

    void run(std::shared_ptr<Tile> source) override {
        auto tile = source;
        if (!tile) return;
        if (!tile->has(id)) return;
        if (frame_ == 0) {
            entity_ = tile->get(id);
        }
        
        frame_++;
        bool move_complete = false;
        const Direction &dir = direction;
        auto e = entity_.lock();
        
        switch (frame_) {
        case 1:
            e->shift( 0.25 * (dir.east - dir.west),
                0.25 * (dir.north - dir.south) );
            break;
        case 2:
            if (e->is_collider && tile->has_collider) {
                e->shift_reset();
                move_complete = true;
            } else {
                e->shift( 0.25 * (dir.east - dir.west), 0.25 * (dir.north - dir.south) );
            }
            break;
        case 3:
            if (tile && dir.up) tile = tile->up;
            if (tile && dir.down) tile = tile->down;
            if (tile && dir.north) tile = tile->north;
            if (tile && dir.south) tile = tile->south;
            if (tile && dir.east) tile = tile->east;
            if (tile && dir.west) tile = tile->west;
            if (!tile || tile == source) return;
            source->remove(id);
            tile->add(e.get());
            e->shift( -0.25 * (dir.east - dir.west), -0.25 * (dir.north - dir.south) );
            break;
        case 4:
        default:
            e->shift_reset();
            move_complete = true;
            break;
        }

        if (!move_complete) {
            tile->enqueue(new MoveRequest(*this));
        }
    }

private:
    unsigned short frame_ = 0;
    std::weak_ptr<Entity> entity_;
};