//
// Created by yahuang.wu on 2018/7/20.
//
#pragma once

#include <eosiolib/eosio.hpp>
#include <eosiolib/asset.hpp>
#include <eosiolib/symbol.hpp>
#include <eosiolib/action.hpp>
#include <cmath>
#include <string>

using namespace eosio;
using namespace std;

namespace meetone {

    typedef double real_type;

    class meetonexdemo : public contract {
        // Uses Bancor math to calculate current price
        //@abi table
        struct exchange_state {
            asset supply;
            asset balance;
            uint32_t connector_weight;

            uint64_t primary_key() const { return supply.symbol; }

            EOSLIB_SERIALIZE(exchange_state, (supply)(balance)(connector_weight))
        };

    public:
        typedef eosio::multi_index<N(stats), exchange_state> state_index;

        meetonexdemo(account_name self) : contract(self) {};

        void init();

        void transfer(account_name from, account_name to, asset quantity, string memo);

    };
} /// namespace meetone
