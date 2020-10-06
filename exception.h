#include <stdexcept>
#include "easylogging++.h"

class ErrorAndLog : public std::runtime_error {
 public:
  explicit ErrorAndLog(const std::string& what_arg)
      : std::runtime_error(what_arg) {
    LOG(ERROR) << what_arg;
  }

  explicit ErrorAndLog(const char* what_arg) : std::runtime_error(what_arg) {
    LOG(ERROR) << what_arg;
  }
};
