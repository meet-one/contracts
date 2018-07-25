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
        struct exchange_state {
            asset supply;
            asset balance;
            uint32_t weight;

            uint64_t primary_key() const { return supply.symbol; }

            EOSLIB_SERIALIZE(exchange_state, (supply)(balance)(weight))
        };

    public:
        typedef eosio::multi_index<N(stats), exchange_state> state_index;

        meetonexdemo(account_name self) : contract(self) {
            state_index stats(_self, _self);

            auto meetone_state = stats.find(S(4, DEMO));

            if (meetone_state == stats.end()) {
                stats.emplace(_self, [&](auto &stat) {
                    stat.supply.symbol = S(4, DEMO);
                    stat.supply.amount = 100000000000;

                    stat.balance.symbol = S(4, MEETONE);
                    stat.balance.amount = 100000000000;

                    stat.weight = 500;
                });
            } else {
                stats.modify(stats.begin(), _self, [&](auto &stat) {
                    stat.supply.symbol = S(4, DEMO);
                    stat.supply.amount = 100000000000;

                    stat.balance.symbol = S(4, MEETONE);
                    stat.balance.amount = 100000000000;

                    stat.weight = 500;
                });
            }
        }

        void transfer(account_name from, account_name to, asset quantity, string memo);

    };
} /// namespace meetone
