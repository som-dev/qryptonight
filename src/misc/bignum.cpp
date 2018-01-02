// Distributed under the MIT software license, see the accompanying
// file LICENSE or http://www.opensource.org/licenses/mit-license.php.

#include "bignum.h"

uint256_t fromByteVector(std::vector<uint8_t> vec)
{
    uint256_t tmp(0);
    for(uint8_t i=0; i<32; i++)
    {
        tmp<<=8;
        tmp+=vec[31-i];
    }
    return tmp;
}

std::vector<uint8_t> toByteVector(uint256_t val)
{
    std::vector<uint8_t> tmp(32, 0);

    for(uint8_t i=0; i<32; i++)
    {
        tmp[i] = uint8_t(val & 0xFF);
        val>>=8;
    }

    return tmp;
}