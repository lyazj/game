#pragma once

#include "Handle.h"

class Terminal {
protected:
  Handle handle;

public:
  Terminal();
  virtual ~Terminal() = default;
  virtual void play() = 0;
};
