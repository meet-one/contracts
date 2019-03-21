#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>

namespace meetone {

class[[eosio::contract("articles.m")]] articles : public eosio::contract {
 public:
  using eosio::contract::contract;

  ACTION publish(std::string title, std::string author, std::string content);

  ACTION edit(uint64_t id, std::string title, std::string author,
              std::string content);

  ACTION delarticle(uint64_t id);

 private:
  TABLE article {
    uint64_t id;
    eosio::name owner;
    std::string title;
    std::string author;
    eosio::time_point create_time;
    eosio::time_point update_time;
    std::string content;

    uint64_t primary_key() const { return id; }
    uint64_t by_owner_name() const { return owner.value; }

    EOSLIB_SERIALIZE(article,
                     (id)(owner)(title)(author)(create_time)(update_time)(content))
  };

  typedef eosio::multi_index<
      "articles"_n, article,
      eosio::indexed_by<
          "owner"_n,
          eosio::const_mem_fun<article, uint64_t, &article::by_owner_name>>>
      article_table;
};

}  // namespace meetone