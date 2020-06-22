/* --COPYRIGHT--,BSD_EX
 * Copyright (c) 2015, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *******************************************************************************
 *
 *                       MSP430 CODE EXAMPLE DISCLAIMER
 *
 * MSP430 code examples are self-contained low-level programs that typically
 * demonstrate a single peripheral function or device feature in a highly
 * concise manner. For this the code may rely on the device's power-on default
 * register values and settings such as the clock configuration and care must
 * be taken when combining code from several examples to avoid potential side
 * effects. Also see www.ti.com/grace for a GUI- and www.ti.com/msp430ware
 * for an API functional library-approach to peripheral configuration.
 *
 * --/COPYRIGHT--*/
//******************************************************************************
//  MSP430FR5x9x Demo - eUSCI_B2 I2C Master RX multiple bytes from MSP430 Slave
//
//  Description: This demo connects two MSP430's via the I2C bus. The master
//  reads 5 bytes from the slave. This is the MASTER CODE. The data from the slave
//  transmitter begins at 0 and increments with each transfer.
//  The USCI_B2 RX interrupt is used to know when new data has been received.
//  ACLK = n/a, MCLK = SMCLK = BRCLK =  DCO = 1MHz
//
//    *****used with "MSP430FR599x_eusciB2_i2c_11.c"****
//
//                                /|\  /|\
//               MSP430FR5994     10k  10k     MSP430FR5994
//                   slave         |    |        master
//             -----------------   |    |   -----------------
//           -|XIN  P7.0/UCB2SDA|<-|----+->|P7.0/UCB2SDA  XIN|-
//            |                 |  |       |                 | 32kHz
//           -|XOUT             |  |       |             XOUT|-
//            |     P7.1/UCB2SCL|<-+------>|P7.1/UCB2SCL     |
//            |                 |          |             P1.0|--> LED
//
//   William Goh
//   Texas Instruments Inc.
//   October 2015
//   Built with IAR Embedded Workbench V6.30 & Code Composer Studio V6.1
//******************************************************************************
#include <msp430.h>

//http://www.ti.com/product/MSP430FR5994/toolssoftware#softTools

unsigned char RXData;
unsigned char TXData;
int x;
int counter;

int main(void)
{
    TXData = 0x32;
    WDTCTL = WDTPW | WDTPW | WDTSSEL__SMCLK | WDTTMSEL | WDTCNTCL | WDTIS__32K;

    // Configure GPIO
    P1OUT &= ~BIT0;                         // Clear P1.0 output latch
    P1DIR |= BIT0;                          // For LED
    P7SEL0 |= BIT0 | BIT1;
    P7SEL1 &= ~(BIT0 | BIT1);

    P3DIR |= BIT0;
    P3OUT &= ~BIT0;


    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_6;                     // Set DCO = 8MHz
    CSCTL2 = SELA__VLOCLK | SELS__DCOCLK | SELM__DCOCLK; // Set ACLK = VLO, MCLK = DCO
    CSCTL3 = DIVA__1 | DIVS__8 | DIVM__8;   // Set all dividers
    CSCTL0_H = 0;



    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;


    // Configure USCI_B2 for I2C mode
    UCB2CTLW0 |= UCSWRST;                   // Software reset enabled
    UCB2CTLW0 |= UCMODE_3 | UCMST | UCSYNC | UCTR | UCTXACK; // I2C mode, Master mode, sync, transmitter
    UCB2CTLW1 |= UCASTP_2 | UCSTPNACK | UCSWACK;                  // Automatic stop generated
                                            // after UCB2TBCNT is reached

    //UCB2I2COA0 |= UCGCEN;               // CLOCK SHIT
    UCB2BRW = 0x24;                       // baudrate = SMCLK / 30; SMCLK is 16 MHz
    UCB2TBCNT = 0x000C;                     // number of bytes to be received
    UCB2I2CSA = 0x0070;                     // Slave address



    UCB2CTLW0 &= ~UCSWRST;

    UCB2IE |= UCNACKIE | UCSTTIE; //UCTXIE | UCRXIE | UCTXIE0 | UCRXIE0;



    //UCB2TXBUF = TXData;

    x = 0;
    //UCB2CTL1 |= UCTR | UCTXSTT;                // I2C start condition

    while(x+5 > 0) {
        __delay_cycles(5000);

        while (UCB2CTL1 & UCTXSTP);
        UCB2CTL1 |= UCTXSTT;
        __delay_cycles(5000);

        UCB2TXBUF = 0x00;
        __delay_cycles(5000);

        UCB2TXBUF = 0x18;
        __delay_cycles(5000);

        UCB2TXBUF = 0x02;
        __delay_cycles(5000);

        UCB2CTL1 |= UCTXSTP;
        x--;
    }


    x = 2000;
    counter = 0;

    SFRIE1 |= WDTIE;
    __bis_SR_register(LPM0_bits + GIE);     // Enter LPM0, enable interrupts
    __no_operation();                       // For debugger
}

