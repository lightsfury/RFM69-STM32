/**
 * @file spiL1.cpp
 * @brief STM32L1 SPI class.
 * @date January 2015
 * @author André Heßling
 *
 * Class for communicating with other SPI devices using the STM32L1 controller.
 */
/**
 * @file spiF4.cpp
 * @brief STM32F3 SPI class.
 * @date June 2016
 * @author Robert Beam
 *
 * Class for communicating with other SPI devices using the STM32F4 controller.
 */

/** @addtogroup SPI
 * @{
 */
#include "SPIF4.hpp"

/**
 * Initialize the peripheral clocks needed for SPI transfers.
 *
 * @return true if OK, else false.
 */
bool SPIF4::initClock()
{
  bool clockEnabled = true;

  // init clocks
  if (_spi == SPI1)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
  }
  else if (_spi == SPI2)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2, ENABLE);
  }
  else if (_spi == SPI3)
  {
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI3, ENABLE);
  }
  else if (_spi == SPI4)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI4, ENABLE);
  }
  else if (_spi == SPI5)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI5, ENABLE);
  }
  else if (_spi == SPI6)
  {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI6, ENABLE);
  }
  else
  {
    clockEnabled = false;
  }

  return clockEnabled;
}

/**
 * Init SPI peripheral.
 *
 * @return true if OK, else false
 */
bool SPIF4::init()
{
  // deinit before init
  if (true == _init)
    deinit();

  // enable peripheral clock
  if (false == initClock())
    return false;

  // configure SPI
  SPI_InitTypeDef SPI_InitStructure;
  SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
  SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
  SPI_InitStructure.SPI_DataSize = (_bits == 8) ? SPI_DataSize_8b : SPI_DataSize_16b;
  SPI_InitStructure.SPI_CPOL = _cpol ? SPI_CPOL_High : SPI_CPOL_Low;
  SPI_InitStructure.SPI_CPHA = _cpha ? SPI_CPHA_2Edge : SPI_CPHA_1Edge;
  SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
  SPI_InitStructure.SPI_BaudRatePrescaler = _prescaler;
  SPI_InitStructure.SPI_FirstBit = _firstBitLSB ? SPI_FirstBit_LSB : SPI_FirstBit_MSB;
  SPI_InitStructure.SPI_CRCPolynomial = 7;
  SPI_Init(_spi, &SPI_InitStructure);

  // enable SPI
  SPI_Cmd(_spi, ENABLE);

  _init = true;

  return _init;
}

/**
 * Deinit the SPI peripheral.
 */
void SPIF4::deinit()
{
  // fixme: check if transfer is pending
  SPI_I2S_DeInit(_spi);

  _init = false;
}

/**
 * SPI read/write.
 *
 * Depending on the number of bits per transfer unit,
 * 8 or 16 bits are read/written.
 *
 * @param data Data to be sent
 * @return Data received
 */
uint16_t SPIF4::transfer(uint16_t data)
{
  // truncate data if necessary
  if (8 == _bits)
    data &= 0xff;

  // SPI must be init'd
  if (false == _init)
    return 0;

  // wait for TX buffer empty (transfer finished)
  while ((_spi->SR & SPI_I2S_FLAG_TXE) == RESET);

  // transfer
  _spi->DR = data;
  //SPI_SendData8(_spi, data);

  // wait for RX buffer not empty (transfer finished)
  while ((_spi->SR & SPI_I2S_FLAG_RXNE) == RESET);
  //while (SPI_GetReceptionFIFOStatus(_spi) == SPI_ReceptionFIFOStatus_Empty);

  // get received data
  data = _spi->DR;
  //data = SPI_ReceiveData8(_spi);

  // truncate data if necessary
  if (8 == _bits)
    return data & 0xff;
  else
    return data;
}

/**
 * Select the device.
 *
 * Can be used if only one device shall be addressed.
 *
 * @note Can only be used if configureCS() has been called before.
 */
void SPIF4::select()
{
  if (_csGPIO != 0)
  {
      GPIO_SetBits(_csGPIO, _csPin);
  }
}

/**
 * Release the device.
 *
 * Can be used if only one device shall be addressed.
 *
 * @note Can only be used if configureCS() has been called before.
 */
void SPIF4::unselect()
{
  if (_csGPIO != 0)
  {
      GPIO_ResetBits(_csGPIO, _csPin);
  }
}

/** @}
 *
 */
