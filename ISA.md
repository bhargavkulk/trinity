# NEO ISA
## `hlt`
Halts execution.

## `CONST 8'bID`
Pushes constant from constant pool with index `ID` onto the VM's stack.

## `CONST_NEG_1`, `CONST_0` to `CONST_10`
Pushes constants ranging from 1-1 to 10 directly onto the stack.

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

## `VARSET`
**TODO NIMISH**

## `VARGET`
**TODO NIMISH**

## `CALL`
**TODO NIMISH**

## `RET`
**TODO NIMISH**

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
