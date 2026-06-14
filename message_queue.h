#pragma once

#include <Arduino.h>
#include <stdint.h>
#include <string.h>

class MessageQueue {
private:
  static const uint8_t MAX_MESSAGES = 10;
  static const uint8_t MAX_MESSAGE_CHARS = 50;

  struct QueueMessage {
    unsigned long timestamp;
    uint8_t flag;
    char msg[MAX_MESSAGE_CHARS];
  };

  QueueMessage _messages[MAX_MESSAGES];

  uint8_t _oldest = 0;
  uint8_t _newest = 0;
  uint8_t _count = 0;

public:
  bool is_empty() const {
    return _count == 0;
  }

  bool is_full() const {
    return _count >= MAX_MESSAGES;
  }

  uint8_t queue_length() const {
    return _count;
  }

  bool push(const char* message, uint8_t flag = 0) {
    if (is_full() || message == nullptr) {
      return false;
    }

    _messages[_newest].timestamp = millis();
    _messages[_newest].flag = flag;

    strncpy(_messages[_newest].msg, message, MAX_MESSAGE_CHARS - 1);
    _messages[_newest].msg[MAX_MESSAGE_CHARS - 1] = '\0';

    _newest = (_newest + 1) % MAX_MESSAGES;
    _count++;

    return true;
  }

  bool pop() {
    if (is_empty()) {
      return false;
    }

    _oldest = (_oldest + 1) % MAX_MESSAGES;
    _count--;

    return true;
  }

  const char* oldest_msg() const {
    if (is_empty()) {
      return nullptr;
    }

    return _messages[_oldest].msg;
  }

  unsigned long oldest_timestamp() const {
    if (is_empty()) {
      return 0;
    }

    return _messages[_oldest].timestamp;
  }

  uint8_t oldest_flag() const {
    if (is_empty()) {
      return 0;
    }

    return _messages[_oldest].flag;
  }
};
