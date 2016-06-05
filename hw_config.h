/**
 * @file hw_config.h
 *
 * @brief HAL configuration
 * @date January 2015
 * @author André Heßling
 *
 * Include the header files that are needed for the controller.
 */
/**
 * @file hw_config.h
 *
 * @brief HAL configuration
 * @date May 2016
 * @author Robert Beam
 *
 * Add support to select STM32 F3 HAL header.
 */

#ifndef HW_CONFIG_H_
#define HW_CONFIG_H_

#if defined(LIBRFM69_STM32_USE_STM32F3)
  #include <stm32f30x.h>
#else
  #include "stm32l1xx.h"
#endif

#endif /* HW_CONFIG_H_ */
