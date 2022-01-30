#pragma once
#include <stdio.h>

struct Entity {
    virtual ~Entity() = 0;
    virtual void update() = 0;
    virtual void render() const = 0;
};