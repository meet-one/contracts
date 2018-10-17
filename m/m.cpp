/**
 * @author UMU618(zhengming@meet.one)
 * @copyright 2018 MEET.ONE
 * @description 2018-09-11, Amoy, Chromium coding-style, compile on eosio.cdt.
 */

#include "m.hpp"

namespace meetone {

void m::transfer(eosio::name from, eosio::name to, eosio::asset quantity, std::string memo) {
}

} /// namespace meetone

EOSIO_ON_TRANSFER(meetone::m, transfer)
