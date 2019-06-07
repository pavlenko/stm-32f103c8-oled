#include <mGFX.h>
#include <mGFX_Font_05x07.h>
#include <mGFX_Font_07x10.h>
#include <mGFX_Font_11x18.h>
#include <mGFX_Font_16x26.h>
#include "main.h"

#include "i2c.h"
#include "tim.h"

#include "fonts.h"
#include "ssd1306.h"

#include "font_5x7.h"
#include "SSD1306_2.h"

#include "bitmap0.h"
#include "Timeout.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

SSD1306_t oled;
mGFX_Handle_t ssd1306_gfx;

void __writeByte(uint8_t type, uint8_t byte) {
    HAL_I2C_Mem_Write(
            &i2c2,
            SSD1306_I2C_ADDR,
            type,
            I2C_MEMADD_SIZE_8BIT,
            (uint8_t *) &byte,
            1,
            1000
    );
}

void __writeData(uint8_t type, uint8_t *data, uint16_t length) {
    HAL_I2C_Mem_Write(
            &i2c2,
            SSD1306_I2C_ADDR,
            type,
            I2C_MEMADD_SIZE_8BIT,
            (uint8_t *) data,
            sizeof(uint8_t) * length,
            1000
    );
}

void update_display() {
    for (uint8_t i = 0; i < 8; i++) {
        __writeByte(SSD1306_REG_COMMAND, 0xB0 + i);
        __writeByte(SSD1306_REG_COMMAND, 0x00);
        __writeByte(SSD1306_REG_COMMAND, 0x10);

        __writeData(SSD1306_REG_DATA, &ssd1306_gfx.buffer[ssd1306_gfx.width * i], ssd1306_gfx.width);
    }
}

Timeout_List_t timeout;

void __toggle_led() {
    HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
}

Timeout_Timer_t timerLED;

