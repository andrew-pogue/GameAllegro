// #pragma once
// #include "tile.hpp"

// // A rectangle of Tiles. Allows for improved performance when searching
// // or filtering through entities in a area of the game world.
// class Chunk {
// public:
//     Chunk(Position Position1, Position Position2) {
//         if (Position1 <= Position2) {
//             min_ = Position1;
//             max_ = Position2;
//             if (Position1 != Position2 && !(Position1 < Position2)) {
//                 int difx = Position2.x - Position1.x,
//                     dify = Position2.y - Position1.y;
//                 if (dify > 0) {
//                     int dify = Position2.y - Position1.y;
//                     min_.y -= dify;
//                     max_.y += dify;
//                 } else {
//                     min_.x -= difx;
//                     max_.x += difx;
//                 }
//             }
//         } else if (Position1 > Position2) {
//             min_ = Position2;
//             max_ = Position1;
//         }

//         tile_map_.reserve((max_.x - min_.x) * (max_.y - min_.y));
//     }

//     bool contains(const Position& Position) const {
//         return Position.y >= min_.y
//             && Position.y <= max_.y
//             && Position.x >= min_.x
//             && Position.x <= max_.x
//             && Position.z >= min_.z
//             && Position.z <= max_.z;
//     }

//     std::shared_ptr<Tile>& operator[](const Position& Position) {
//         if (!contains(Position))
//             throw std::out_of_range("Chunk doesn't contain Positioninate.");
//         return tile_map_[Position];
//     }

// private:
//     Position min_; // Bottom left corner of chunk
//     Position max_; // Upper right corner of chunk
//     std::unordered_map<Position, std::shared_ptr<Tile>> tile_map_;
// };