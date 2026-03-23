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
};