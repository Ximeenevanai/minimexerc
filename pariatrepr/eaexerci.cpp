#include <cstdint>

// Assume tensLookupTable is defined somewhere in your code
extern const uint64_t tensLookupTable[];

// Example usage
void someFunction(int halfIndex) {
    const uint64_t tens = tensLookupTable[halfIndex];
    // Use the value of 'tens' in further computations or operations
}
