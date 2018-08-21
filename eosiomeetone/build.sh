image_name=eosio/eos-dev
image_version=v1.1.1
image_id=8fa0988c81cc
contract='eosiomeetone'
docker run --rm -v `pwd`:/scts ${image_id} bash -c "cd /scts \
        && eosiocpp -o ${contract}.wast ${contract}.cpp \
        && eosiocpp -g ${contract}.abi ${contract}.cpp"