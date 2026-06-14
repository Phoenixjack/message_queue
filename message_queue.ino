#include "message_queue.h"

MessageQueue queue;

void setup() {
  Serial.begin(9600);

  queue.push("System boot", 1);
  queue.push("Sensor ready", 2);
}

void loop() {
  if (!queue.is_empty()) {
    Serial.print(queue.oldest_timestamp());
    Serial.print(" [");
    Serial.print(queue.oldest_flag());
    Serial.print("] ");
    Serial.println(queue.oldest_msg());

    queue.pop();
  }

  delay(1000);
}
