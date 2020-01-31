# cxx-siphasher
C++ SipHash implementation (NOT a cryptographic hash)

# Example
```c++
#include <iostream>
#include "siphasher.h"

int main(int argc, char const **argv)
{
    // Computes the hash of the inputs, '2', '0', '1', 0xF5, 'a'.
    // Should output 16467991608841586078
    SipHasher hasher;
    hasher << '2' << '0' << '1';
    hasher << 0xF5;
    hasher << 'a';
    std::cout << hasher.finish() << std::endl;

    return 0;
}
```
