echo 'May need run: "cleos wallet unlock"'

contract='m'
cleos set contract ${contract} ../${contract} -p ${contract}@active
