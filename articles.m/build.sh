contract='articles.m'

eosio-cpp -contract=${contract} -abigen ${contract}.cpp -o ${contract}.wasm -O=3 -lto-opt=O3