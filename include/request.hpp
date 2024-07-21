#pragma once
#include "entity.hpp"

struct Request {
    virtual void run(Tile* source) = 0;
};

struct Move : Request {
public:
    Move(size_t id, Direction dir)
        : id_(id), frame_(0), direction_(dir), entity_()
    {}

    void run(Tile* source) override {
        auto tile = std::make_shared<Tile>(source);

        if (!tile || !tile->has(id_))
            return;

        if (frame_ == 0)
            entity_ = tile->get(id_);
        frame_++;

        auto e = entity_.lock();
        bool move_complete = false;

        switch (frame_) {
        case 1:
            e->shift( 0.25 * (direction_.east - direction_.west),
                0.25 * (direction_.north - direction_.south) );
            break;
        case 2:
            if (e->is_collider && tile->has_collider) {
                e->shift_reset();
                move_complete = true;
            } else {
                e->shift( 0.25 * (direction_.east - direction_.west),
                    0.25 * (direction_.north - direction_.south) );
            }
            break;
        case 3:
            if (tile && direction_.up) tile = tile->up;
            if (tile && direction_.down) tile = tile->down;
            if (tile && direction_.north) tile = tile->north;
            if (tile && direction_.south) tile = tile->south;
            if (tile && direction_.east) tile = tile->east;
            if (tile && direction_.west) tile = tile->west;
            if (!tile || tile.get() == source) return;
            source->remove(id_);
            tile->add(e.get());
            e->shift( -0.25 * (direction_.east - direction_.west),
                -0.25 * (direction_.north - direction_.south) );
            break;
        case 4:
        default:
            e->shift_reset();
            move_complete = true;
            break;
        }

        if (!move_complete) {
            tile->add(new Move(*this));
        }
    }

private:
    const size_t id_;
    unsigned short frame_;
    Direction direction_;
    std::weak_ptr<Entity> entity_;

    Move(const Move& other)
        : id_(other.id_), frame_(other.frame_),
        direction_(direction_), entity_(other.entity_)
    {}
};