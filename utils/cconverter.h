#ifndef DLP_UTILS_CONVERTER_H_
#define DLP_UTILS_CONVERTER_H_

#include <string>
#include <stdint.h>
void u322u16(const uint32_t &u32,uint16_t *u16);
uint32_t u162u32(const uint16_t *u16);

double u162d16(const uint16_t *value);

double u162d32(const uint16_t *value);
void d322u16(const double &d32,uint16_t *u16);

double u162t32(const uint16_t *time);

std::string pin2str(const uint16_t &pin_addr);


#include "../dlp/dlpalgorithm.h"
float division2angle(STEPMOTORDIVISION &division);
uint8_t division2ratio(STEPMOTORDIVISION &division);
STEPMOTORDIVISION ratio2division(uint8_t ratio);

#endif // DLP_UTILS_CONVERTER_H_
