#pragma once
#include <stdio.h>

// can act on props or other actors
struct Actor {
    virtual ~Actor() {};
    virtual void act() const = 0;
    virtual void transform() = 0;
    virtual void render() const = 0;
};