#include "articles.m.hpp"

namespace meetone {

void articles::publish(std::string title,
                       std::string author,
                       std::string content) {
  auto act = eosio::get_action(1, 0);
  eosio::name owner = act.authorization.at(0).actor;
  require_auth(owner);
  auto now = eosio::time_point(eosio::microseconds(current_time()));
  article_table articles(get_self(), get_self().value);
  articles.emplace(owner, [&](auto& a) {
    a.id = articles.available_primary_key();
    a.owner = owner;
    a.title = title;
    a.author = author;
    a.create_time = now;
    a.update_time = now;
    a.content = content;
  });
}

void articles::edit(uint64_t id,
                    std::string title,
                    std::string author,
                    std::string content) {
  article_table articles(get_self(), get_self().value);
  auto itr = articles.require_find(id, "article not exist.");
  require_auth(itr->owner);
  auto now = eosio::time_point(eosio::microseconds(current_time()));
  articles.modify(itr, itr->owner, [&](auto& a) {
    a.title = title;
    a.author = author;
    a.update_time = now;
    a.content = content;
  });
}

void articles::delarticle(uint64_t id) {
  article_table articles(get_self(), get_self().value);
  auto itr = articles.require_find(id, "article not exist.");
  require_auth(itr->owner);
  articles.erase(itr);
}

}  // namespace meetone

EOSIO_DISPATCH(meetone::articles, (publish)(edit)(delarticle))