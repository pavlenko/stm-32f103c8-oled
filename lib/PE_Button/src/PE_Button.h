#ifndef PE_BUTTON_H
#define PE_BUTTON_H

#include <stdint.h>

#ifndef PE_BUTTON_USE_HOLD_SINGULAR
#define PE_BUTTON_USE_HOLD_SINGULAR 1
#endif

#ifndef PE_BUTTON_USE_HOLD_REPEATED
#define PE_BUTTON_USE_HOLD_REPEATED 1
#endif

#ifndef PE_BUTTON_TIMEOUT_DEBRIEF
#define PE_BUTTON_TIMEOUT_DEBRIEF 10U
#endif

#ifndef PE_BUTTON_TIMEOUT_HOLD_SINGULAR
#define PE_BUTTON_TIMEOUT_HOLD_SINGULAR 1000U
#endif

#ifndef PE_BUTTON_TIMEOUT_HOLD_REPEATED
#define PE_BUTTON_TIMEOUT_HOLD_REPEATED 1200U
#endif

#ifndef PE_BUTTON_TIMEOUT_REPEAT
#define PE_BUTTON_TIMEOUT_REPEAT 100U
#endif

typedef bool (*PE_ButtonReader_t) ();
typedef bool (*PE_ButtonHandler_t) ();

class PE_Button {
private:
    PE_ButtonReader_t _reader;
    uint8_t _status = 0;
    uint32_t _millis = 0;
    PE_ButtonHandler_t _onPress        = nullptr;
    PE_ButtonHandler_t _onRelease      = nullptr;
#if PE_BUTTON_USE_HOLD_SINGULAR == 1
    PE_ButtonHandler_t _onHoldSingular = nullptr;
#endif
#if PE_BUTTON_USE_HOLD_REPEATED == 1
    PE_ButtonHandler_t _onHoldRepeated = nullptr;
#endif
public:
    explicit PE_Button(PE_ButtonReader_t reader);

    /**
     * Init button internal timestamp
     *
     * @param millis
     */
    void initialize(uint32_t millis);

    /**
     * Dispatch button handlers
     *
     * @param millis
     */
    void dispatch(uint32_t millis);

    /**
     * Set handler for press event
     *
     * @param handler
     */
    void setOnPress(PE_ButtonHandler_t handler);

    /**
     * Set handler for release event
     *
     * @param handler
     */
    void setOnRelease(PE_ButtonHandler_t handler);

#if PE_BUTTON_USE_HOLD_SINGULAR == 1
    /**
     * Set handler for singular hold event
     *
     * @param handler
     */
    void setOnHoldSingular(PE_ButtonHandler_t handler);
#endif

#if PE_BUTTON_USE_HOLD_REPEATED == 1
    /**
     * Set handler for repeated hold event
     *
     * @param handler
     */
    void setOnHoldRepeated(PE_ButtonHandler_t handler);
#endif
};

#endif //PE_BUTTON_H
