Through these pins, serial data is transmitted and received in normal USART mode as
frames comprising:
• An Idle Line prior to transmission or reception
• A start bit
• A data word (8 or 9 bits) least significant bit first
• 0.5,1, 1.5, 2 Stop bits indicating that the frame is complete
• This interface uses a fractional baud rate generator - with a 12-bit mantissa and 4-bit
fraction
• A status register (USART_SR)
• Data register (USART_DR)
• A baud rate register (USART_BRR) - 12-bit mantissa and 4-bit fraction.
• A Guardtime Register (USART_GTPR)


CK: Transmitter clock output
CTS: Clear To Send blocks the data transmission at the end of the current transfer
when high
RTS: Request to send indicates that the USART is ready to receive a data (when low).


When the transmitter is enabled and nothing is to be transmitted, the TX pin is at high level.
The TX pin is in low state during the start bit. It is in high state during the stop bit.


An Idle character is interpreted as an entire frame of “1”s followed by the start bit of the
next frame which contains data (The number of “1” ‘s will include the number of stop bits).
A Break character is interpreted on receiving “0”s for a frame period. At the end of the
break frame the transmitter inserts either 1 or 2 stop bits (logic “1” bit) to acknowledge the
start bit.


Transmission and reception are driven by a common baud rate generator, the clock for each
is generated when the enable bit is set respectively for the transmitter and receiver.


/***********************************************************************************************
M bit in the USART_CR1 register.

When the transmit enable bit (TE) is set, the data in the transmit shift register is output on
	the TX pin and the corresponding clock pulses are output on the CK pin. 
	An idle frame will be sent after the TE bit is enabled

Transmister: 	data shifts out least significant bit first on the TX pin. 
				USART_DR register consists of a buffer (TDR) between the internal bus and the
				transmit shift register.
				Procedure:
					1. Enable the USART by writing the UE bit in USART_CR1 register to 1.
					2. Program the M bit in USART_CR1 to define the word length.
					3. Program the number of stop bits in USART_CR2.
					4. Select DMA enable (DMAT) in USART_CR3 if Multi buffer Communication is to take
					place. Configure the DMA register as explained in multibuffer communication.
					5. Select the desired baud rate using the USART_BRR register.
					6. Set the TE bit in USART_CR1 to send an idle frame as first transmission.
					6.1 Wait TXE empty
					7. Write the data to send in the USART_DR register (this clears the TXE bit). Repeat this
					for each data to be transmitted in case of single buffer.
					8. After writing the last data into the USART_DR register, wait until TC=1. This indicates
					that the transmission of the last frame is complete. This is required for instance when
					the USART is disabled or enters the Halt mode to avoid corrupting the last
					transmission.
				
****************************************************************************************************/



/*========================================= RECEIVE DATA =============================================*/
In the USART, the start bit is detected when a specific sequence of samples is recognized.
This sequence is: 1 1 1 0 X 0 X 0 X 0 0 0 0.

The start bit is confirmed (RXNE flag set, interrupt generated if RXNEIE=1) if the 3 sampled
bits are at 0 (first sampling on the 3rd, 5th and 7th bits finds the 3 bits at 0 and second
sampling on the 8th, 9th and 10th bits also finds the 3 bits at 0). the NE noise
flag is set if, for both samplings, at least 2 out of the 3 sampled bits are at 0 (sampling on the
3rd, 5th and 7th bits and sampling on the 8th, 9th and 10th bits). If this condition is not met,
the start detection aborts and the receiver returns to the idle state (no flag is set)





/*===================================================================================================*/