#include <string.h>
#include <uart_ring.h>

/**** define the UART you are using  ****/

UART_HandleTypeDef* esp_uart;

/****************=======================>>>>>>>>>>> NO CHANGES AFTER THIS =======================>>>>>>>>>>>**********************/


ring_buffer rx_buffer = { { 0 }, 0, 0};
ring_buffer tx_buffer = { { 0 }, 0, 0};

ring_buffer *_rx_buffer;
ring_buffer *_tx_buffer;

void store_char(unsigned char c, ring_buffer *buffer);


void ringbuf_init(UART_HandleTypeDef *huart)
{
  esp_uart = huart;

  _rx_buffer = &rx_buffer;
  _tx_buffer = &tx_buffer;

  /* Enable the UART Error Interrupt: (Frame error, noise error, overrun error) */
  __HAL_UART_ENABLE_IT(esp_uart, UART_IT_ERR);

  /* Enable the UART Data Register not empty Interrupt */
  __HAL_UART_ENABLE_IT(esp_uart, UART_IT_RXNE);
}


void store_char(unsigned char c, ring_buffer *buffer)
{
  int i = (unsigned int)(buffer->head + 1) % UART_BUFFER_SIZE;

  // if we should be storing the received character into the location
  // just before the tail (meaning that the head would advance to the
  // current location of the tail), we're about to overflow the buffer
  // and so we don't write the character or advance the head.
  if(i != buffer->tail) {
    buffer->buffer[buffer->head] = c;
    buffer->head = i;
  }
}


int uart_read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if(_rx_buffer->head == _rx_buffer->tail)
  {
    return -1;
  }
  else
  {
    unsigned char c = _rx_buffer->buffer[_rx_buffer->tail];
    _rx_buffer->tail = (unsigned int)(_rx_buffer->tail + 1) % UART_BUFFER_SIZE;
    return c;
  }
}

void uart_write(int c)
{
	if (c>=0)
	{
		int i = (_tx_buffer->head + 1) % UART_BUFFER_SIZE;

		// If the output buffer is full, there's nothing for it other than to
		// wait for the interrupt handler to empty it a bit
		// ???: return 0 here instead?
		while (i == _tx_buffer->tail);

		_tx_buffer->buffer[_tx_buffer->head] = (uint8_t)c;
		_tx_buffer->head = i;

		__HAL_UART_ENABLE_IT(esp_uart, UART_IT_TXE); // Enable UART transmission interrupt
	}
}

int uart_is_data_available()
{
  return (uint16_t)(UART_BUFFER_SIZE + _rx_buffer->head - _rx_buffer->tail) % UART_BUFFER_SIZE;
}

void uart_send_string(char *s)
{
	while(*s)
		uart_write(*s++);
}


void uart_flush()
{
	memset(_rx_buffer->buffer,'\0', UART_BUFFER_SIZE);
	_rx_buffer->head = 0;
}


int uart_peek()
{
  if(_rx_buffer->head == _rx_buffer->tail)
  {
    return -1;
  }
  else
  {
    return _rx_buffer->buffer[_rx_buffer->tail];
  }
}


int uart_wait_for(char** cases, uint8_t size, uint32_t timeout)
{

	size_t lens[size];
	for(uint8_t i = 0; i < size; i++)
		lens[i] = strlen(cases[i]);

	uint8_t case_ctrs[size];
	for(uint8_t i = 0; i < size; i++)
		case_ctrs[i] = 0;

	uint32_t last = HAL_GetTick();
	while(!timeout || (HAL_GetTick() - last < timeout))
	{
		for(uint8_t i = 0; i < size; i++)
		{
			char* str = cases[i];

			while(!uart_is_data_available())
				if(timeout && (HAL_GetTick() - last >= timeout))
					return -1; // Timeout
			if(uart_peek() == str[case_ctrs[i]])
			{
				case_ctrs[i]++;

				if (case_ctrs[i] == lens[i])
				{
					uart_read();
					return i;
				}
			}
			else // Chain is over
			{
				case_ctrs[i] = 0;
			}
		}

		uart_read(); // Next char
	}

	return -1; // Timeout
}


