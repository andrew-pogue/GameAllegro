#pragma once

struct Command {
    virtual ~Command() {}
    virtual void run() = 0;
};

class MoveRight : Command {
public:
    void run();
};