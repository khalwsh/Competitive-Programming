#define static_assert(...);
#include <tr2/dynamic_bitset>
using custom_bitset = tr2::dynamic_bitset<long long>;
// custom_bitset(10)
// think of using __int128 if number of bits are small
// because for large integers it got WA