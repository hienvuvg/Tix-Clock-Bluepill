
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2020 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "stm32f3xx_hal.h"

/* USER CODE BEGIN Includes */
/*
M1 x9: M1.1 M1.2 M1.3 ...
M2 x6: M2.1 M2.2 ...
H1 x9: H1.1 H2.2 ...
H2 x3: H2.1 H2.2 H2.3
*/
#include "cstdlib"
#include <stdbool.h> 

/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
IWDG_HandleTypeDef hiwdg;

RTC_HandleTypeDef hrtc;

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/
RTC_TimeTypeDef currTime = {0};
RTC_DateTypeDef currDate = {0};

uint8_t M1 = 0, M2 = 0, H1 = 0, H2 = 0;
int lastSecond = 0;
bool temp[9], displayTime = 1, setPM = 1;
uint32_t errorSecond = 0;
uint8_t  IWDG_Reset = 1;


RTC_TimeTypeDef setTime = {0,0,0,RTC_HOURFORMAT_24,0,0,RTC_DAYLIGHTSAVING_NONE,RTC_STOREOPERATION_RESET}; // Hour, Minute, Second
RTC_DateTypeDef setDate = {6,01,25,20}; // WeekDay, Month, Day, Year
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_IWDG_Init(void);
static void MX_RTC_Init(void);

/* USER CODE BEGIN PFP */
/* Private function prototypes -----------------------------------------------*/

/* USER CODE END PFP */

/* USER CODE BEGIN 0 */
void    DisplayTime(void);
void    DisplaySetTime(void);
int     GeneratePosition(int value, int N_position);
void    ShowPoints(char matrix_location, int position);
int     CountingOne(int data, int N_Position);
void    interruptDisplayTime(void);
void    DisplayAll(void);
void    getTime(void);


