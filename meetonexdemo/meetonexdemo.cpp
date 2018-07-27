//
// Created by yahuang.wu on 2018/7/20.
//

#include "meetonexdemo.hpp"

#define MEETONE_SYMBOL S(4,MEETONE)
#define DEMO_SYMBOL S(4,DEMO)

namespace meetone {

    void meetonexdemo::init() {
        state_index stats(_self, _self);

        stats.emplace(_self, [&](auto &stat) {
            stat.supply.symbol = DEMO_SYMBOL;
            stat.supply.amount = 100000000000;

            stat.balance.symbol = MEETONE_SYMBOL;
            stat.balance.amount = 100000000000;

            stat.connector_weight = 500;
        });

//        stats.modify(stats.begin(), _self, [&](auto &stat) {
//            stat.supply.symbol = S(4, DEMO);
//            stat.supply.amount = 100000000000;
//
//            stat.balance.symbol = S(4, MEETONE);
//            stat.balance.amount = 100000000000;
//
//            stat.connector_weight = 500;
//        });
    }

    void meetonexdemo::transfer(account_name from, account_name to, asset token_paid, string memo) {
        if (from == _self || to != _self) {
            return;
        }

//        eosio::print("from:", from, "\n");
//        eosio::print("to:", to, "\n");
//        eosio::print("token_paid:", token_paid, "\n");
//        eosio::print("symbol:", token_paid.symbol, "\n");
//        eosio::print("memo:", memo, "\n");

        // Only accept MEETONE token
        if (token_paid.symbol == MEETONE_SYMBOL) {
            eosio_assert(token_paid.is_valid(), "Invalid token transfer");
            eosio_assert(token_paid.amount > 0, "Quantity must be positive");

            state_index stats(_self, _self);

            if (stats.find(DEMO_SYMBOL) == stats.end()) {
                init();
            }

            auto meetone_stat = stats.get(DEMO_SYMBOL);

//            eosio::print("meetone_stat connector_weight: ", meetone_stat.connector_weight, "\n");
//            eosio::print("meetone_stat supply symbol: ", meetone_stat.supply.symbol, "\n");
//            eosio::print("meetone_stat supply amount: ", meetone_stat.supply.amount, "\n");
//            eosio::print("meetone_stat balance symbol: ", meetone_stat.balance.symbol, "\n");
//            eosio::print("meetone_stat balance amount: ", meetone_stat.balance.amount, "\n\n\n\n");

            real_type token_paid_amount = token_paid.amount;
            real_type balance_amount = meetone_stat.balance.amount;
            real_type supply_amount = meetone_stat.supply.amount;

            // stat connector_weight
            real_type cw = meetone_stat.connector_weight / 1000.0;
            real_type ONE = 1.0;

            // calculate amount of token issued
            real_type token_issued_amount =
                    supply_amount * (std::pow((token_paid_amount / balance_amount) + ONE, cw) - ONE);
            int64_t issued = int64_t(token_issued_amount);


            asset target_quantity = asset{issued, DEMO_SYMBOL};

            // calculate supply amount and balance amount after token issued.
            int64_t supply_amount_after_issued = meetone_stat.supply.amount + issued;
            int64_t balance_amount_after_issued = meetone_stat.balance.amount + token_paid.amount;

            // update stat token data
            stats.modify(stats.find(DEMO_SYMBOL), _self, [&](auto &stat) {
                stat.supply.amount = supply_amount_after_issued;
                stat.balance.amount = balance_amount_after_issued;
            });

//            eosio::print("issued: ", issued, "\n");
//            eosio::print("supply_amount_after_issued: ", supply_amount_after_issued, "\n");
//            eosio::print("balance_amount_after_issued: ", balance_amount_after_issued, "\n");

            action(
                    permission_level{_self, N(active)},
                    N(eosiomeetone), N(transfer),
                    make_tuple(_self, from, target_quantity, std::string("issued from meetonexdemo"))
            ).send();

        } else {
//            eosio_assert(token_paid.symbol == MEETONE_SYMBOL, "meetonexdemo only accepts MEETONE");
        }
    }
}


#define EOSIO_ABI_EX(TYPE, MEMBERS) \
extern "C" { \
    void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
        auto self = receiver; \
        eosio::print("receiver",receiver,"\n"); \
        eosio::print("code",code,"\n"); \
        eosio::print("action",action,"\n"); \
        if( action == N(onerror)) { \
            eosio_assert(code == N(eosiomeetone), "onerror action's are only valid from the \"eosiomeetone\" account"); \
        } \
        if((code == N(eosiomeetone) && action == N(transfer)) ) { \
            TYPE thiscontract( self ); \
            switch( action ) { \
                EOSIO_API( TYPE, MEMBERS ) \
            } \
        } \
    } \
} \

EOSIO_ABI_EX(meetone::meetonexdemo, (transfer))