#include "TM4C123.h"
#include <stdint.h>
#include <stdbool.h>

void UART_init(void);
void UART_write(uint8_t *data, const uint32_t length);
void UART_write_byte(uint8_t data);
uint32_t UART_read(uint8_t *data, const uint32_t length);
uint8_t UART_read_byte(uint8_t *data);
bool UART_data_available(void);