int uart_wait_until(char* buffer, size_t* buffer_size, char** cases, uint8_t size, uint32_t timeout)
{
	size_t buff_ctr = 0;

	size_t lens[size];
	for(uint8_t i = 0; i < size; i++)
		lens[i] = strlen(cases[i]);

	uint8_t case_ctrs[size];
	for(uint8_t i = 0; i < size; i++)
		case_ctrs[i] = 0;

	uint32_t last = HAL_GetTick();
	while(!timeout || (HAL_GetTick() - last < timeout))
	{
		for(uint8_t i = 0; i < size; i++)
		{
			char* str = cases[i];

			while(!uart_is_data_available())
				if(timeout && (HAL_GetTick() - last >= timeout))
					//printf("Trouble!\r\n");
					return -1; // Timeout
			if(uart_peek() == str[case_ctrs[i]])
			{
				case_ctrs[i]++;

				if (case_ctrs[i] == lens[i])
				{
					buffer[buff_ctr++] = uart_read(); // Final char
					buffer[buff_ctr] = '\0';
					*buffer_size = buff_ctr;
					return i;
				}
			}
			else // Chain is over
			{
				case_ctrs[i] = 0;
			}
		}

		if(uart_peek())
		{
			buffer[buff_ctr] = uart_read(); // Next char
			buff_ctr++;
		}
		else
			uart_read();
	}

	return -1; // Timeout
}


long long get_string_between(char* str, char* start_str, char* end_str, char buffer[], uint32_t first)
{
	char* start = strstr(str+first, start_str);
	char* end = strstr(str+first, end_str);

	if(!start || !end || end < start)
		return -1;

	size_t size = end - start - strlen(start_str);

	strncpy(buffer, start + strlen(start_str), size);
	buffer[size] = '\0';

	return start - str + size;
}


size_t uart_get_string(char buffer[], size_t size, uint32_t timeout)
{
	uint32_t last = HAL_GetTick();
	for(size_t i = 0; i < size; i++)
	{
		while(!uart_is_data_available())
			if(timeout && (HAL_GetTick() - last >= timeout))
				return (size - i); // Timeout

		buffer[i] = (char) uart_read();
	}
	buffer[size] = '\0';

	return 0;
}


void uart_isr (UART_HandleTypeDef *huart)
{
	uint32_t isrflags   = READ_REG(huart->Instance->ISR);
	uint32_t cr1its     = READ_REG(huart->Instance->CR1);

	/* if DR is not empty and the Rx Int is enabled */
	if (((isrflags & USART_ISR_RXNE) != RESET) && ((cr1its & USART_CR1_RXNEIE) != RESET))
	{
		/******************
		*  @note   PE (Parity error), FE (Framing error), NE (Noise error), ORE (Overrun
		*          error) and IDLE (Idle line detected) flags are cleared by software
		*          sequence: a read operation to USART_SR register followed by a read
		*          operation to USART_DR register.
		* @note   RXNE flag can be also cleared by a read to the USART_DR register.
		* @note   TC flag can be also cleared by software sequence: a read operation to
		*          USART_SR register followed by a write operation to USART_DR register.
		* @note   TXE flag is cleared only by a write to the USART_DR register.
		*********************/
		huart->Instance->ISR;                       /* Read status register */
		unsigned char c = huart->Instance->RDR;     /* Read data register */
		store_char (c, _rx_buffer);  // store data in buffer
		return;
	}

	/*If interrupt is caused due to Transmit Data Register Empty */
	if (((isrflags & USART_ISR_TXE) != RESET) && ((cr1its & USART_CR1_TXEIE) != RESET))
	{
		if(tx_buffer.head == tx_buffer.tail)
		{
			// Buffer empty, so disable interrupts
			__HAL_UART_DISABLE_IT(huart, UART_IT_TXE);
		}
		else
		{
			// There is more data in the output buffer. Send the next byte
			unsigned char c = tx_buffer.buffer[tx_buffer.tail];
			tx_buffer.tail = (tx_buffer.tail + 1) % UART_BUFFER_SIZE;
			huart->Instance->ISR;
			huart->Instance->TDR = c;
		}
		return;
	}
}
