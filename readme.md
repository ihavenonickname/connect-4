* Using `least` types (`uint_least8_t`, `int_least16_t` etc): Those are more portable than fixed-length types (such as `uint8_t`) and the compiler is able to perform a few tricks to increase performance.

* Using `uint_least8_t` for board size: Board size can't be negative, so that's why it's unsigned. Also, typically the size is a single digit number, so 8 bits are more than enough.

* Using `int_least16_t` for position: I want it to be possible to represent positions outside of the board. A 16-bit, signed number is big enough for this.

* Using `class enum`: A `class enum` offers better type safety over plain and old C enums.


