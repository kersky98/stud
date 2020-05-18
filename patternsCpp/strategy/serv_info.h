#ifndef SERV_INFO_H
#define SERV_INFO_H

#include <stdint.h>

enum class VID{
  NIIDAR,
  SARANSK,
  PLANETA
};

enum class DID{
  _77YA6DM_YA400,
  _113G6_B072,
  _113G6_B073,
  _113G6_B221
};

/**
  @struct ServInfo
  @brief сервисная информация каждого устройства
*/
struct ServInfo{
  uint16_t vid; //!< vendor id
  uint16_t did; //!< device id
  uint32_t unique_number; //!< unique_number
  uint8_t sw_ver; //!< software version
  uint8_t hw_ver; //!< hardware version
  uint32_t time_cnt;  //!< working time counter (hours)
  uint32_t mem_sz;  //!< available memory size (bytes)
};


#endif //SERV_INFO_H
