contract='eosioarticle'

eosiocpp -o ${contract}.wast ${contract}.cpp
eosiocpp -g ${contract}.abi ${contract}.cpp
