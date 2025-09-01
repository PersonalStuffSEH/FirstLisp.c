1. problem 1:
  - desc:
    > i cant get the file size trivially.
    fseek and ftell
    IT��bU (and other gibberish) somehow gets added
  - sol:
      off by 1 error. i didnt account for the \0

**1. problem 2:**
  - desc:
    > header files and symbol resolution
  - sol:
      no solution found yet. i will get back to it

1. problem 3:
  - desc:
    > reading the file into memory in one go is very inefficient
  - sol:
      use fgetc and construct the ast from there
      i will implement that on a different branch because this should be a journey

1. problem 4:
  - desc:
    > i refuse to make allocations in the populate tree file
    it is bad practice
  - opt1:
    *i return the index of the ( and return the index of the ), store the slice*
    *that wont work because the ( is overwritten each time*
  - sol:
      use a stack and iter through once
      i translated the solution into python first
    ```py
    for i, e in enumerate(buffer):
      if e == '(':
        startIdx.append(i)
      if e == ')':
        idx = startIdx.pop(-1)
      expr = buffer[i:idx]
    ```

1. problem 5:
  - desc:
    > making the ast in a lisp
  - sol:
    use a recursive dict in python
    in c i can use a pointer in an array that stores the order too

1. problem 6:
  - desc:
    > the stack didnt return the lowest index (intentional behaviour)
  - sol:
    the file was read from lowest to highest order
    meaning that if i used a stack i would get the last index of ( and ) respectively
    easy fix, use a queue instead of a stack

**1. problem 7:**
  - desc:
    > i need to know at what point my lisp becomes a programming language
    for that i need to know the definitions of both
  - sol:
    grammar -> formal language
    semantics -> actual function
  - fup:
    > how does one implement semantics?

1. problem 8:
  - desc:
    > i dont free the allocated memory blocks
  - sol:
    free the memory

**1. problem 2:**
  - sol:
    link with dlopen

1. problem 9:
  - desc:
    > i dont know how to construct the lisp tree, what data structure is best
    sure a tree works with pointers but there are 2 implementations that are valid:
    the question then becomes, do i use an array or a linked list?
    linked lists for this structure are easier to traverse
    -> (a (b)(b' (b'a)))(c)
    -> => [X] is a node of X, -> v ^ are the connections
  - opt1:
    [a] -> [c]     // linked list
     v
    [b] -> [a<-b'] // b and b' are a linked list with common .prev=a
            v
           [b'a]   // b' has a linked list child of b'a
  - opt2:
    { [a], [c] }   // a and c are members of an array
       v
      { [b] [b'] } // a has a child array of b and b'
             v
            [b'a]  // b has a child array of b'a
