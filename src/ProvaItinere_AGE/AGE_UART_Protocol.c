
/* Includes ------------------------------------------------------------------*/
#include "AGE_UART_Protocol.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void AGE_UART_PacketRecognize_It()
{
#warning AEG.15 PacketRecognize_It
  /*
  questa funzione e' chiamata all'interno dell'interrupt della uart1 
  e si preoccupa di conservare i byte in ingresso e quindi riconoscere un pacchetto valido
  */
}

void AGE_UART_Exec()
{
#warning AEG.16 AGE_UART_Exec`
  /*
  questa funzione dato un pacchetto lo interpreta e lo esegue
  */
}
