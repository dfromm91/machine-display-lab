#include "decoder.h"
#include <iostream>

int main()
{
    const bool acceptsLittleEndian = decodeSpeed(speedFrame, {0x2c, 0x01}) == 300;
    const bool acceptsZero = decodeSpeed(speedFrame, {0, 0}) == 0;
    const bool rejectsWrongId = !decodeSpeed(0x180, {0, 0});
    const bool rejectsTruncation = !decodeSpeed(speedFrame, {1});
    const bool rejectsTrailingBytes = !decodeSpeed(speedFrame, {1, 0, 0});
    const bool rejectsOutOfRange = !decodeSpeed(speedFrame, {0xff, 0xff});
    if (acceptsLittleEndian && acceptsZero && rejectsWrongId && rejectsTruncation
        && rejectsTrailingBytes && rejectsOutOfRange) return 0;
    std::cerr << "A decoder invariant failed\n";
    return 1;
}