int main()
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C2_Init();
    MX_TIM2_Init();

    oled.writeByte = [](uint8_t reg, uint8_t byte){
        uint8_t dt[2];
        dt[0] = reg;
        dt[1] = byte;
        HAL_I2C_Master_Transmit(&i2c2, SSD1306_I2C_ADDR, dt, 2, 10);
    };

    oled.writeData = [](uint8_t reg, uint8_t *data, uint16_t length){
        uint8_t dt[1];
        dt[0] = reg;
        //dt[1] = *data;
        HAL_I2C_Master_Transmit(&i2c2, SSD1306_I2C_ADDR, dt, 1, 10);
        HAL_I2C_Master_Transmit(&i2c2, SSD1306_I2C_ADDR, data, length, 10);
    };

    SSD1306_initialize(&oled);

    mGFX_initialize(&ssd1306_gfx, 128, 64);

    mGFX_string(&ssd1306_gfx, 0, 0, "Core...OK", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    mGFX_string(&ssd1306_gfx, 0, 8, "Channel1...OK", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    mGFX_string(&ssd1306_gfx, 0, 16, "Channel2...OK", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    mGFX_string(&ssd1306_gfx, 0, 24, "Channel3...OK", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    mGFX_string(&ssd1306_gfx, 0, 32, "Channel4...OK", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    mGFX_string(&ssd1306_gfx, 0, 40, "Channel5...OK", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    mGFX_string(&ssd1306_gfx, 0, 48, "Channel6...OK", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    mGFX_string(&ssd1306_gfx, 0, 56, "Run main program", &mGFX_Font_05x07, mGFX_WHITE);
    update_display();

    HAL_Delay(2000);
    mGFX_clear(&ssd1306_gfx);

    mGFX_line(&ssd1306_gfx, 0, 0, 127, 63, mGFX_WHITE);
    mGFX_line(&ssd1306_gfx, 0, 63, 127, 0, mGFX_WHITE);
    mGFX_rectangle(&ssd1306_gfx, 0, 0, 127, 63, mGFX_WHITE);
    mGFX_circle(&ssd1306_gfx, 63, 31, 31, mGFX_WHITE);

    update_display();

    HAL_Delay(1500);

    mGFX_clear(&ssd1306_gfx);
    mGFX_bitmap(&ssd1306_gfx, 0, 0, &bitmap0, mGFX_WHITE);
    /*mGFX_bitmap(&ssd1306_gfx, 0, 0, &VUMeter_b, mGFX_WHITE);
    mGFX_string(&ssd1306_gfx, 0, 56, "Hel", &mGFX_Font_05x07, mGFX_WHITE);
    mGFX_string(&ssd1306_gfx, 21, 55, "Hel", &mGFX_Font_07x10, mGFX_WHITE);
    mGFX_string(&ssd1306_gfx, 45, 48, "Hel", &mGFX_Font_11x18, mGFX_WHITE);
    mGFX_string(&ssd1306_gfx, 70, 40, "He", &mGFX_Font_16x26, mGFX_WHITE);*/

    update_display();

    //SSD1306_GotoXY(0, 0);
    //SSD1306__puts("HELLO", SSD1306_COLOR_WHITE);

    //ssd1306_gfx.update();

    //SSD1306_Init();
    //SSD1306_GotoXY(0, 10);
    //SSD1306_Puts("OLED initialized", &Font_7x10, SSD1306_COLOR_WHITE);
    //SSD1306_UpdateScreen();

    //int counter = 0;
    //char buf[20];
    /*int16_t _w = 0;
    int16_t _h = 0;
    int16_t dw = 4;
    int16_t dh = 2;*/

    //tim4.Instance->CCR1 = 2000;

    int16_t _i = 600;
    int16_t di = 0;

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

    timerLED.interval = 500;
    timerLED.callable = __toggle_led;

    Timeout_initialize(&timeout, HAL_GetTick(), 16);

    if (!Timeout_createHandlerRepeated(&timeout, 500, __toggle_led)) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_RESET);
    }

    char str[20];

    while (true) {
        Timeout_dispatch(&timeout, HAL_GetTick());
        sprintf(str, "tick: %lu", HAL_GetTick());
        mGFX_string(&ssd1306_gfx, 0, 0, str, &mGFX_Font_05x07, mGFX_WHITE);

        //char str2[20];
        //sprintf(str2, "tick: %d", sizeof(timeout.items));
        //mGFX_string(&ssd1306_gfx, 0, 8, str2, &mGFX_Font_05x07, mGFX_WHITE);
        //timerLED.callable();
        //Timeout_dispatch(&timeout, HAL_GetTick());
        /*SSD1306_GotoXY(0, 20);
        sprintf(buf, "counter: %d", counter++);
        SSD1306_Puts(buf, &Font_7x10, SSD1306_COLOR_WHITE);
        SSD1306_UpdateScreen();*/
        /*mGFX_clear(&ssd1306_gfx);

        mGFX_line(&ssd1306_gfx, 0, 0, 127, 63, mGFX_WHITE);
        mGFX_line(&ssd1306_gfx, 0, 63, 127, 0, mGFX_WHITE);
        mGFX_circle(&ssd1306_gfx, 63, 31, 31, mGFX_WHITE);

        mGFX_rectangle(&ssd1306_gfx, 0, 0, _w - 1, _h - 1, mGFX_WHITE);*/

        update_display();

        /*if (_w == 0 && _h == 0) {
            dw = 4;
            dh = 2;
        } else if (_w == 128 && _h == 64) {
            dw = -4;
            dh = -2;
        }

        _w += dw;
        _h += dh;*/

        //HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(25);

        if (_i == 1500) {
            di = -10;
            //tim4.Instance->CCR1 = 1500;
        } else if (_i == 600) {
            di = 10;
            //tim4.Instance->CCR1 = 600;
        }

        _i += di;
        tim4.Instance->CCR1 = _i;
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{

  /* GPIO Ports Clock Enable */
    __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef gpio;

    gpio.Pin   = GPIO_PIN_13;
    gpio.Mode  = GPIO_MODE_OUTPUT_PP;
    gpio.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOC, &gpio);

}

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
