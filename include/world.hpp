// #pragma once
// #include <algorithm>
// #include <forward_list>
// #include "chunk.hpp"

// // manages chunks
// class World {
// public:

//     // void parse(file)
//     // void load(Position)
//     World(std::forward_list<Entity> entities) {
//         entities
//     }

//     Tile& operator[](const Position& Position) {
//         auto tile = get_entity(Position);
//         if (!tile) add(Position);
//         return *tile;
//     }
// private:
//     std::unordered_multimap<Position, std::shared_ptr<Chunk>> chunk_map_;
//     // data structure for unloaded chunks

//     void add(const Position& Position) {
//         chunk_map_[Position] = 
//     }

//     std::vector<std::shared_ptr<Chunk>>& get_chunks(const Position& Position) {
//         auto range = chunk_map_.equal_range(Position);
//         std::vector<std::shared_ptr<Chunk>> result;
//         for_each (
//             range.first,
//             range.second,
//             [&result](std::shared_ptr<Chunk> chunk) {
//                 result.push_back(chunk);
//             }
//         );
//         result.shrink_to_fit();
//         return result;
//     }

//     std::shared_ptr<Tile>& get_entity(const Position& Position) {
//         auto chunk = chunk_map_.find(Position);
//         if (chunk == chunk_map_.end()) {
//             // load in chunk and return loaded chunk
//             return std::shared_ptr<Tile>();
//         }
//         return chunk->second->operator[](Position);
//     }
// };

#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <utility>
#include "tile.hpp"

// acts as a tile factory
struct World {
public:
    World();
    ~World();

    // Gets a reference to the tile located at the position.
    // If no tile found, creates a new tile at the position.
    Tile& operator[](const Position& pos) {
        // Do reference variables keep the instance from being deleted?
        return tile_map_.emplace(pos, pos).first->second;
    }

    // tile += entity
    // tile -= entity
    // world[position] = entity;
    // tile -= entity

private:
    std::unordered_map<Position, Tile> tile_map_;
};