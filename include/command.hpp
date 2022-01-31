#pragma once
#include "actor.hpp"

/*

struct Command {
    virtual ~Command() {}
    virtual void run(Actor* actor) = 0;
};

class DoNothing : Command {
    void run(Actor* actor) override {};
};

class MoveN : Command {
public:
    void run(Actor* actor) override
    { actor->move(Direction(1,0,0,0)); };
};

class MoveS : Command {
public:
    void run(Actor* actor) override
    { actor->move(Direction(0,1,0,0)); };
};

class MoveE : Command {
public:
    void run(Actor* actor) override
    { actor->move(Direction(0,0,1,0)); };
};

class MoveW : Command {
public:
    void run(Actor* actor) override
    { actor->move(Direction(0,0,0,1)); };
};

*/