/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H__
#define __MAIN_H__

/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private define ------------------------------------------------------------*/

#define H2_1_Pin GPIO_PIN_0
#define H2_1_GPIO_Port GPIOA
#define H2_2_Pin GPIO_PIN_1
#define H2_2_GPIO_Port GPIOA
#define H2_3_Pin GPIO_PIN_2
#define H2_3_GPIO_Port GPIOA
#define H1_1_Pin GPIO_PIN_3
#define H1_1_GPIO_Port GPIOA
#define H1_2_Pin GPIO_PIN_4
#define H1_2_GPIO_Port GPIOA
#define H1_3_Pin GPIO_PIN_5
#define H1_3_GPIO_Port GPIOA
#define H1_4_Pin GPIO_PIN_6
#define H1_4_GPIO_Port GPIOA
#define H1_5_Pin GPIO_PIN_7
#define H1_5_GPIO_Port GPIOA
#define H1_6_Pin GPIO_PIN_0
#define H1_6_GPIO_Port GPIOB
#define H1_7_Pin GPIO_PIN_1
#define H1_7_GPIO_Port GPIOB
#define IH1_Pin GPIO_PIN_2
#define IH1_GPIO_Port GPIOB
#define H1_8_Pin GPIO_PIN_10
#define H1_8_GPIO_Port GPIOB
#define H1_9_Pin GPIO_PIN_11
#define H1_9_GPIO_Port GPIOB
#define IM1_Pin GPIO_PIN_12
#define IM1_GPIO_Port GPIOB
#define IM2_Pin GPIO_PIN_13
#define IM2_GPIO_Port GPIOB
#define M1_9_Pin GPIO_PIN_14
#define M1_9_GPIO_Port GPIOB
#define M1_8_Pin GPIO_PIN_15
#define M1_8_GPIO_Port GPIOB
#define M1_7_Pin GPIO_PIN_8
#define M1_7_GPIO_Port GPIOA
#define M1_6_Pin GPIO_PIN_9
#define M1_6_GPIO_Port GPIOA
#define M1_5_Pin GPIO_PIN_10
#define M1_5_GPIO_Port GPIOA
#define M1_4_Pin GPIO_PIN_11
#define M1_4_GPIO_Port GPIOA
#define M1_3_Pin GPIO_PIN_12
#define M1_3_GPIO_Port GPIOA
#define M1_2_Pin GPIO_PIN_15
#define M1_2_GPIO_Port GPIOA
#define M1_1_Pin GPIO_PIN_3
#define M1_1_GPIO_Port GPIOB
#define M2_6_Pin GPIO_PIN_4
#define M2_6_GPIO_Port GPIOB
#define M2_5_Pin GPIO_PIN_5
#define M2_5_GPIO_Port GPIOB
#define M2_4_Pin GPIO_PIN_6
#define M2_4_GPIO_Port GPIOB
#define M2_3_Pin GPIO_PIN_7
#define M2_3_GPIO_Port GPIOB
#define M2_2_Pin GPIO_PIN_8
#define M2_2_GPIO_Port GPIOB
#define M2_1_Pin GPIO_PIN_9
#define M2_1_GPIO_Port GPIOB

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "assert_param" macro in the 
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* USER CODE BEGIN Private defines */

#define ResetLED           GPIO_PIN_RESET
#define SetLED             GPIO_PIN_SET

#define SetPin          HAL_GPIO_WritePin
#define ReadPin         HAL_GPIO_ReadPin


/* USER CODE END Private defines */

#ifdef __cplusplus
 extern "C" {
#endif
void _Error_Handler(char *, int);

#define Error_Handler() _Error_Handler(__FILE__, __LINE__)
#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
