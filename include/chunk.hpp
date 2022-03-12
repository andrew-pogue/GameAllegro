#pragma once
#include "tile.hpp"

// manages tiles
class Chunk {
public:
    Chunk(Coord coord1, Coord coord2) {
        if (coord1 <= coord2) {
            min_ = coord1;
            max_ = coord2;
            if (coord1 != coord2 && !(coord1 < coord2)) {
                int difx = coord2.x - coord1.x,
                    dify = coord2.y - coord1.y;
                if (dify > 0) {
                    int dify = coord2.y - coord1.y;
                    min_.y -= dify;
                    max_.y += dify;
                } else {
                    min_.x -= difx;
                    max_.x += difx;
                }
            }
        } else if (coord1 > coord2) {
            min_ = coord2;
            max_ = coord1;
        }

        tile_map_.reserve((max_.x - min_.x) * (max_.y - min_.y));
    }

    bool contains(const Coord& coord) const {
        return coord >= min_ && coord <= max_;
    }

    std::shared_ptr<Tile> operator[](const Coord& coord) {
        if (!contains(coord))
            throw std::out_of_range("Chunk doesn't contain coordinate.");
        return tile_map_[coord];
    }

private:
    Coord min_; // Bottom left corner of chunk
    Coord max_; // Upper right corner of chunk
    std::unordered_map<Coord, std::shared_ptr<Tile>> tile_map_;
};