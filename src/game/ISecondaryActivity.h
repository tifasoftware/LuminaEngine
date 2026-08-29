#pragma once

class ISecondaryActivity : public IControllable {
    public:
    ISecondaryActivity() = default;
    //virtual ~ISecondaryActivity() = default;

    virtual void render() {}
};
