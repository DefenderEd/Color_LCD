/*
 * Bafang LCD 850C firmware
 *
 * Copyright (C) Casainho, 2018.
 *
 * Released under the GPL License, Version 3
 */

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stdio.h"

#include "pins.h"
#include "UTFT-STM8S/UTFT.h"

void lcd_backlight (uint32_t ui32_state);

void lcd_init (void)
{
  static uint16_t ui16_reg_value;
  uint8_t ui8_i;

  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = LCD_BACKLIGHT__PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_BACKLIGHT__PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_READ__PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_READ__PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_RESET__PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_RESET__PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_COMMAND_DATA__PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_COMMAND_DATA__PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_CHIP_SELECT__PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_CHIP_SELECT__PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = LCD_WRITE__PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(LCD_WRITE__PORT, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = 0xffff;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  // these pins must be at 1 logic level (original firmware does that)
  GPIO_SetBits(LCD_READ__PORT, LCD_READ__PIN);
  GPIO_SetBits(LCD_RESET__PORT, LCD_RESET__PIN);

  // enable backlight
  lcd_backlight (1);

  UTFT ();
  UTFT_InitLCD ();

  //  while (1)
  //  {
//      for (ui8_i = 0; ui8_i < 255; ui8_i++)
//      {
//        ui16_reg_value = UTFT_read_reg_0 (ui8_i);
//      }
  //  }
}

void lcd_backlight (uint32_t ui32_state)
{
  if (ui32_state)
  {
    GPIO_SetBits(LCD_BACKLIGHT__PORT, LCD_BACKLIGHT__PIN);
  }
  else
  {
    GPIO_ResetBits(LCD_BACKLIGHT__PORT, LCD_BACKLIGHT__PIN);
  }
}
