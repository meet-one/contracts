#include "articles.m.hpp"

namespace meetone {

// publish an article
void articles::publish(std::string title,
                       std::string author,
                       std::string content) {
// get the action's authorization account
  auto act = eosio::get_action(1, 0);
  eosio::name owner = act.authorization.at(0).actor;
  require_auth(owner);

  auto now = eosio::time_point(eosio::microseconds(current_time()));
  article_table articles(get_self(), get_self().value);
  articles.emplace(owner, [&](auto& a) {
// id strictly auto-incrementing  
    a.id = articles.available_primary_key();
    a.owner = owner;
    a.title = title;
    a.author = author;
    a.create_time = now;
    a.update_time = now;
    a.content = content;
  });
}

// edit a published article
void articles::edit(uint64_t id,
                    std::string title,
                    std::string author,
                    std::string content) {
// get the article
  article_table articles(get_self(), get_self().value);
  auto itr = articles.require_find(id, "article not exist.");
// only article's owner can edit the article
  require_auth(itr->owner);

  auto now = eosio::time_point(eosio::microseconds(current_time()));
  articles.modify(itr, itr->owner, [&](auto& a) {
    a.title = title;
    a.author = author;
    a.update_time = now;
    a.content = content;
  });
}

// delete a published article
void articles::delarticle(uint64_t id) {
  article_table articles(get_self(), get_self().value);
  auto itr = articles.require_find(id, "article not exist.");
// only article's owner can delete the article
  require_auth(itr->owner);
  articles.erase(itr);
}

}  // namespace meetone

EOSIO_DISPATCH(meetone::articles, (publish)(edit)(delarticle))