/*
  * This program is free software: you can redistribute it and/or modify
  * it under the terms of the GNU General Public License as published by
  * the Free Software Foundation, either version 3 of the License, or
  * any later version.
  *
  * This program is distributed in the hope that it will be useful,
  * but WITHOUT ANY WARRANTY; without even the implied warranty of
  * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  * GNU General Public License for more details.
  *
  * You should have received a copy of the GNU General Public License
  * along with this program.  If not, see <http://www.gnu.org/licenses/>.
  *
  * Additional permission under GNU GPL version 3 section 7
  *
  * If you modify this Program, or any covered work, by linking or combining
  * it with OpenSSL (or a modified version of that library), containing parts
  * covered by the terms of OpenSSL License and SSLeay License, the licensors
  * of this Program grant you additional permission to convey the resulting work.
  *
  */
#include <iostream>
#include <xmrstak/backend/cpu/crypto/cryptonight.h>
#include <xmrstak/backend/cpu/crypto/cryptonight_aesni.h>
#include "gtest/gtest.h"

namespace {
    TEST(Xmr_stak, Init) {
        alloc_msg msg = { nullptr };

        size_t res = cryptonight_init(0, 1, &msg);
        EXPECT_EQ(1, 1);
    }

    TEST(Xmr_stak, CreateContext) {
        alloc_msg msg = { nullptr };

        auto res = cryptonight_init(0, 1, &msg);
        EXPECT_EQ(1, res);

        auto context = cryptonight_alloc_ctx(0, 1, &msg);

        EXPECT_NE(nullptr, context);
        if (context == nullptr)
            std::cout << "MEMORY ALLOC FAILED: " << msg.warning << std::endl;

        cryptonight_free_ctx(context);

        EXPECT_EQ(1, 1);
    }

    TEST(Xmr_stak, RunSingleHash) {
        alloc_msg msg = { nullptr };

        auto res = cryptonight_init(0, 1, &msg);
        EXPECT_EQ(1, res);

        auto context = cryptonight_alloc_ctx(0, 1, &msg);

        EXPECT_NE(nullptr, context);
        if (context == nullptr)
            std::cout << "MEMORY ALLOC FAILED: " << msg.warning << std::endl;

        std::vector<uint8_t> input {
                0x03, 0x05, 0x07, 0x09
        };

        std::vector<uint8_t> output_expected {
                0x3E, 0xE5, 0x3F, 0xE1, 0xAC, 0xF3, 0x55, 0x92,
                0x66, 0xD8, 0x43, 0x89, 0xCE, 0xDE, 0x99, 0x33,
                0xC6, 0x8F, 0xC5, 0x1E, 0xD0, 0xA6, 0xC7, 0x91,
                0xF8, 0xF9, 0xE8, 0x9D, 0xB6, 0x23, 0xF0, 0xF6
        };

        std::vector<uint8_t> output(32);

        cryptonight_hash<MONERO_MASK, MONERO_ITER, MONERO_MEMORY, false, false>(input.data(), input.size(),
                                                                                output.data(),
                                                                                context);

        cryptonight_free_ctx(context);


        EXPECT_EQ(output_expected, output);
    }

}
