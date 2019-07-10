#include "main.h"
#include "adc.h"
#include "calc.h"
#include "dma.h"
#include "led.h"
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
#include "pwm_driver.h"

DMA_HandleTypeDef hdma_adc1;

void SystemClock_Config();
static void MX_GPIO_Init();

void update_display() {
    ssd1306_api.update(ssd1306_gfx.getBufferData(), ssd1306_gfx.getBufferSize());
}

static volatile bool pin14press = false;
static volatile uint32_t pin14hold = 0;

bool readBTN(){
    return HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_14) == GPIO_PIN_RESET;
}

PE_Button btn = PE_Button(readBTN);

int main()
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    HAL_Init();

    /* Configure the system clock */
    SystemClock_Config();

    /* Initialize all configured peripherals */
    MX_LED_Init();
    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_I2C2_Init();
    MX_TIM4_Init();
    MX_DMA_Init();
    MX_ADC1_Init();

    servo0.setMinimum(640);
    servo0.setMaximum(2250);
    //servo0.setDegree(0);

    fsm.initialize(&SERVO_MID);

    ssd1306_api.initialize();
    ssd1306_gfx.initialize();

    HAL_Delay(100);

    //scan i2c bus
    uint8_t i, j = 0, y = 0;
    char scan[20];

    for (i = 1; i < 128; i ++) {
        if (HAL_I2C_IsDeviceReady(&i2c1, (uint16_t) (i << 1u), 2, 100) != HAL_OK) { // HAL_ERROR or HAL_BUSY or HAL_TIMEOUT
            sprintf(scan, "_x%X", (i << 1u));
            ssd1306_gfx.string(0, y, scan, &PE_mGFX_Font_05x07, PE_mGFX_WHITE); // No ACK received at that address
            update_display();
        } else {
            sprintf(scan, "0x%X", (i << 1u));
            ssd1306_gfx.string(0, y, scan, &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
            update_display();
            y += (PE_mGFX_Font_05x07.height + 1);
        }
    }

    HAL_Delay(2000);

    uint8_t  PWM_ADDR   = 0x1E;
    uint8_t  PWM_W_REG  = PWM_DRIVER_CMD_W_REGISTER(PWM_DRIVER_CH0_PULSE);
    uint8_t  PWM_R_REG  = PWM_DRIVER_CMD_R_REGISTER(PWM_DRIVER_CH0_PULSE);
    uint16_t PWM_value0 = 0x14E;
    uint16_t PWM_value1;

    ssd1306_gfx.string(0, 4 * (PE_mGFX_Font_05x07.height + 1), "write", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();

    HAL_I2C_Mem_Write(&i2c1, PWM_ADDR, PWM_W_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *) &PWM_value0, 2, 10);

    ssd1306_gfx.string(0, 5 * (PE_mGFX_Font_05x07.height + 1), "read", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();

    HAL_I2C_Mem_Read(&i2c1, PWM_ADDR, PWM_R_REG, I2C_MEMADD_SIZE_8BIT, (uint8_t *) &PWM_value1, 2, 10);

    char result[18];
    sprintf(result, "0x%.4X == 0x%.4X", PWM_value0, PWM_value1);
    ssd1306_gfx.string(0, 6 * (PE_mGFX_Font_05x07.height + 1), result, &PE_mGFX_Font_05x07, PE_mGFX_WHITE);
    update_display();

    HAL_Delay(3000);

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
    ssd1306_gfx.bitmap(0, 16, &VUMeter_b, PE_mGFX_WHITE);

    update_display();

    PE_Ticker ticker = PE_Ticker();
    ticker.initialize(HAL_GetTick(), 16);

    /*ticker.createHandlerRepeated(2000, [](){
        if (0 == servo0.getDegree()) {
            fsm.transitionTo(&SERVO_MAX);
        } else {
            fsm.transitionTo(&SERVO_MIN);
        }
    });*/

    ticker.createHandlerRepeated(100, [](){
        uint16_t channel0, channel1;

        ADC_Fetch(&channel0, &channel1);

        servo0.setMicros(map(channel0, 0, 2000, 600, 2300));

        LED(LED_ON);
        char str[20];

        sprintf(str, "tick: %lu", HAL_GetTick());
        ssd1306_gfx.string(0, 0, str, &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

        ssd1306_gfx.string(0, 8, "              ", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

        //sprintf(str, "B: %u H: %lu", (uint8_t) pin14press, pin14hold);
        sprintf(str, "adc: %d %d", channel0, channel1);
        ssd1306_gfx.string(0, 8, str, &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

        update_display();
    });

    ticker.createHandlerRepeated(50, [](){
        ADC_Start();
    });

    btn.setOnPress([](){ pin14press = true; pin14hold = 0; });
    btn.setOnRelease([](){ pin14press = false; pin14hold = 0; });
    btn.setOnHoldSingular([](){ pin14hold++; });
    btn.setOnHoldRepeated([](){ pin14hold++; });

    while (true) {
        ticker.dispatch(HAL_GetTick());
        fsm.dispatch();
        btn.dispatch(HAL_GetTick());
        LED(LED_OFF);
    }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config() {
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    /** Initializes the CPU, AHB and APB busses clocks */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState       = RCC_HSE_ON;
    RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
    RCC_OscInitStruct.HSIState       = RCC_HSI_ON;
    RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource  = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLMUL     = RCC_PLL_MUL9;

    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        Error_Handler();
    }

    /** Initializes the CPU, AHB and APB busses clocks */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK
                                | RCC_CLOCKTYPE_SYSCLK
                                | RCC_CLOCKTYPE_PCLK1
                                | RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource   = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider  = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK) {
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
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_InitTypeDef gpioC14;

    gpioC14.Pin   = GPIO_PIN_14;
    gpioC14.Mode  = GPIO_MODE_INPUT;
    gpioC14.Pull  = GPIO_PULLUP;
    gpioC14.Speed = GPIO_SPEED_FREQ_HIGH;

    HAL_GPIO_Init(GPIOC, &gpioC14);
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
