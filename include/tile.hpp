#pragma once
#include <memory>
#include <stdexcept>
#include <unordered_map>
#include <queue>
#include "entity.hpp"
#include "position.hpp"

// An entity that manages other entities?
struct Tile : Position {
    Tile(int x, int y, int z)
        : Position({x, y, z})
    {}

    Tile(const Position& pos)
        : Position(pos)
    {}

    ~Tile() {}

    std::shared_ptr<Tile> 
        up, down,
        north, south,
        east, west;
    bool has_collider = false;
    static inline float size = 20.0;

    void update() {
        while (!request_queue_.empty()) {
            request_queue_.top()->run(this);
            request_queue_.pop();
        }

        for (auto pair : entity_map_)
            pair.second->update();
    }

    // Parameters x and y are the tile's location on the display.
    void render(const float x, const float y) const {
        for (auto pair : entity_map_) 
            pair.second->render(x, y);
    }

    void remove(size_t id) {
        auto it = entity_map_.find(id);
        if (it == entity_map_.end()) return;
        it->second->tile = nullptr;
        entity_map_.erase(it);
    }

    void add(Entity *entity) {
        if (!entity) return;
        entity->tile = this;
        entity_map_[entity->id] = std::make_shared<Entity>(entity);
    }

    std::shared_ptr<Entity> get(size_t id) {
        return entity_map_.at(id);
    }

    bool has(size_t id) {
        return entity_map_.count(id);
    }

    void add(Request* request) {
        if (!request) return;
        request_queue_.push(std::make_shared<Request>(request));
    }

private:
    std::unordered_map<size_t, std::shared_ptr<Entity>> entity_map_;
    std::priority_queue<std::shared_ptr<Request>> request_queue_;
};

/** Worst-case time complexity for acessing a tile:
 * O(c) + O(e) where
 *  c is the number of chunks loaded
 *  e is the number of entities within the chunk
 * 
 * Average-case time complexity for accesing a tile is O(1)
 **/

/**
 * Instead of accessing the needed entities/components directly,
 * changes/requests can be queued for the next frame.
 * When the systems get iterated next frame, queued changes will be applied.
 * This may be cheaper to do because making a request would always be O(1).
 * However, the response would lag behind by 1 frame instead of being immediate.
 **/

// void move(Tile& origin, Tile& destination)