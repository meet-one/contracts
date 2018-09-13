echo 'May need run: "cleos wallet unlock"'

contract='eosioarticle'
cleos set contract ${contract} ../${contract} -p ${contract}@active