/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  *
  * @retval None
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration----------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_IWDG_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */
  //HAL_RTC_SetTime(&hrtc, &setTime, RTC_FORMAT_BIN);
  //HAL_RTC_SetDate(&hrtc, &setDate, RTC_FORMAT_BIN);
    DisplayAll();
    HAL_Delay(1000);
    
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {

  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
    
    // **************************
    if ( ReadPin(IH1_GPIO_Port,IH1_Pin) == 0){
      while( ReadPin(IH1_GPIO_Port,IH1_Pin) == 0);
      getTime();
      if (setTime.Hours < 23)
        setTime.Hours++;
      else
        setTime.Hours = 0;
      
      setTime.Seconds           = 0;
      setTime.SecondFraction    = 0;
      setTime.SubSeconds        = 0;
      
      HAL_RTC_SetTime(&hrtc, &setTime, RTC_FORMAT_BIN);
      HAL_RTC_SetDate(&hrtc, &setDate, RTC_FORMAT_BIN);
      DisplaySetTime();
      
    }
    
    // **************************
    if ( ReadPin(IM1_GPIO_Port,IM1_Pin) == 0){
      while( ReadPin(IM1_GPIO_Port,IM1_Pin) == 0);
      getTime();
      if (setTime.Minutes%10 != 9)
        setTime.Minutes++;
      else
        setTime.Minutes = setTime.Minutes - 9;
      
      setTime.Seconds           = 0;
      setTime.SecondFraction    = 0;
      setTime.SubSeconds        = 0;
      
      HAL_RTC_SetTime(&hrtc, &setTime, RTC_FORMAT_BIN);
      HAL_RTC_SetDate(&hrtc, &setDate, RTC_FORMAT_BIN);
      DisplaySetTime();
    }
    
    // **************************
    if ( ReadPin(IM2_GPIO_Port,IM2_Pin) == 0){
      while( ReadPin(IM2_GPIO_Port,IM2_Pin) == 0);
      getTime();
      if (setTime.Minutes < 49)
        setTime.Minutes = setTime.Minutes + 10;
      else
        setTime.Minutes = setTime.Minutes - 50;
      
      setTime.Seconds           = 0;
      setTime.SecondFraction    = 0;
      setTime.SubSeconds        = 0;
      
      HAL_RTC_SetTime(&hrtc, &setTime, RTC_FORMAT_BIN);
      HAL_RTC_SetDate(&hrtc, &setDate, RTC_FORMAT_BIN);
      DisplaySetTime();
    }
      
  }
  /* USER CODE END 3 */

}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{

  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_ClkInitTypeDef RCC_ClkInitStruct;
  RCC_PeriphCLKInitTypeDef PeriphClkInit;

    /**Configure LSE Drive Capability 
    */
  HAL_PWR_EnableBkUpAccess();

  __HAL_RCC_LSEDRIVE_CONFIG(RCC_LSEDRIVE_MEDIUMLOW);

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_HSE
                              |RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Initializes the CPU, AHB and APB busses clocks 
    */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

    /**Configure the Systick interrupt time 
    */
  HAL_SYSTICK_Config(HAL_RCC_GetHCLKFreq()/1000);

    /**Configure the Systick 
    */
  HAL_SYSTICK_CLKSourceConfig(SYSTICK_CLKSOURCE_HCLK);

  /* SysTick_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(SysTick_IRQn, 1, 0);
}

/* IWDG init function */
static void MX_IWDG_Init(void)
{

  hiwdg.Instance = IWDG;
  hiwdg.Init.Prescaler = IWDG_PRESCALER_16;
  hiwdg.Init.Window = 4094;
  hiwdg.Init.Reload = 4095;
  if (HAL_IWDG_Init(&hiwdg) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/* RTC init function */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

    /**Initialize RTC Only 
    */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 127;
  hrtc.Init.SynchPrediv = 255;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    _Error_Handler(__FILE__, __LINE__);
  }

}

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
        * Free pins are configured automatically as Analog (this feature is enabled through 
        * the Code Generation settings)
*/
static void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(Tix_GPIO_Port, Tix_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, H2_1_Pin|H2_2_Pin|H2_3_Pin|H1_1_Pin 
                          |H1_2_Pin|H1_3_Pin|H1_4_Pin|H1_5_Pin 
                          |M1_7_Pin|M1_6_Pin|M1_5_Pin|M1_4_Pin 
                          |M1_3_Pin|M1_2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, H1_6_Pin|H1_7_Pin|H1_8_Pin|H1_9_Pin 
                          |M1_9_Pin|M1_8_Pin|M1_1_Pin|M2_6_Pin 
                          |M2_5_Pin|M2_4_Pin|M2_3_Pin|M2_2_Pin 
                          |M2_1_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : Tix_Pin */
  GPIO_InitStruct.Pin = Tix_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(Tix_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : H2_1_Pin H2_2_Pin H2_3_Pin H1_1_Pin 
                           H1_2_Pin H1_3_Pin H1_4_Pin H1_5_Pin 
                           M1_7_Pin M1_6_Pin M1_5_Pin M1_4_Pin 
                           M1_3_Pin M1_2_Pin */
  GPIO_InitStruct.Pin = H2_1_Pin|H2_2_Pin|H2_3_Pin|H1_1_Pin 
                          |H1_2_Pin|H1_3_Pin|H1_4_Pin|H1_5_Pin 
                          |M1_7_Pin|M1_6_Pin|M1_5_Pin|M1_4_Pin 
                          |M1_3_Pin|M1_2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : H1_6_Pin H1_7_Pin H1_8_Pin H1_9_Pin 
                           M1_9_Pin M1_8_Pin M1_1_Pin M2_6_Pin 
                           M2_5_Pin M2_4_Pin M2_3_Pin M2_2_Pin 
                           M2_1_Pin */
  GPIO_InitStruct.Pin = H1_6_Pin|H1_7_Pin|H1_8_Pin|H1_9_Pin 
                          |M1_9_Pin|M1_8_Pin|M1_1_Pin|M2_6_Pin 
                          |M2_5_Pin|M2_4_Pin|M2_3_Pin|M2_2_Pin 
                          |M2_1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : IM1_Pin IH1_Pin IM2_Pin */
  GPIO_InitStruct.Pin = IM1_Pin|IH1_Pin|IM2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */
/*
M1 x9: M1.1 M1.2 M1.3 ...
M2 x6: M2.1 M2.2 ...
H1 x9: H1.1 H2.2 ...
H2 x3: H2.1 H2.2 H2.3
*/

void getTime(void){
    
    HAL_RTC_GetTime(&hrtc, &currTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &currDate, RTC_FORMAT_BIN);
    //
    setTime.Hours       = currTime.Hours;
    setTime.Minutes     = currTime.Minutes;
    setTime.Seconds     = currTime.Seconds;
    
    
}
void interruptDisplayTime(void){
  lastSecond = currTime.Seconds;
  getTime();
  
  if (currTime.Seconds == lastSecond + 1) {
    HAL_GPIO_TogglePin(Tix_GPIO_Port,Tix_Pin);
    //SetPin(Tix_GPIO_Port, Tix_Pin, GPIO_PIN_RESET); 
    //HAL_Delay(100);
    //SetPin(Tix_GPIO_Port, Tix_Pin, GPIO_PIN_SET);
  }
  else if ( currTime.Seconds != 0 ) errorSecond++;
  /*
  if (currTime.Minutes == 0 && currTime.Seconds == 0) {
    SetPin(Tix_GPIO_Port, Tix_Pin, GPIO_PIN_SET); 
    HAL_Delay(300);
    ResetPin(Tix_GPIO_Port, Tix_Pin, GPIO_PIN_RESET);
  }
  */
  if(displayTime == 1) DisplayTime();
}

void DisplayTime(void){
  int position = 0;
  
  if (setPM == 1){
    if ( currTime.Hours > 12 ) currTime.Hours = currTime.Hours - 12;
    if ( currTime.Hours == 0 ) currTime.Hours = 12;
  }
  
  M1 = currTime.Minutes%10;
  position = GeneratePosition(M1,9);
  ShowPoints(1,position);
  
  M2 = currTime.Minutes/10;
  position = GeneratePosition(M2,6);
  ShowPoints(2,position);
  
  H1 = currTime.Hours%10;
  position = GeneratePosition(H1,9);
  ShowPoints(3,position);
  
  H2 = currTime.Hours/10;
  position = GeneratePosition(H2,3);
  ShowPoints(4,position);
  
}

void DisplaySetTime(void){
  int position = 0;
  
  if (setPM == 1){
    if ( setTime.Hours > 12 ) setTime.Hours = setTime.Hours - 12;
    if ( setTime.Hours == 0 ) setTime.Hours = 12;
  }
  
  M1 = setTime.Minutes%10;
  position = GeneratePosition(M1,9);
  ShowPoints(1,position);
  
  M2 = setTime.Minutes/10;
  position = GeneratePosition(M2,6);
  ShowPoints(2,position);
  
  H1 = setTime.Hours%10;
  position = GeneratePosition(H1,9);
  ShowPoints(3,position);
  
  H2 = setTime.Hours/10;
  position = GeneratePosition(H2,3);
  ShowPoints(4,position);
  
}

void DisplayAll(void){
  ShowPoints(1,0x1FF);
  ShowPoints(2,0x3F);
  ShowPoints(3,0x1FF);
  ShowPoints(4,0x07);
}

int GeneratePosition(int value, int N_Position){
  int data = 0;
  int position = 0;
  int NoOfOne = 0;
  // Generate position data from value
    while(NoOfOne < value){
        if (temp[position] == 0){
            if ((( rand()%100)%10) > 5){
                temp[position] = 1;
                NoOfOne++;
            }
        }
        if (position < (N_Position - 1) ) 
          position++;
        else 
          position = 0;
    }

    // Copy from array to binary
    for (int i = 0; i < N_Position; i++){
      if (temp[i] == 1) data++; 
      data = data<<1;
    }
    data = data>>1;
    
    // Format temp
    for (int i = 0; i < 9; i++ ){
      temp[i] = 0;
    }
    
  return data;
}

int CountingOne(int data, int N_Position){
  int NoOfOne = 0;
  int temp = data;
  for (int i = 0; i < N_Position; i++){
    if (temp&0x01) NoOfOne++;
    temp = temp >> 1;
  }
  return NoOfOne;
}

void ShowPoints(char matrix_location, int position){
  switch(matrix_location){
  case 1:
    if (position&0x01)  SetPin(M1_1_GPIO_Port,M1_1_Pin,SetLED);
    else                SetPin(M1_1_GPIO_Port,M1_1_Pin,ResetLED);
    if (position&0x02)  SetPin(M1_2_GPIO_Port,M1_2_Pin,SetLED);
    else                SetPin(M1_2_GPIO_Port,M1_2_Pin,ResetLED);
    if (position&0x04)  SetPin(M1_3_GPIO_Port,M1_3_Pin,SetLED);
    else                SetPin(M1_3_GPIO_Port,M1_3_Pin,ResetLED);
    if (position&0x08)  SetPin(M1_4_GPIO_Port,M1_4_Pin,SetLED);
    else                SetPin(M1_4_GPIO_Port,M1_4_Pin,ResetLED);
    if (position&0x10)  SetPin(M1_5_GPIO_Port,M1_5_Pin,SetLED);
    else                SetPin(M1_5_GPIO_Port,M1_5_Pin,ResetLED);
    if (position&0x20)  SetPin(M1_6_GPIO_Port,M1_6_Pin,SetLED);
    else                SetPin(M1_6_GPIO_Port,M1_6_Pin,ResetLED);
    if (position&0x40)  SetPin(M1_7_GPIO_Port,M1_7_Pin,SetLED);
    else                SetPin(M1_7_GPIO_Port,M1_7_Pin,ResetLED);
    if (position&0x80)  SetPin(M1_8_GPIO_Port,M1_8_Pin,SetLED);
    else                SetPin(M1_8_GPIO_Port,M1_8_Pin,ResetLED);
    if (position&0x100) SetPin(M1_9_GPIO_Port,M1_9_Pin,SetLED);
    else                SetPin(M1_9_GPIO_Port,M1_9_Pin,ResetLED);
    break;
  case 2: 
    if (position&0x01)  SetPin(M2_1_GPIO_Port,M2_1_Pin,SetLED);
    else                SetPin(M2_1_GPIO_Port,M2_1_Pin,ResetLED);
    if (position&0x02)  SetPin(M2_2_GPIO_Port,M2_2_Pin,SetLED);
    else                SetPin(M2_2_GPIO_Port,M2_2_Pin,ResetLED);
    if (position&0x04)  SetPin(M2_3_GPIO_Port,M2_3_Pin,SetLED);
    else                SetPin(M2_3_GPIO_Port,M2_3_Pin,ResetLED);
    if (position&0x08)  SetPin(M2_4_GPIO_Port,M2_4_Pin,SetLED);
    else                SetPin(M2_4_GPIO_Port,M2_4_Pin,ResetLED);
    if (position&0x10)  SetPin(M2_5_GPIO_Port,M2_5_Pin,SetLED);
    else                SetPin(M2_5_GPIO_Port,M2_5_Pin,ResetLED);
    if (position&0x20)  SetPin(M2_6_GPIO_Port,M2_6_Pin,SetLED);
    else                SetPin(M2_6_GPIO_Port,M2_6_Pin,ResetLED);
    break;
  case 3: 
    if (position&0x01)  SetPin(H1_1_GPIO_Port,H1_1_Pin,SetLED);
    else                SetPin(H1_1_GPIO_Port,H1_1_Pin,ResetLED);
    if (position&0x02)  SetPin(H1_2_GPIO_Port,H1_2_Pin,SetLED);
    else                SetPin(H1_2_GPIO_Port,H1_2_Pin,ResetLED);
    if (position&0x04)  SetPin(H1_3_GPIO_Port,H1_3_Pin,SetLED);
    else                SetPin(H1_3_GPIO_Port,H1_3_Pin,ResetLED);
    if (position&0x08)  SetPin(H1_4_GPIO_Port,H1_4_Pin,SetLED);
    else                SetPin(H1_4_GPIO_Port,H1_4_Pin,ResetLED);
    if (position&0x10)  SetPin(H1_5_GPIO_Port,H1_5_Pin,SetLED);
    else                SetPin(H1_5_GPIO_Port,H1_5_Pin,ResetLED);
    if (position&0x20)  SetPin(H1_6_GPIO_Port,H1_6_Pin,SetLED);
    else                SetPin(H1_6_GPIO_Port,H1_6_Pin,ResetLED);
    if (position&0x40)  SetPin(H1_7_GPIO_Port,H1_7_Pin,SetLED);
    else                SetPin(H1_7_GPIO_Port,H1_7_Pin,ResetLED);
    if (position&0x80)  SetPin(H1_8_GPIO_Port,H1_8_Pin,SetLED);
    else                SetPin(H1_8_GPIO_Port,H1_8_Pin,ResetLED);
    if (position&0x100) SetPin(H1_9_GPIO_Port,H1_9_Pin,SetLED);
    else                SetPin(H1_9_GPIO_Port,H1_9_Pin,ResetLED);
    break;
  case 4: 
    if (position&0x01)  SetPin(H2_1_GPIO_Port,H2_1_Pin,SetLED);
    else                SetPin(H2_1_GPIO_Port,H2_1_Pin,ResetLED);
    if (position&0x02)  SetPin(H2_2_GPIO_Port,H2_2_Pin,SetLED);
    else                SetPin(H2_2_GPIO_Port,H2_2_Pin,ResetLED);
    if (position&0x04)  SetPin(H2_3_GPIO_Port,H2_3_Pin,SetLED);
    else                SetPin(H2_3_GPIO_Port,H2_3_Pin,ResetLED);
    break;
  default: break;
  }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  file: The file name as string.
  * @param  line: The line in file as a number.
  * @retval None
  */
void _Error_Handler(char *file, int line)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  while(1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
