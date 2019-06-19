#include "main.h"
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

ADC_HandleTypeDef hadc1;
DMA_HandleTypeDef hdma_adc1;
uint16_t ADCReadings[2]; //ADC Readings

void SystemClock_Config();
static void MX_GPIO_Init();
static void MX_ADC1_Init();
static void MX_DMA_Init();

void update_display() {
    ssd1306_api.update(ssd1306_gfx.getBuffer(), (128 * 64) / 8);
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
    MX_I2C2_Init();
    MX_TIM4_Init();
    MX_ADC1_Init();
    MX_DMA_Init();

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
    ssd1306_gfx.bitmap(0, 16, &VUMeter_b, PE_mGFX_WHITE);

    update_display();

    PE_Ticker ticker = PE_Ticker();
    ticker.initialize(HAL_GetTick(), 16);

    ticker.createHandlerRepeated(2000, [](){
        if (0 == servo0.getDegree()) {
            fsm.transitionTo(&SERVO_MAX);
        } else {
            fsm.transitionTo(&SERVO_MIN);
        }
    });

    ticker.createHandlerRepeated(100, [](){
        LED(LED_ON);
        char str[20];

        sprintf(str, "tick: %lu", HAL_GetTick());
        ssd1306_gfx.string(0, 0, str, &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

        ssd1306_gfx.string(0, 8, "              ", &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

        sprintf(str, "B: %u H: %lu", (uint8_t) pin14press, pin14hold);
        ssd1306_gfx.string(0, 8, str, &PE_mGFX_Font_05x07, PE_mGFX_WHITE);

        update_display();
    });

    btn.setOnPress([](){ pin14press = true; pin14hold = 0; });
    btn.setOnRelease([](){ pin14press = false; pin14hold = 0; });
    btn.setOnHoldSingular([](){ pin14hold++; });
    btn.setOnHoldRepeated([](){ pin14hold++; });

    __enable_irq();
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) ADCReadings, 2);//start the DMA collecting the data

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

/* ADC1 init function */
void MX_ADC1_Init() {
    ADC_ChannelConfTypeDef sConfig;

    /** Common config */
    hadc1.Instance                   = ADC1;
    hadc1.Init.ScanConvMode          = ADC_SCAN_ENABLE;
    hadc1.Init.ContinuousConvMode    = ENABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv      = ADC_SOFTWARE_START;
    hadc1.Init.NbrOfDiscConversion   = 0;
    hadc1.Init.DataAlign             = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion       = 2;

    if (HAL_ADC_Init(&hadc1) != HAL_OK) {
        Error_Handler();
    }

    /** Configure Regular Channel */
    sConfig.Channel      = ADC_CHANNEL_0;
    sConfig.Rank         = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;

    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
        Error_Handler();
    }

    /** Configure Regular Channel */
    sConfig.Channel      = ADC_CHANNEL_1;
    sConfig.Rank         = ADC_REGULAR_RANK_2;
    sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;

    if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK) {
        Error_Handler();
    }

}

void MX_DMA_Init() {
    /* DMA controller clock enable */
    __HAL_RCC_DMA1_CLK_ENABLE();

    /* DMA interrupt init */
    /* DMA1_Channel1_IRQn interrupt configuration */
    HAL_NVIC_SetPriority(DMA1_Channel1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(DMA1_Channel1_IRQn);
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
