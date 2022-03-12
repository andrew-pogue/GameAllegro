#pragma once
#include "chunk.hpp"

// manages chunks
class World {
public:

    // void parse(file)
    // void load(coord)

    Tile& operator[](const Coord& coord) {
        auto chunk = chunk_map_.find(coord);
        if (chunk == chunk_map_.end()) {
            // load in chunk and return loaded chunk
            // if chunk doesn't exist/can't be loaded, throw error
            throw std::out_of_range("Chunk doesn't exist");
        }
        return chunk_map_.find(coord)->second->operator[](coord);
    }

private:
    std::unordered_multimap<Coord, std::shared_ptr<Chunk>> chunk_map_;
    // data structure for unloaded chunks
};