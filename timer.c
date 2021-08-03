#include "timer.h"


void Timer1BaseUnit( void ){
	/* enable clock timer1  72MHz */
	RCC->APB2ENR|= 0x01 << 11u;
	/* set prescaler */
	TIM1->PSC= 7200U - 1U; // clock is 10KHz==> 0.1ms
	/* set auto */
	TIM1->ARR= 100u; // counter count untill equal 100pulses will reload
	/* set repeat register */
	TIM1->RCR= 9u; // repeat 10 times: after counter reload 10 times then generate an update event
	/* set UG bit */
	//TIM1->EGR|= 0x01;
	/* enable interrupts */
	TIM1->DIER|= 0x01;
	/* enable interrupts in NVIC */
	NVIC->ISER[0]= 0x01 << 25u;
	/* reset counter */
	TIM1->CNT = 0;
	/* counter enable */
	TIM1->CR1|= 0x01;
}


/*
For example, to configure the upcounter to count in response to a rising edge on the TI2
input, use the following procedure:
1. Configure channel 2 to detect rising edges on the TI2 input by writing CC2S = ‘01’ in
the TIMx_CCMR1 register.
2. Configure the input filter duration by writing the IC2F[3:0] bits in the TIMx_CCMR1
register (if no filter is needed, keep IC2F=0000).
3. Select rising edge polarity by writing CC2P=0 in the TIMx_CCER register.
4. Configure the timer in external clock mode 1 by writing SMS=111 in the TIMx_SMCR
register.
5. Select TI2 as the trigger input source by writing TS=110 in the TIMx_SMCR register.
6. Enable the counter by writing CEN=1 in the TIMx_CR1 register.
*/
void EXT_CLK_MODE1( void ){
	/* enable clock timer1  72MHz */
	RCC->APB2ENR|= 0x01 << 11u;
	TIM1->CCMR1|= 0x01 << 8u;  // step 1
	TIM1->CCMR1|= 0x01 << 13u; // choose filter
	/* Bit 4 CC2E: Capture/Compare 2 output enable */
	TIM1->CCER |= 0x01 << 4u; // enable load value from counter into capture register
	TIM1->SMCR |= 0x07;       // step 4
	TIM1->SMCR |= 0x03 << 5u; // step 5
	/* reset counter */
	TIM1->CNT = 0;
	TIM1->CR1  |= 0x01;       // step 6
	/* extense mode */
	/* Bit 2 CC2IE: Capture/Compare 2 interrupt enable */
	TIM1->DIER |= 0x01 << 2u;
	/* enable interrupts in NVIC */
	NVIC->ISER[0] |= 0x01 << 27u;
	
}



/*
For example, to configure the upcounter to count each 2 rising edges on ETR, use the
following procedure:
1. As no filter is needed in this example, write ETF[3:0]=0000 in the TIMx_SMCR register.
2. Set the prescaler by writing ETPS[1:0]=01 in the TIMx_SMCR register
3. Select rising edge detection on the ETR pin by writing ETP=0 in the TIMx_SMCR
register
4. Enable external clock mode 2 by writing ECE=1 in the TIMx_SMCR register.
5. Enable the counter by writing CEN=1 in the TIMx_CR1 register.
The counter counts once each 2 ETR rising edges.
*/
void EXT_CLK_MODE2( void ){
	/* enable clock timer1  72MHz */
	RCC->APB2ENR|= 0x01 << 11u;
	/* filter */
	/* Bits 13:12 ETPS[1:0]: External trigger prescaler */
	TIM1->SMCR |= 0x01 << 12u;
	/* rising edge */
	/* Bit 14 ECE: External clock enable */
	TIM1->SMCR |= 0x01 << 14u;
	/* Bit 6 TIE: Trigger interrupt enable */
	TIM1->DIER |= 0x01 << 6u;
	/* reset counter */
	TIM1->CNT = 0;
	/* Enable CEN */
	TIM1->CR1 |= 0x01;
}



/*
The following example shows how to capture the counter value in TIMx_CCR1 when TI1
input rises. To do this, use the following procedure:
1 Select the active input: TIMx_CCR1 must be linked to the TI1 input, so write the CC1S
bits to 01 in the TIMx_CCMR1 register. As soon as CC1S becomes different from 00,
the channel is configured in input and the TIMx_CCR1 register becomes read-only.
2 Program the needed input filter duration with respect to the signal connected to the
timer (by programming ICxF bits in the TIMx_CCMRx register if the input is a TIx input).
Let’s imagine that, when toggling, the input signal is not stable during at must five
internal clock cycles. We must program a filter duration longer than these five clock
cycles. We can validate a transition on TI1 when 8 consecutive samples with the new
level have been detected (sampled at fDTS frequency). Then write IC1F bits to 0011 in
the TIMx_CCMR1 register.
3 Select the edge of the active transition on the TI1 channel by writing CC1P bit to 0 in
the TIMx_CCER register (rising edge in this case).
4 Program the input prescaler. In our example, we wish the capture to be performed at
each valid transition, so the prescaler is disabled (write IC1PS bits to ‘00’ in the
TIMx_CCMR1 register).
5 Enable capture from the counter into the capture register by setting the CC1E bit in the
TIMx_CCER register.
6 If needed, enable the related interrupt request by setting the CC1IE bit in the
TIMx_DIER register, and/or the DMA request by setting the CC1DE bit in the
TIMx_DIER register
*/

