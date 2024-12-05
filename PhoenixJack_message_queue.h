#include "Arduino.h"
#include <stdint.h>

class PhoenixJack_message_queue {
private:
  uint8_t _max_messages = 20;
  uint8_t _num_messages_unsent = 0;
  uint8_t _msg_chars = 50;
  uint8_t _oldest_msg_id = 0;
  uint8_t _newest_msg_id = 0;
  struct _message_queue {
    unsigned long timestamp = 0;
    uint8_t flag = 0;
    char msg[100];
  };
public:
  explicit PhoenixJack_message_queue(uint8_t num_messages, uint8_t msg_chars);  // initialize
  bool anything_in_queue();
  bool is_queue_empty();
  bool is_queue_full();
  uint8_t queue_length();
  uint8_t oldest_msg_id();
  uint8_t newest_msg_id();
  char* oldest_msg();
};
PhoenixJack_message_queue::PhoenixJack_message_queue(uint8_t num_messages = 10, uint8_t msg_chars = 50) {
  //uint32_t size_needed = num_messages * (msg_chars + 4 + 1);  // calculating how much space this will take; we add a few bytes for the millis() timestamp and a byte for acknowledged
  _message_queue[_max_messages];
};
bool PhoenixJack_message_queue::anything_in_queue() {
  return (_num_messages_unsent > 0);
};
bool PhoenixJack_message_queue::is_queue_empty() {
  return !anything_in_queue();
};
bool PhoenixJack_message_queue::is_queue_full() {
  return (_num_messages_unsent == _max_messages);
};
uint8_t PhoenixJack_message_queue::queue_length() {
  return _num_messages_unsent;
};
uint8_t PhoenixJack_message_queue::oldest_msg_id() {
  return _oldest_msg_id;
};
uint8_t PhoenixJack_message_queue::newest_msg_id() {
  return _newest_msg_id;
};
char* PhoenixJack_message_queue::oldest_msg() {
  return *_message_queue[_oldest_msg_id];
};
