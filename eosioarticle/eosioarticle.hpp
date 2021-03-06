#pragma once

#include <eosiolib/asset.hpp>
#include <eosiolib/eosio.hpp>

#include <string>

namespace eosiosystem {
class system_contract;
}

namespace meetone {

class eosioarticle : public eosio::contract {
public:
      eosioarticle(account_name self) :
            contract(self),
            articles_(_self, _self) {}

      void publish(account_name owner, std::string title, std::string author, std::string body);
      void edit(uint64_t id, account_name owner, std::string title, std::string author, std::string body);

      // NOT save to database
      void record(std::string title, std::string author, std::string body);

      // NOT save to database
      void post(account_name to, std::string title, std::string body);

      // NOT save to database
      void chat(account_name to, std::string memo);

      // NOT save to database
      void memo(std::string memo);

private:
      ///@abi table articles i64
      struct article {
            uint64_t id;
            account_name owner;
            std::string title;
            std::string author;
            std::string body;

            uint64_t primary_key() const { return id; }

            EOSLIB_SERIALIZE(article, (id)(owner)(title)(author)(body))
      };

      typedef eosio::multi_index<N(articles), article> articles;

      articles articles_;
};

} /// namespace meetone
