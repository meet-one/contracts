contract='m'

eosio-cpp -contract=${contract} -abigen ${contract}.cpp -o ${contract}.wasm
