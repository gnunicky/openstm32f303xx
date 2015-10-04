/**
  ******************************************************************************
  * @file    ADC_Example/main.c 
  * @author  MCD Application Team
  * @version V1.1.0
  * @date    20-September-2012
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2012 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <stdio.h> 
#include <string.h>

/** @addtogroup STM32F3_Discovery_Peripheral_Examples
  * @{
  */

/** @addtogroup ADC_Example
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
__IO uint32_t UserButtonPressed = 0;
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint32_t TimingDelay = 0;
__IO uint32_t TimingCounter = 0;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
#define STU_SIZE 10

#define NAME_SIZE 100
#define CODE_SIZE 5
#define DEP_NUM 4

typedef struct _student_t
{
  char name[NAME_SIZE];
  char code[CODE_SIZE+1];
  int rights[DEP_NUM];
  int access_counter;
  char validity;
} student_t;

student_t students[STU_SIZE];
int position = 1; /* 0 ... DEP_NUM-1 */
char code[20];

void student_init(student_t *pstudent)
{
  memset(pstudent, 0, sizeof(student_t));
}
void student_set(student_t *pstudent, const char *name, const char *code, int dip1, int dip2, int dip3, int dip4)
{
  if (pstudent)
  {
    strcpy(pstudent->name, name);
    strcpy(pstudent->code, code);
    pstudent->rights[0] = dip1;
    pstudent->rights[1] = dip2;
    pstudent->rights[2] = dip3;
    pstudent->rights[3] = dip4;
    pstudent->access_counter = 0;
    pstudent->validity = 1;
  }
}
void idle_func()
{
  if ((TimingCounter % 1000) == 0)
  {
    STM_EVAL_LEDToggle(LED4);
  }
  TimingCounter++;
}
RCC_ClocksTypeDef RCC_Clocks;
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f30x.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f30x.c file
     */ 
  RCC_GetClocksFreq(&RCC_Clocks);

  /* Setup SysTick Timer for 1 ms interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000))
  { 
    /* Capture error */ 
    while (1)
    {
    }
  }
  
  /* Initialize LEDs and User Button available on STM32F3-Discovery board */
  STM_EVAL_LEDInit(LED3);
  STM_EVAL_LEDInit(LED4);
  STM_EVAL_LEDInit(LED5);
  STM_EVAL_LEDInit(LED6);
  STM_EVAL_LEDInit(LED7);
  STM_EVAL_LEDInit(LED8);
  STM_EVAL_LEDInit(LED9);
  STM_EVAL_LEDInit(LED10);
  
  STM_EVAL_PBInit(BUTTON_USER, BUTTON_MODE_EXTI); 

  for(int i=0;i<100;i++)
  {
    STM_EVAL_LEDToggle(LED10);
    Delay(100);
  }
  
  //reset all items
  memset(students, 0, sizeof(student_t) * STU_SIZE);
  
  //add students
  student_set(students+0, "Mario Rossi",         "A0001", 1,0,0,0);
  student_set(students+1, "Giuseppe Garibaldi",  "A0002", 1,1,0,0);
  student_set(students+2, "Giuseppe Mazzini",    "B0001", 0,1,1,0);
  student_set(students+3, "Paolo Consoli",       "B0002", 0,0,0,1);

  /* Infinite loop */
  while (1)
  {
    STM_EVAL_LEDOff(LED3);
    STM_EVAL_LEDOff(LED5);
    STM_EVAL_LEDOff(LED6);
    STM_EVAL_LEDOn(LED4);
    printf("Code student:\n");
    //get code
    scanf("%s", code);
    printf("Code student received %s\n", code);
    
    //search the student in the db
    student_t * pstudent = NULL;
    for(int i = 0; i < STU_SIZE; i++)
    {
      if (students[i].validity == 1 && strcmp(students[i].code, code) == 0)
      {
        pstudent = &students[i];;
        break;
      }
    }
    STM_EVAL_LEDOff(LED4);

    if (!pstudent)
    {
      STM_EVAL_LEDOn(LED3);
      printf("Invalid code student\n");
    }
    else if (pstudent->rights[position] == 0) 
    {
      STM_EVAL_LEDOn(LED5);
      printf("No access for students\n");
    }
    else
    {
      STM_EVAL_LEDOn(LED6);
      pstudent->access_counter++;
      printf("Open door for students %s code %s (%d)\n", pstudent->name, pstudent->code, pstudent->access_counter);
    }
    Delay(2000);
  }
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
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
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
