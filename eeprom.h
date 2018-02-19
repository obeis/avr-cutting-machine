#ifndef _EEPROM_H_
#define _EEPROM_H_

void EEPROM_write(uint16_t uiAddress, uint8_t ucData);
uint8_t EEPROM_read(uint16_t uiAddress);

#endif
