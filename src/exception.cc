#include "exception.hh"

namespace Kakoune {

StringView exception::what() const {
  return typeid(*this).name();
}
}
