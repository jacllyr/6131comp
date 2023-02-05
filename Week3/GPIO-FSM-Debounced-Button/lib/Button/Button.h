#ifndef BUTTON_H_
#define BUTTON_H_

enum ButtonState
{
    ON,
    OFF
};

class Button
{
private:
    const int BOUNCE_DELAY_MS = 5;
    int pin;
    ButtonState debouncedState = ButtonState::OFF;
    ButtonState bouncedState = ButtonState::OFF;
    long lastChange;

public:
    Button();
    Button(int pin);
    ButtonState checkState();
};

#endif /* BUTTON_H_ */ 
