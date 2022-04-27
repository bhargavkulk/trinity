# NEO ISA
## `hlt`
Halts execution.

## `CONST 8'bID`
Pushes constant from constant pool with index `ID` onto the VM's stack.

## `CONST_NEG_1`, `CONST_0` to `CONST_10`
Pushes constants ranging from -1 to 10 directly onto the stack.

## `ADD`
Pops top 2 integers from the stack and pushes the sum onto the stack.
- Throws error if both elements not being compared are not integers.

## `SUB`
Pops top 2 integers from the stack and pushes the difference onto the stack.
- Throws error if both elements not being compared are not integers.

## `MUL`
Pops top 2 integers from the stack and pushes the product onto the stack. 
- Throws error if both elements not being compared are not integers.

## `DIV`
Pops top 2 integers from the stack and pushes the quotient onto the stack. 
- Throws error if both elements not being compared are not integers.
- Throws error if divisor is zero.

## `MOD`
Pops top 2 integers from the stack and pushes the remainder onto the stack.
- Throws error if both elements not being compared are not integers.

## `SUB`
Pops topmost integer from the stack and pushes the negation onto the stack. 
- Throws error if both elements not being compared are not integers.

## `LESS`, `LESS_EQUAL`, `GREAT`, `GREAT_EQUAL`
Pops top 2 integers from the stack and pushes the boolean comparison result onto the stack. 
- Throws error if both elements not being compared are not integers.

## `EQUAL`
Pops top 2 elements from the stack and pushes the boolean comparison result onto the stack.
- Throws error if both elements are not of the same type.

## `GLOB_VARSET`
**TODO NIMISH**

## `GLOB_VARGET`
**TODO NIMISH**

## `VARSET 8'bID`
Pops value from the stack and saves it in the variable with id `ID`.

## `VARGET 8'bID`
Pushes the value saved in variable with id `ID`.

## `CALL 32b'ADDR`
Jumps the instruction pointed to at by `ADDR` while also starting a new stackframe.

## `RET`
Moves PC back to where the caller called the callee.

## `LOGINT`
Pops the topmost element of the stack and logs it.
- Throws error if element is not an integer.

## `LOGSTR`
Pops the topmost element of the stack and logs it.
- Throws error if element is not a string.

## `JMP_IF_FALSE 16'bOFFSET`
Pops the topmost element of the stack. If the element is falsey i.e. the element is 0, the 16-bit `OFFSET` is added to the program counter, else the program counter remains the same.
- Throws error if the `OFFSET` cannot be represented as an unsigned 16-bit integer.

## `JMP 16'bOFFSET`
The 16-bit `OFFSET` is unconditionally added to the program counter.
- Throws error if the `OFFSET` cannot be represented as an unsigned 16-bit integer.

## `LOOP 16'bOFFSET`
The 16-bit `OFFSET` is unconditionally subtracted from the program counter.
- Throws error if the `OFFSET` cannot be represented as an unsigned 16-bit integer.
- Throws error if the `OFFSET` is greater than the program counter

## `POP`
Topmost element of the stack is discarded.

## `ARR 8'bSIZE`
Pushes a new array on stack with `SIZE` as dimension.

## `ARRSET`
Pops array pointer and indices and value from stack and sets the element of the array at the indices to that value.

## `ARRGET`
Pops array pointer and indices from stack and get the value saved in the array at the indices.

## `DEL`
Pops pointer to array from the stack and deletes it.
