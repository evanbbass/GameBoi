[Back to Dev Diaries](../DevDiaries.md)
## 6/14/2017

This was a busy week, so I haven't had time to update this dev diary properly. For most of the week I was busy with another assignment, so most of the work on this was pushed to the last couple days.

Eventually I was able to get all of the opcodes implemented. Some took longer than expected, but most took much less than the time I had estimated for them.

| Task                     | Estimated Time (hours) | Actual Time(hours) |
| ---------------------- |:----------------------:|:------------------:|
| 16-bit Loads             | 2:00                   | 1:49               |
| 8-bit ALU                | 2:00                   | 2:07               |
| 16-bit Arithmetic        | 1:00                   | 0:38               |
| Miscellaneous            | 2:00                   | 1:28               |
| Rotates & Shifts         | 3:00                   | 1:51               |
| Bit Opcodes              | 1:00                   | 1:03               |
| Jumps                    | 1:00                   | 0:15               |
| Calls, Restarts, Returns | 1:00 each              | 0:17 total         |

Jumps and Calls ended up being trivial. When estimating these tasks I didn't think far enough into them to realize that all they involve is setting the Program Counter, with pushing the current PC onto the stack for calls.

As for the tasks that took longer than expected, the ALU took a while because setting the flags ended up being trickier than I anticipated. Calculating the half-carry flag involves doing another addition to check if there was a carry between bits 3 and 4 (or bits 11 and 12 in 16-bit land):

```c++
// for ADC A,A
bool halfCarry = (mRegisters.A & 0xF) + (mRegisters.A & 0xF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xF;
bool fullCarry = (mRegisters.A & 0xFF) + (mRegisters.A & 0xFF) + mRegisters.GetCarryFlag() ? 1 : 0 > 0xFF;
```

As for the bit opcodes, they took a while simply because there are so many of them (192 to be exact).

Nothing else too exciting happened this week; it was really just a long slog through all of the instructions. One thing I do want to note, however, is that treating warnings as errors ended up saving me in the arithmetic shifts:

```c++
bool carry = (mRegisters.A & 0x1) != 0;
bool negative = mRegisters.A & 0x80 != 0;
uint8_t result = (mRegisters.A >> 1) | (negative ? 0x80 : 0x00);
```

Can you tell what's wrong with that code? (Besides the fact that it's kind of gross.)

The answer lies in the order of operations: line 2 would first check if 0x80 is not equal to 0, then bit-wise and that (false, by the way) with `mRegisters.A`

The Visual Studio compiler kindly warned me about this so I could add parentheses to make it correct:

```c++
bool carry = (mRegisters.A & 0x1) != 0;
bool negative = (mRegisters.A & 0x80) != 0;
uint8_t result = (mRegisters.A >> 1) | (negative ? 0x80 : 0x00);
```

This will check if bit 7 is set (which would indicate that the number is negative).

That's all for this week, next week should be much more interesting since I will be starting work on the debugger.