// Watchdog Timer interrupt service routine
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(WDT_VECTOR))) WDT_ISR (void)
#else
#error Compiler not supported!
#endif
{
    while (UCB2CTL1 & UCTXSTP);

    UCB2CTL1 |= UCTR;
    UCB2CTL1 |= UCTXSTT;
    __delay_cycles(5000);

    UCB2TXBUF = 0x00;
    __delay_cycles(5000);

    UCB2CTL1 &= ~UCTR;
    __delay_cycles(5000);

    UCB2CTL1 |= UCTXSTT;

    __delay_cycles(5000);


    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);
    x = RXData; // voltage value 1 (little)

    RXData = UCB2RXBUF;
    __delay_cycles(5000);
    x = x + ((int)RXData)*16*16; // voltage value 2 (big)

    RXData = UCB2RXBUF;
    __delay_cycles(5000);

    RXData = UCB2RXBUF;
    __delay_cycles(5000);



    UCB2CTL1 |= UCTXSTP;
    UCB2CTL1 |= UCTXSTT;


    __delay_cycles(100000);


    if(x < 1435){
        if(counter == 1) {
            P3OUT |= BIT0;
            counter = 0;
        } else {
            counter += 1;
        }
    }
    else {
        P3OUT &= ~BIT0;
        counter = 0;
    }
}

/*
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector = EUSCI_B2_VECTOR
__interrupt void USCI_B2_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(EUSCI_B2_VECTOR))) USCI_B2_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(UCB2IV, USCI_I2C_UCBIT9IFG))
    {
        case USCI_NONE:
            break;     // Vector 0: No interrupts
        case USCI_I2C_UCALIFG:   break;     // Vector 2: ALIFG
        case USCI_I2C_UCNACKIFG:            // Vector 4: NACKIFG
            UCB2CTL1 |= UCTXSTP;     // I2C start condition
            __bic_SR_register_on_exit(LPM0_bits);

            break;
        case USCI_I2C_UCSTTIFG:
            __bic_SR_register_on_exit(LPM0_bits);
            break;     // Vector 6: STTIFG
        case USCI_I2C_UCSTPIFG:
            //while (UCB2CTL1 & UCTXSTP);
            __bic_SR_register_on_exit(LPM0_bits);
            break;     // Vector 8: STPIFG
        case USCI_I2C_UCRXIFG3:  break;     // Vector 10: RXIFG3
        case USCI_I2C_UCTXIFG3:  break;     // Vector 12: TXIFG3
        case USCI_I2C_UCRXIFG2:  break;     // Vector 14: RXIFG2
        case USCI_I2C_UCTXIFG2:  break;     // Vector 16: TXIFG2
        case USCI_I2C_UCRXIFG1:  break;     // Vector 18: RXIFG1
        case USCI_I2C_UCTXIFG1:  break;     // Vector 20: TXIFG1
        case USCI_I2C_UCRXIFG0:             // Vector 22: RXIFG0
            UCB2CTL1 |= TXData;
            break;
        case USCI_I2C_UCTXIFG0:

            //__bic_SR_register_on_exit(LPM0_bits);
            UCB2TXBUF = TXData;
            __bic_SR_register_on_exit(LPM0_bits);
            break;     // Vector 24: TXIFG0
        case USCI_I2C_UCBCNTIFG:            // Vector 26: BCNTIFG
            P1OUT ^= BIT0;                  // Toggle LED on P1.0
            break;
        case USCI_I2C_UCCLTOIFG: UCB2CTL1 |= UCTXSTP; break;     // Vector 28: clock low timeout
        case USCI_I2C_UCBIT9IFG: UCB2CTL1 |= UCTXSTP; break;     // Vector 30: 9th bit
        default: break;
    }
}*/
