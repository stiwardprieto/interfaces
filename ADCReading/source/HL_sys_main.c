/** @file HL_sys_main.c 
*   @brief Application main file
*   @date 11-Dec-2018
*   @version 04.07.01
*
*   This file contains an empty main function,
*   which can be used for the application.
*/

/* 
* Copyright (C) 2009-2018 Texas Instruments Incorporated - www.ti.com  
* 
* 
*  Redistribution and use in source and binary forms, with or without 
*  modification, are permitted provided that the following conditions 
*  are met:
*
*    Redistributions of source code must retain the above copyright 
*    notice, this list of conditions and the following disclaimer.
*
*    Redistributions in binary form must reproduce the above copyright
*    notice, this list of conditions and the following disclaimer in the 
*    documentation and/or other materials provided with the   
*    distribution.
*
*    Neither the name of Texas Instruments Incorporated nor the names of
*    its contributors may be used to endorse or promote products derived
*    from this software without specific prior written permission.
*
*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* USER CODE BEGIN (0) */
#include "HL_sci.h"
#include "HL_adc.h"
#include "stdlib.h"
/* USER CODE END */

/* Include Files */

#include "HL_sys_common.h"

/* USER CODE BEGIN (1) */
char texto[50];
/* USER CODE END */

/** @fn void main(void)
*   @brief Application main function
*   @note This function is empty by default.
*
*   This function is called after startup.
*   The user can use this function to implement the application.
*/

/* USER CODE BEGIN (2) */
void delay_ms(uint32 reta)
{
    uint32  cont_, cont1_;
    for (cont_=0;cont_<reta;cont_++){
        for (cont1_=0;cont1_<27258;cont1_++);// delay 1ms
    }
}

void sci_send_text_const(const char *info){
    while(*info)     sciSendByte(sciREG1, *info++);
}
void sci_send_text(char *info)
{
    while(*info)     sciSendByte(sciREG1, *info++);
}
/* USER CODE END */

int main(void)
{
/* USER CODE BEGIN (3) */
    adcData_t adc_data;
    adcData_t *adc_data_ptr = &adc_data;
    unsigned int value,presion;
    char *NumberOfChars;

    sciInit();
    adcInit();
    sci_send_text_const("Iniciando lectura \r\n");
    adcStartConversion(adcREG1,adcGROUP1);
    while(1){
        while(!adcIsConversionComplete(adcREG1,adcGROUP1));
        adcGetData(adcREG1,1U,adc_data_ptr);
        value = (unsigned int)adc_data_ptr -> value;
        presion = value/0.0297 + 95/9;
        sprintf(texto,"Presion: %u \r\n",presion);
        sci_send_text(texto);
        adcStopConversion(adcREG1,adcGROUP1);
        delay_ms(1000);
    }
/* USER CODE END */

    return 0;
}


/* USER CODE BEGIN (4) */
/* USER CODE END */
