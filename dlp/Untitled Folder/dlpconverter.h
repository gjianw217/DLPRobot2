#ifndef DLP_COMMON_DLPCONVERTER_H_
#define DLP_COMMON_DLPCONVERTER_H_
void u322u16(const uint32_t &u32,uint16_t *u16);
uint32_t u162u32(const uint16_t *u16);
double u162d16(const uint16_t *value);
double u162d32(const uint16_t *value);
void d322u16(const double &d32,uint16_t *u16);
double u162t32(const uint16_t *time);
#endif//DLP_COMMON_DLPCONVERTER_H_