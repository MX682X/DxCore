/* UART3.cpp - Hardware serial library
 * This library is free software under LGPL 2.1. See License.md
 * for more information. This file is part of DxCore.
 *
 * Copyright (c) 2006 Nicholas Zambetti, Modified by
 * 11/23/2006 David A. Mellis, 9/20/2010 Mark Sproul,
 * 8/24/2012 Alarus, 12/3/2013 Matthijs Kooijman
 * unknown others 2013-2020, 2020-2021 Spence Konde
 */

#include "Arduino.h"
#include "UART.h"
#include "UART_private.h"

#if defined(USART3)
  ISR(USART3_TXC_vect) {
    uint8_t ctrla;
    while (USART3.STATUS & USART_RXCIF_bm) {
      ctrla = USART3.RXDATAL;
    }
    ctrla = USART3.CTRLA;
    ctrla |= USART_RXCIE_bm; // turn on receive complete
    ctrla &= ~USART_TXCIE_bm; // turn off transmit complete
    USART3.CTRLA = ctrla;
  }

  ISR(USART3_RXC_vect) {
    UartClass::_rx_complete_irq(Serial3);
  }

  ISR(USART3_DRE_vect) {
    UartClass::_tx_data_empty_irq(Serial3);
  }

  UartClass Serial3(&USART3, (uint8_t*)_usart3_pins, MUXCOUNT_USART3, HWSERIAL3_MUX_DEFAULT);
#endif  // HWSERIAL3