void TIM1_INP_CAPTURE( void ){
	/* enable clock timer1  72MHz */
	RCC->APB2ENR|= 0x01 << 11u;
	/* Bits 1:0 CC1S: Capture/Compare 1 Selection */
	TIM1->CCMR1 |= 0x01;
	/* Bits 7:4 IC1F[3:0]: Input capture 1 filter */
	TIM1->CCMR1 |= 0x03 << 4u; 
	/* SMCR config */
	TIM1->SMCR |= 0x01 << 4u;
	TIM1->SMCR |= 0x01 << 6u;
	TIM1->SMCR |= 7u;
	/* Bit 1 CC1P: Capture/Compare 1 output polarity */
	/* Bits 3:2 IC1PSC: Input capture 1 prescaler */
	/* Bit 0 CC1E: Capture/Compare 1 output enable */
	TIM1->CCER |= 0x01;
	/* reset counter */
	TIM1->CNT = 0;
	/* Enable CEN */
	TIM1->CR1 |= 0x01;
}





/*
	For example, user can measure the period (in TIMx_CCR1 register) and the duty cycle (in
TIMx_CCR2 register) of the PWM applied on TI1 using the following procedure (depending
on CK_INT frequency and prescaler value):
1/ Select the active input for TIMx_CCR1: write the CC1S bits to 01 in the TIMx_CCMR1
register (TI1 selected).
2/ Select the active polarity for TI1FP1 (used both for capture in TIMx_CCR1 and counter
clear): write the CC1P bit to ‘0’ (active on rising edge).
3/ Select the active input for TIMx_CCR2: write the CC2S bits to 10 in the TIMx_CCMR1
register (TI1 selected).
4/ Select the active polarity for TI1FP2 (used for capture in TIMx_CCR2): write the CC2P
bit to ‘1’ (active on falling edge).
5/ Select the valid trigger input: write the TS bits to 101 in the TIMx_SMCR register
(TI1FP1 selected).
6/ Configure the slave mode controller in reset mode: write the SMS bits to 100 in the
TIMx_SMCR register.
7 Enable the captures: write the CC1E and CC2E bits to ‘1’ in the TIMx_CCER register.
*/

void PWM_INPUT( void ){
	/* enable clock timer1  72MHz */
	RCC->APB2ENR|= 0x01 << 11u;
	/* config prescaler */
	TIM1->PSC= 7200u - 1u;
	/* Bits 1:0 CC1S: Capture/Compare 1 Selection: 	USE TI1 ON IC1 */
	TIM1->CCMR1 |= 0x01;
	/* Select the rising edge */
	/* Bits 9:8 CC2S: Capture/Compare 2 selection: USE TI1 ON IC2 */
	TIM1->CCMR1 |= 0x01 << 9;
	/* Bit 5 CC2P: Capture/Compare 2 output polarity: CHOOSE FALLING EDGE */
	TIM1->CCER |= 0x01 << 5u;
	/* Bits 6:4 TS[2:0]: Trigger selection: USE TIFP1 */
	TIM1->SMCR |= 0x05 << 4u;
	/* Bits 2:0 SMS: Slave mode selection */
	TIM1->SMCR |= 0x01 << 2u;
	/* Enabel CC1E AND CC2E */
	TIM1->CCER |= 0x11;
	/* reset counter */
	TIM1->CNT = 0;
	/* Enable CEN */
	TIM1->CR1 |= 0x01;
}



void PWM_A9(uint16_t nCounter, uint8_t dutyCycle ){
	/* TIM1_CH2 */
	/* enable clock timer1  72MHz */
	RCC->APB2ENR|= 0x01 << 11u;
	/* prescaler of counter */
	TIM1->PSC= 7200u - 1u; // 1 counter corresponding 0.1ms
	/* set freq */
	TIM1->ARR= nCounter;   // freq= 1/ ( nCounter * 0.1ms )
	/* set dutycycles */
	TIM1->CCR2= (uint16_t)(dutyCycle/100.0*nCounter);
	/* choose Pwm 1 */
	TIM1->CCMR1 |= 0x03 << 13u;
	/* Prescaler of CC2 */
	TIM1->CCMR1 |= 0x01 << 11u;
	/* Bit 7 ARPE: Auto-reload preload enable in CR1 */
	/* Bit 4 CC2E: Capture/Compare 2 output enable */
	/* Bit 6 CC2NE: Capture/Compare 2 complementary output enable */
	TIM1->CCER |= 0x05 << 4u;
	/* Bit 11 OSSR: Off-state selection for Run mode */
	TIM1->BDTR |= 0x01 << 11u;
	/* Bit 15 MOE: Main output enable */
	TIM1->BDTR |= 0x01 << 15u;
	/* before starting the counter, the user must initialize all the registers by setting the UG
   bit in the TIMx_EGR register. */
	TIM1->EGR |= 0x01;
	/* reset counter */
	TIM1->CNT = 0;
	/* enable counter */
	TIM1->CR1 |= 0x01;
}


/* Encoder interface */
void EncoderInterface( void ){
	/* enable clock timer1  72MHz */
	RCC->APB2ENR|= 0x01 << 11u;
	/* TI1FP1 mapped on TI1 */
	TIM1->CCMR1 |= 0x01;
	/* TI1FP1  non-inverted */
	/* TI1FP1 0011: fSAMPLING=fCK_INT, N=8 */
	TIM1->CCMR1 |= 0x03 << 3u;
	/* TI1FP2 mapped on TI2 */
	TIM1->CCMR1 |= 0x01 << 8u;
	/* TI1FP2 and non-inverted */
	/* TI1FP2 0011: fSAMPLING=fCK_INT, N=8 */
	TIM1->CCMR1 |= 0x03 << 12u;
	/* Bits 2:0 SMS: Slave mode selection */
	TIM1->SMCR |= 0x03; // encoder 3 mode
	/* DIR bit in the TIMx_CR1: count up*/
	/* configure TIMx_ARR before starting */
	TIM1->ARR= 59u;
	/* reset counter */
	TIM1->CNT = 0;
	/* Enable counter */
	TIM1->CR1 |= 0x01;

}

























