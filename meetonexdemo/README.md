## MEET.ONE x DEMO

#### These are test only keys and should never be used for the production blockchain. 

Private key: 5JeB16BrspVqc8zwmNkMLt2K7omD8iS3jLZSgvQefH4zMe5NRgv
Public key: EOS66jh1quuuZRLivjTxeF4fTDFpVRz4vyE4kq1VN2vA6UmTphrFK


### Create Account
```
cleos create account eosio meetonexdemo EOS66jh1quuuZRLivjTxeF4fTDFpVRz4vyE4kq1VN2vA6UmTphrFK EOS66jh1quuuZRLivjTxeF4fTDFpVRz4vyE4kq1VN2vA6UmTphrFK
```

### Compile
```
eosiocpp -o meetonexdemo.wast meetonexdemo.cpp
eosiocpp -g meetonexdemo.abi meetonexdemo.cpp
```

### Deploy
```
cleos set contract meetonexdemo ../meetonexdemo -p meetonexdemo@active
```

### Add authority
```
cleos set account permission meetonexdemo active '{"threshold": 1,"keys": [{"key": "EOS66jh1quuuZRLivjTxeF4fTDFpVRz4vyE4kq1VN2vA6UmTphrFK","weight": 1}],"accounts": [{"permission":{"actor":"meetonexdemo","permission":"eosio.code"},"weight":1}]}' owner -p meetonexdemo
```

### [Deploy Token](https://github.com/meet-one/contracts/tree/master/eosiomeetone)

### Test
```
cleos push action eosiomeetone transfer '["eosiomeetone","meetonexdemo","100.0000 MEETONE","Hello world."]' -p eosiomeetone
```

### Check Balance:
```
cleos get currency balance eosiomeetone meetonexdemo
cleos get currency balance eosiomeetone eosiomeetone
cleos get currency stats eosiomeetone MEETONE
cleos get currency stats eosiomeetone DEMO
```


### Query Table:
```
cleos get table meetonexdemo meetonexdemo stats
```