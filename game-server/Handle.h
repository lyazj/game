#pragma once

#include <stdint.h>

#define VAL_MAX 1024
#define VAL_NSEG 2
#define ACC_THRESHOLD 16
#define OP_INVALID ((uint8_t)-1)
#define OP_DEFAULT 1

enum Hop : uint8_t {
  UP,
  DOWN,
  LEFT,
  RIGHT,
  PRESS,
  NHOP,
};

class Handle {
private:
  uint8_t read_single(uint8_t pin);
  uint8_t read_buf(uint8_t buf[3]);
public:
  uint8_t read();
};
