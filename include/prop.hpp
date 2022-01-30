#pragma once

// gets acted on by actors
struct Prop {
    virtual ~Prop() {}
    virtual void render() const = 0;
    virtual void transform() = 0;
};