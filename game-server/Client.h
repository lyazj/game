#pragma once

#include "Terminal.h"

class Client: public Terminal {
public:
  virtual void play() override;
};
