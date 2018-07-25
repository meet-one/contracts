eosiocpp -o meetonexdemo.wast meetonexdemo.cpp
cleos set contract meetonexdemo ../meetonexdemo -p meetonexdemo@active
cleos push action eosiomeetone transfer '["eosiomeetone","meetonexdemo","100.0000 MEETONE","Hello world."]' -p eosiomeetone
