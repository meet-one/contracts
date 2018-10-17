#pragma once

#include <eosiolib/crypto.h>
#include <cstring>
#include <eosiolib/action.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>
#include <eosiolib/symbol.hpp>

namespace meetone {

class m : public eosio::contract {
 public:
  using eosio::contract::contract;

  void transfer(eosio::name from,
                eosio::name to,
                eosio::asset quantity,
                std::string memo);

 private:
  struct signup_public_key {
    uint8_t type;
    std::array<unsigned char, 33> data;
  };
  struct permission_level_weight {
    eosio::permission_level permission;
    uint16_t weight;
  };
  struct key_weight {
    signup_public_key key;
    uint16_t weight;
  };
  struct wait_weight {
    uint32_t wait_sec;
    uint16_t weight;
  };
  struct authority {
    uint32_t threshold;
    std::vector<key_weight> keys;
    std::vector<permission_level_weight> accounts;
    std::vector<wait_weight> waits;
  };
  struct newaccount {
    eosio::name creator;
    eosio::name name;
    authority owner;
    authority active;
  };
};

}  // namespace meetone

#define EOSIO_ON_TRANSFER(TYPE, FUNCTION)                                    \
  extern "C" {                                                               \
  void apply(capi_name receiver, capi_name code, capi_name action) {         \
    if (action == "onerror"_n.value) {                                       \
      /* onerror is only valid if it is for the "eosio" code account and     \
       * authorized by "eosio"'s "active permission */                       \
      eosio_assert(code == "eosio"_n.value,                                  \
                   "onerror action's are only valid from the \"eosio\" "     \
                   "system account");                                        \
    }                                                                        \
    if ((code == "eosio.token"_n.value && action == "transfer"_n.value)) {   \
      eosio::datastream<const char*> ds =                                    \
          eosio::datastream<const char*>(nullptr, 0);                        \
      eosio::execute_action(eosio::name(receiver), eosio::name(code),        \
                            &TYPE::FUNCTION);                                \
      /* does not allow destructor of thiscontract to run: eosio_exit(0); */ \
    }                                                                        \
  }                                                                          \
  }
