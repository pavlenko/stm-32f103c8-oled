#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "bitmap0.h"
#include "bitmap2.h"

#include "PE_Button.h"
#include "PE_mGFX.h"
#include "PE_mGFX_Font_05x07.h"
#include "PE_SSD1306.h"
#include "PE_Ticker.h"

#include "fsm.h"
#include "ssd1306.h"
#include "servomotor.h"

void SystemClock_Config();
static void MX_GPIO_Init();

void update_display() {
    ssd1306_api.update(ssd1306_gfx.getBuffer(), (128 * 64) / 8);
}

bool readBTN(){ return true; }

PE_Button btn = PE_Button(readBTN);

int main()
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_GPIO_Init();
    MX_I2C2_Init();
    MX_TIM4_Init();

    servo0.setMinimum(640);
    servo0.setMaximum(2250);
    //servo0.setDegree(0);

    fsm.initialize(&SERVO_MID);

    ssd1306_api.initialize();
    ssd1306_gfx.initialize();

    ssd1306_gfx.string(0, 0, "Core...OK", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    ssd1306_gfx.string(0, 8, "Channel1...OK", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    ssd1306_gfx.string(0, 16, "Channel2...OK", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    ssd1306_gfx.string(0, 24, "Channel3...OK", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    ssd1306_gfx.string(0, 32, "Channel4...OK", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    ssd1306_gfx.string(0, 40, "Channel5...OK", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    ssd1306_gfx.string(0, 48, "Channel6...OK", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();
    HAL_Delay(100);
    ssd1306_gfx.string(0, 56, "Run main program", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();

    HAL_Delay(2000);
    ssd1306_gfx.clear();

    ssd1306_gfx.line(0, 0, 127, 63, PE_mGFX_WHITE);
    ssd1306_gfx.line(0, 63, 127, 0, PE_mGFX_WHITE);
    ssd1306_gfx.rectangle(0, 0, 127, 63, PE_mGFX_WHITE);
    ssd1306_gfx.circle(63, 31, 31, PE_mGFX_WHITE);

    update_display();

    HAL_Delay(1500);

    ssd1306_gfx.clear();
    ssd1306_gfx.bitmap(0, 8, &VUMeter_b, PE_mGFX_WHITE);

    update_display();

    /*int16_t _w = 0;
    int16_t _h = 0;
    int16_t dw = 4;
    int16_t dh = 2;*/

    //tim4.Instance->CCR1 = 2000;

    int16_t _i = 600;
    int16_t di = 0;

    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_13, GPIO_PIN_SET);

    PE_Ticker ticker = PE_Ticker();
    ticker.initialize(HAL_GetTick(), 16);
    ticker.createHandlerRepeated(500, [](){ HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13); });

    ticker.createHandlerRepeated(2000, [](){
        if (0 == servo0.getDegree()) {
            //servo0.setDegree(180);
            fsm.initialize(&SERVO_MAX);
        } else {
            //servo0.setDegree(0);
            fsm.initialize(&SERVO_MIN);
        }
    });

    char str[20];

    while (true) {
        ticker.dispatch(HAL_GetTick());
        fsm.dispatch();
        sprintf(str, "tick: %lu", HAL_GetTick());
        ssd1306_gfx.string(0, 0, str, &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

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

        HAL_Delay(25);

        if (_i == 2300) {
            di = -10;
            //tim4.Instance->CCR1 = 1500;
        } else if (_i == 600) {
            di = 10;
            //tim4.Instance->CCR1 = 600;
        }

        _i += di;
        //servo0.setMicros(_i);
        //tim4.Instance->CCR1 = _i;
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config()
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
static void MX_GPIO_Init()
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
 * @brief This function is executed in case of error occurrence.
 * @param file
 * @param line
 */
void _Error_Handler(const char * file, int line)
{
    /* User can add his own implementation to report the HAL error return state */
    while(true) {}
}

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
