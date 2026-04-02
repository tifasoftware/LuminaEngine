#pragma once

class IControllable {
    public:
    IControllable() = default;
    virtual ~IControllable() = default;

    //PSP - DPAD Up
    //Computer - W
    virtual void OnMoveUp() {};
    virtual void OnStopMoveUp() {};

    //PSP - DPAD Down
    //Computer - S
    virtual void OnMoveDown() {};
    virtual void OnStopMoveDown() {};

    //PSP - DPAD Left
    //Computer - A
    virtual void OnMoveLeft() {};
    virtual void OnStopMoveLeft() {};

    //PSP - DPAD Right
    //Computer - D
    virtual void OnMoveRight() {};
    virtual void OnStopMoveRight() {};

    //PSP - DPAD UP
    //PC - Keyboard Up
    virtual void OnButtonUp() {};

    //PSP - DPAD Down
    //PC - Keyboard Down
    virtual void OnButtonDown() {};

    //PSP - DPAD Left
    //PC - Keyboard Left
    virtual void OnButtonLeft() {};

    //PSP - DPAD Right
    //PC - Keyboard Right
    virtual void OnButtonRight() {};

    //PSP - Cross
    //3DS - A
    //Computer - Enter/Return
    virtual void OnButtonA() {};

    //PSP - Circle
    //3DS - B
    //Computer - Backspace
    virtual void OnButtonB() {};

    //PSP - Triangle
    //3DS - Y
    //Computer - Tab
    virtual void OnButtonY() {};

    //PSP - Square
    //3DS - X
    //Computer - E
    virtual void OnButtonX() {};

    //PSP - Select
    //3DS - Select
    //Computer - Space
    virtual void OnButtonSelect() {};

    //PSP - Start
    //3DS - Start
    //Computer - Escape
    virtual void OnButtonStart() {};

    //Window Close or maybe PSP OS Quit
    virtual void OnQuit() {};

    bool getActive() { return isActive; }
    void activate() { isActive = true; }
    void deactivate() { isActive = false; }
protected:
    bool isActive = false;
};