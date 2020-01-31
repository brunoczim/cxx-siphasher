#include <iostream>
#include "siphasher.h"

int main(int argc, char const **argv)
{
    // Computes the hash of the inputs, '2', '0', '1', 0xF5, 'a'.
    // Should print 3681736453344691554
    SipHasher hasher;
    hasher << '2' << '0' << '1';
    hasher << 0xF5;
    hasher << 'a';
    std::cout << hasher.finish() << std::endl;
    
    /// Only the order changed.
    /// Should print 11314489606337045264
    hasher.reset();
    hasher << '2' << '0' << '1';
    hasher << 'a';
    hasher << 0xF5;
    std::cout << hasher.finish() << std::endl;

    // Slight change.
    // Should print 11087590648384868559
    hasher.reset();
    hasher << '2' << '0' << '1';
    hasher << 0xF5;
    hasher << 'b';
    std::cout << hasher.finish() << std::endl;

    // Same input as the first time, same output expected.
    hasher.reset();
    hasher << '2' << '0' << '1';
    hasher << 0xF5;
    hasher << 'a';
    std::cout << hasher.finish() << std::endl;

    return 0;
}
