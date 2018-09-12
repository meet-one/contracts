/**
 *  2018-09-11, Amoy, UMU618(zhengming@meet.one)
 *  @copyright 2018 MEET.ONE
 */

#include "eosioarticle.hpp"

using namespace eosio;

namespace meetone {

/// @abi action
void eosioarticle::publish(account_name owner, std::string title, std::string author, std::string body)
{
    //print("checking publish parameters...");
    require_auth(owner);
    require_recipient(owner);
    eosio_assert(title.size() <= 2 * 1024, "title has more than 2k bytes");
    eosio_assert(author.size() <= 1 * 1024, "title has more than 1k bytes");
    eosio_assert(body.size() <= 512 * 1024, "body has more than 512k bytes");

    //print("publishing...");
    // Store new article
    articles_.emplace(_self, [&](auto& article){
        article.id = articles_.available_primary_key();
        //print("new article, id = ", article.id, "...");
        article.owner = owner;
        article.title = title;
        article.author = author;
        article.body = body;
    });

    //print("published!");
}

/// @abi action
void eosioarticle::edit(uint64_t id, account_name owner, std::string title, std::string author, std::string body)
{
    //print("checking edit parameters...");
    require_auth(owner);
    require_recipient(owner);
    eosio_assert(title.size() <= 2 * 1024, "title has more than 2k bytes");
    eosio_assert(author.size() <= 1 * 1024, "title has more than 1k bytes");
    eosio_assert(body.size() <= 512 * 1024, "body has more than 512k bytes");

    //print("editing...");
    // find article
    auto itr = articles_.find(id);
    if (itr == articles_.cend()) {
        articles_.emplace(_self, [&](auto& article) {
            article.id = articles_.available_primary_key();
            //print("id = ", article.id, "...");
            article.owner = owner;
            article.title = title;
            article.author = author;
            article.body = body;
        });
    } else {
        eosio_assert(itr->owner == owner, "can't edit other's article.");

        articles_.modify(itr, 0, [&](auto& article) {
            article.title = title;
            article.author = author;
            article.body = body;
        });
    }

    //print("edited!");
}

/// @abi action
void eosioarticle::record(std::string title, std::string author, std::string body)
{
    //print("checking record parameters...");
    eosio_assert(title.size() <= 2 * 1024, "title has more than 2k bytes");
    eosio_assert(author.size() <= 1 * 1024, "title has more than 1k bytes");
    eosio_assert(body.size() <= 512 * 1024, "body has more than 512k bytes");
    //print("record!");
}

/// @abi action
void eosioarticle::post(account_name to, std::string title, std::string body)
{
    require_recipient(to);
    eosio_assert(title.size() <= 2 * 1024, "title has more than 2k bytes");
    eosio_assert(body.size() <= 512 * 1024, "body has more than 512k bytes");
}

} /// namespace meetone

EOSIO_ABI(meetone::eosioarticle, (publish)(edit)(record)(post))
