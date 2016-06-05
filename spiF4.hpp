/**
 * @file spiF4.hpp
 * @brief STM32L1 SPI class.
 * @date June 2016
 * @author Robert Beam
 *
 * Class for communicating with other SPI devices using the STM32F4 controller.
 * Tested against an STM32F429 discovery board (STM32F429ZI).
 */

#ifndef SPIF4_HPP_
#define SPIF4_HPP_

#include "spibase.hpp"

/** STM32L1 SPI class */
class SPIF4 : public SPIBase
{
  /** @addtogroup SPI
   * @{
   */

public:
  /**
   * SPI constructor.
   *
   * @param spi SPI interface (SPI1, SPI2, ...) which should be used
   */
  SPIF4(SPI_TypeDef *spi) : SPIBase(spi) { };

  virtual ~SPIF4() { };

  virtual bool init();

  virtual void deinit();

  virtual uint16_t transfer(uint16_t data);

  virtual void select();

  virtual void unselect();

protected:
  virtual bool initClock();

  /** @}
   *
   */
};

#endif /* SPIL1_HPP_ */
