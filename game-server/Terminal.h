#pragma once

#include "Handle.h"

class Terminal {
protected:
  Handle handle;

public:
  virtual ~Terminal() = default;
  virtual void play() = 0;
};
