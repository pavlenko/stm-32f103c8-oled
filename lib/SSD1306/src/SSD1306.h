#ifndef PE_SSD1306_H
#define PE_SSD1306_H

/**
 * SSD1306 based displays API, except connection transport & graphics
 */
namespace PE {
    typedef enum {
        SSD1306_TYPE_96x16,
        SSD1306_TYPE_128x32,
        SSD1306_TYPE_128x64,
    } SSD1306_Type_t;

    class SSD1306 {
    public:
        SSD1306() = default;
    };
}


#endif //PE_SSD1306_H
