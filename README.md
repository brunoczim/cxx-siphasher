# cxx-siphasher
C++ SipHash implementation (NOT a cryptographic hash)

# Example
```c++
#include <iostream>
#include "siphasher.h"

int main(int argc, char const **argv)
{

    // Computes the hash of the inputs, '2', '0', '1', 0xF5, 'a'.
    // Should print 16868040514378186995
    SipHasher hasher;
    hasher << '2' << '0' << '1';
    hasher << '2' << '0' << '0';
    hasher << '1' << '1' << '2';
    hasher << 0xF5;
    hasher << 'a';
    std::cout << hasher.finish() << std::endl;
    
    /// Only the order changed.
    // Should print 6702610910943071329
    hasher.reset();
    hasher << '2' << '0' << '1';
    hasher << '2' << '0' << '0';
    hasher << '1' << '1' << '2';
    hasher << 'a';
    hasher << 0xF5;
    std::cout << hasher.finish() << std::endl;

    // Slight change.
    // Should print 4708902222725415026
    hasher.reset();
    hasher << '2' << '0' << '1';
    hasher << '2' << '0' << '0';
    hasher << '1' << '1' << '2';
    hasher << 0xF5;
    hasher << 'b';
    std::cout << hasher.finish() << std::endl;

    // Same input as the first time, same output expected.
    // Should print 16868040514378186995
    hasher.reset();
    hasher << '2' << '0' << '1';
    hasher << '2' << '0' << '0';
    hasher << '1' << '1' << '2';
    hasher << 0xF5;
    hasher << 'a';
    std::cout << hasher.finish() << std::endl;

    return 0;
}
```
