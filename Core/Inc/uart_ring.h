#ifndef UARTRINGBUFFER_H
#define UARTRINGBUFFER_H

#include <stm32f7xx_hal.h>

#define UART_BUFFER_SIZE 1024

typedef struct
{
  unsigned char buffer[UART_BUFFER_SIZE];
  volatile unsigned int head;
  volatile unsigned int tail;
} ring_buffer;


void ringbuf_init(UART_HandleTypeDef *huart);
int uart_read(void);
void uart_write(int c);
void uart_send_string(char *s);
int uart_is_data_available();
void uart_flush (void);
int uart_peek();
int uart_wait_for(char** cases, uint8_t size, uint32_t timeout);
int uart_wait_until(char* buffer, size_t* buffer_size, char** cases, uint8_t size, uint32_t timeout);
size_t uart_get_string(char buffer[], size_t size, uint32_t timeout);
long long get_string_between(char* str, char* start_str, char* end_str, char buffer[], uint32_t first);

// !!! Put it in interrupt !!!
void uart_isr(UART_HandleTypeDef *m_puart);

#endif
