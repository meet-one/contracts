## MEET.ONE TOKEN

#### These are test only keys and should never be used for the production blockchain. 

Private key: 5K8UVpGD3ZPvfmpNdTpzCgJRNK7zSogVGVQBSH8Y6sdYmpTxtwj

Public key: EOS6yiFPzQFCxVg8DX8WPVChaFSBv6tTu2tF79m3mn3ZdHivy3uSE



### Create Account

```
cleos create account eosio eosiomeetone EOS6yiFPzQFCxVg8DX8WPVChaFSBv6tTu2tF79m3mn3ZdHivy3uSE EOS6yiFPzQFCxVg8DX8WPVChaFSBv6tTu2tF79m3mn3ZdHivy3uSE
```
```
cleos create account eosio meetonetest1 EOS6yiFPzQFCxVg8DX8WPVChaFSBv6tTu2tF79m3mn3ZdHivy3uSE EOS6yiFPzQFCxVg8DX8WPVChaFSBv6tTu2tF79m3mn3ZdHivy3uSE
```


### Deploy Contract

```
cleos set contract eosiomeetone ../eosiomeetone -p eosiomeetone@active
```


### Create Token

```
cleos push action eosiomeetone create '["eosiomeetone","10000.0000 MEETONE"]' -p eosiomeetone@active
```


### Issue Token

```
cleos push action eosiomeetone issue '["eosiomeetone","7500000000.0000 MEETONE","memo"]' -p eosiomeetone@active
```
```
cleos push action eosiomeetone issue '["eosiomeetone","625000000.0000 MEETONE","memo"]' -p eosiomeetone@active
```


### Transfer Token

```
cleos push action eosiomeetone transfer '["eosiomeetone","meetonetest1","100000000.0000 MEETONE","memo"]' -p eosiomeetone
```
```
cleos push action eosiomeetone transfer '["meetonetest1","eosiomeetone","100000000.0000 MEETONE","memo"]' -p meetonetest1
```


### Check Balance

```
cleos get currency balance eosiomeetone meetonetest1
```
```
cleos get currency balance eosiomeetone eosiomeetone
```
```
cleos get currency stats eosiomeetone MEETONE
```

