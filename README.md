# message_queue

An experimental Arduino helper for storing short timestamped messages in a fixed-size queue.

This project is intended for small embedded projects that need to temporarily hold short status messages, events, debug strings, or outgoing messages until they can be processed or transmitted.

## Project Status

Experimental / incomplete.

This repo currently represents the start of a lightweight message queue helper. It should be treated as a work-in-progress, not a finished library.

## Intended Use

The goal is to support simple embedded workflows such as:

* buffering short debug messages
* storing status events
* holding outgoing messages until a transmitter is ready
* tracking message timestamps
* marking messages with small flags
* avoiding immediate blocking output in timing-sensitive code

## Target Environment

This project is intended for:

* Arduino-compatible projects
* small microcontrollers
* short text messages
* fixed-size memory allocation
* simple single-threaded loop-based firmware

## Concept

Each queued message is intended to contain:

| Field       | Purpose                                               |
| ----------- | ----------------------------------------------------- |
| `timestamp` | Time the message was created, usually from `millis()` |
| `flag`      | Small status, priority, or message-type marker        |
| `msg`       | Short character buffer containing the message text    |

## Intended Queue Behavior

The eventual queue behavior should include:

* fixed maximum number of messages
* fixed maximum message length
* check whether the queue is empty
* check whether the queue is full
* add a new message
* read the oldest message
* remove the oldest message
* track oldest and newest message positions
* avoid dynamic memory allocation

## Planned API

Possible future API:

```cpp
bool push(const char* message, uint8_t flag = 0);
bool pop();
bool peek(char* buffer, uint8_t buffer_size);
bool is_empty();
bool is_full();
uint8_t queue_length();
unsigned long oldest_timestamp();
uint8_t oldest_flag();
```

## Suggested Arduino IDE Layout

The Arduino IDE expects the sketch folder and main `.ino` file to share the same name.

Recommended layout:

```text
message_queue/
├── message_queue.ino
├── message_queue.h
├── README.md
└── LICENSE
```

## Known Limitations

* Experimental code
* Not currently a finished queue implementation
* No complete enqueue/dequeue behavior yet
* No formal examples yet
* No automated tests
* Intended for short messages only
* Not thread-safe
* No warranty or support commitment

## Possible Future Improvements

Possible future improvements:

* implement fixed-size ring buffer behavior
* add `push()` and `pop()` functions
* add `peek()` without removing the message
* add message flags
* add timestamp accessors
* add overflow handling behavior
* add example sketch
* add serial diagnostic demo
* add configurable message length
* add documentation for memory use
* add unit-style test sketch
* add optional message integrity checking using checksum, CRC-8, or CRC-16

## Possible Message Integrity Support

A future version could optionally include a checksum or CRC with each queued message.

That would be useful if queued messages are later sent over:

- Serial
- radio modules
- telemetry links
- SD card logs
- unreliable or noisy connections

Possible approaches include:

- simple additive checksum for low-overhead debugging
- CRC-8 for short messages
- CRC-16 for stronger error detection

This is not currently implemented.

## Related Use Cases

This helper would pair well with projects that need to buffer output before writing to:

* Serial
* SD card
* radio modules
* displays
* telemetry links
* debug consoles

## License

This project is released under the MIT License.

You are free to use, modify, and adapt it for your own projects. No warranty is provided, and no ongoing support or maintenance is implied.
