#include "main.h"

#include "i2c.h"

#include "fonts.h"
#include "ssd1306.h"

#include "font_5x7.h"
#include "SSD1306_2.h"

#include "MonoLCD.h"

void SystemClock_Config(void);
static void MX_GPIO_Init(void);

MonoLCD ssd1306_gfx = MonoLCD(128, 64);

SSD1306_t oled;

char SSD1306__putc(char ch, SSD1306_COLOR_t color) {
    uint32_t i, b, j;

    for (j = 0; j < 5; j++) {
        b = Font_5x7[ch - 32][j];

        for (i = 0; i < 7; i++) {
            if ((b >> i) & 0x01) {
                SSD1306_DrawPixel(SSD1306_getCurrentX() + j, (SSD1306_getCurrentY() + i), (SSD1306_COLOR_t) color);
            } else {
                SSD1306_DrawPixel(SSD1306_getCurrentX() + j, (SSD1306_getCurrentY() + i), (SSD1306_COLOR_t) !color);
            }
        }
    }

    /* Increase pointer */
    SSD1306_GotoXY(SSD1306_getCurrentX() + 6, SSD1306_getCurrentY());

    /* Return character written */
    return ch;
}

char SSD1306__puts(const char* str, SSD1306_COLOR_t color) {
    while (*str) {
        if (SSD1306__putc(*str, color) != *str) {
            return *str;
        }

        str++;
    }

    return *str;
}

int main(void)
{
  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* Configure the system clock */
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
    MX_I2C2_Init();

    MonoLCD_FONT_t font = {
        .data   = Font_7x10.data,
        .width  = Font_7x10.FontWidth,
        .height = Font_7x10.FontHeight,
    };

    ssd1306_gfx.string(0, 0, "TEST", &font, MonoLCD_COLOR_WHITE);

    oled.writeByte = [](uint8_t byte){
        uint8_t dt[2];
        dt[0] = 0x00;
        dt[1] = byte;
        HAL_I2C_Master_Transmit(&i2c2, SSD1306_I2C_ADDR, dt, 2, 10);
    };

    SSD1306_initialize(&oled);
    SSD1306_GotoXY(0, 0);
    SSD1306__puts("HELLO", SSD1306_COLOR_WHITE);

    //SSD1306_Init();
    SSD1306_GotoXY(0, 10);
    SSD1306_Puts("OLED initialized", &Font_7x10, SSD1306_COLOR_WHITE);
    SSD1306_UpdateScreen();

    int counter = 0;
    char buf[20];

    while (true) {
        SSD1306_GotoXY(0, 20);
        sprintf(buf, "counter: %d", counter++);
        SSD1306_Puts(buf, &Font_7x10, SSD1306_COLOR_WHITE);
        SSD1306_UpdateScreen();

        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(500);
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
