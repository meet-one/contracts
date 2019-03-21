# MEETONE Sidechain Article Publisher

Contract account name:
```
articles.m
```

## ACTION
 
**publish**

Publish an article.(You must pay for RAM)

```
cleos -u https://fullnode.meet.one push action articles.m publish '["ARTICLE_TITLE","ARTICLE_AUTHOR","ARTTICLE_CONTENT"]' -p RAM_PAYER
```
`RAM_PAYER` is the article's owner.

**edit**

Edit a published article by id.

```
cleos -u https://fullnode.meet.one push action articles.m edit '["ARTICLE_ID","ARTICLE_TITLE","ARTICLE_AUTHOR","ARTTICLE_CONTENT"]' -p ARTTICLE_OWNER
```
only owner of article can edit a published article. 

**delarticle**

delete a published article by id.

```
cleos -u https://fullnode.meet.one push action articles.m delarticle '["ARTICLE_ID"]' -p ARTTICLE_OWNER
```
only owner of article can delete a published article, and RAM will return to owner.

## QUERY

query all articles:

```
cleos -u https://fullnode.meet.one get table articles.m articles.m articles
```

query an article by id:

```
cleos -u https://fullnode.meet.one get table articles.m articles.m articles -L ARTICLE_ID _U ARTICLE_ID
```

query all articles published by someone:

```
cleos -u https://fullnode.meet.one get table articles.m articles.m articles --index 2 --key-type i64 -L ARTICLE_OWNER _U ARTICLE_OWNER
```