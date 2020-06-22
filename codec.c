#include <msp430.h>

/*
 * CODEC mode control using SPI
 *
 * Author: Aditya Thagarthi Arun
 * Date created: 2/26/20
 * Date Modified: 2/28/20
 *
 */

//3 wire master to slave communication- use as example for mode control for CODEC

//
//                   MSP430FR5994
//                 -----------------
//            /|\ |              XIN|-
//             |  |                 |  32KHz Crystal
//             ---|RST          XOUT|-
//                |                 |
//                |             P5.0|-> Data Out (UCB1SIMO)-> MD codec
//                |                 |
//                |             P5.1|<- DATA In (UCB1SOMI) (Not required)
//                |                 |
//                |             P5.2|-> Serial Clock Out-> MC codec
//                |                 |
//                |             P5.3|-> CS/ strobe pulse-> ML codec

volatile unsigned char RXData = 0;
volatile unsigned char TXData;
volatile unsigned short TXdatafull= 0x0F100F300;//values to mute r0 and r1
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

    // Configure GPIO
    P5SEL1 &= ~(BIT0 | BIT1 | BIT2 | BIT3);        // USCI_B1 SCLK, MOSI, and MISO pin
    P5SEL0 |= (BIT0 | BIT1 | BIT2);
    PJSEL0 |= BIT4 | BIT5;                  // For XT1
    P5DIR |= 0x08; //set P5.3 to output direction


    // Disable the GPIO power-on default high-impedance mode to activate
    // previously configured port settings
    PM5CTL0 &= ~LOCKLPM5;

    // XT1 Setup
    CSCTL0_H = CSKEY_H;                     // Unlock CS registers
    CSCTL1 = DCOFSEL_0;                     // Set DCO to 1MHz
    CSCTL2 = SELA__LFXTCLK | SELS__DCOCLK | SELM__DCOCLK;
    CSCTL3 = DIVA__1 | DIVS__1 | DIVM__1;   // set all dividers
    CSCTL4 &= ~LFXTOFF;
    do
    {
        CSCTL5 &= ~LFXTOFFG;                // Clear XT1 fault flag
        SFRIFG1 &= ~OFIFG;
    } while (SFRIFG1 & OFIFG);              // Test oscillator fault flag
    CSCTL0_H = 0;                           // Lock CS registers

    // Configure USCI_B1 for SPI operation
    UCB1CTLW0 = UCSWRST;                    // **Put state machine in reset**
    UCB1CTLW0 |= UCMST | UCSYNC | UCMSB; // 3-pin, 8-bit SPI master//| UCCKPL
    UCB1CTLW0 &= ~(UCCKPL);// clock polarity has to be low when idle for the trickery to work
                                            // Clock polarity high, MSB
    UCB1CTLW0 |= UCSSEL__ACLK;              // ACLK
    UCB1BRW = 0x02;                         // /2
    //UCB1MCTLW = 0;                          // No modulation
    UCB1CTLW0 &= ~UCSWRST;                  // **Initialize USCI state machine**
    UCB1IE |= UCRXIE;                       // Enable USCI_B1 RX interrupt

    int counter = 0;

    //int i=0;

    for(counter=0; counter<4; counter++)
    {
        P5OUT |= 0x08;
        UCB1IE |= UCTXIE;
        __bis_SR_register(LPM0_bits | GIE); // CPU off, enable interrupts
        //__delay_cycles(1000);               // Delay before next transmission

        TXData = 0xFF & (TXdatafull >> ((3-counter)*8));
        counter++;

        if(counter % 2 != 0)
        {
            P5OUT &= 0xF7;//turn off cs after sending 16 bits
            __delay_cycles(1000);//delay before next register
        }
    }

//    while(1)
//    {
//        P5OUT |= 0x08;
//                UCB1IE |= UCTXIE;
//                __bis_SR_register(LPM0_bits | GIE); // CPU off, enable interrupts
//                //__delay_cycles(1000);               // Delay before next transmission
//
//                TXData = 0xFF & (TXdatafull >> ((counter % 2)*8));
//                counter++;
//                if(counter == 100)
//                {
//                    counter = 0;
//                }
//                if(counter % 2 != 0)
//                {
//                    P5OUT &= 0xF7;//turn off cs after sending 16 bits
//                }
//    }

    while(1){}
}

#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=EUSCI_B1_VECTOR
__interrupt void USCI_B1_ISR(void)
#elif defined(__GNUC__)
void __attribute__ ((interrupt(EUSCI_B1_VECTOR))) USCI_B1_ISR (void)
#else
#error Compiler not supported!
#endif
{
    switch(__even_in_range(UCB1IV, USCI_SPI_UCTXIFG))
    {
        case USCI_NONE: break;

        case USCI_SPI_UCRXIFG:
            RXData = UCB1RXBUF;
            UCB1IFG &= ~UCRXIFG;
            __bic_SR_register_on_exit(LPM0_bits); // Wake up to setup next TX
            break;

        case USCI_SPI_UCTXIFG:
            UCB1TXBUF = TXData;                   // Transmit characters
            UCB1IE &= ~UCTXIE;
            break;
        default: break;
    }
}
