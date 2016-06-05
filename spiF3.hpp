/**
 * @file spiL1.hpp
 * @brief STM32L1 SPI class.
 * @date May 2016
 * @author Robert Beam
 *
 * Class for communicating with other SPI devices using the STM32F3 controller.
 * Tested against an STM32F3 discovery board (STM32F303VC).
 */

#ifndef SPIF3_HPP_
#define SPIF3_HPP_

#include "spibase.hpp"

/** STM32L1 SPI class */
class SPIF3 : public SPIBase
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
  SPIF3(SPI_TypeDef *spi) : SPIBase(spi) { };

  virtual ~SPIF3() { };

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
