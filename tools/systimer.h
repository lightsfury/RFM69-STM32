#ifndef RFM69_STM32_TOOLS_SYSTIMER_H_
#define RFM69_STM32_TOOLS_SYSTIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

void delay_ms(uint32_t ms);

uint32_t mstimer_get();

#ifdef __cplusplus
};
#endif

#endif // RFM69_STM32_TOOLS_SYSTIMER_H_
