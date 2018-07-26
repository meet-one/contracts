echo "account meetonexdemo:"
cleos get currency balance eosiomeetone meetonexdemo
echo "account eosiomeetone:"
cleos get currency balance eosiomeetone eosiomeetone

cleos push action eosiomeetone transfer '["eosiomeetone","meetonexdemo","10000.0000 MEETONE","Hello world."]' -p eosiomeetone

echo "account meetonexdemo:"
cleos get currency balance eosiomeetone meetonexdemo
echo "account eosiomeetone:"
cleos get currency balance eosiomeetone eosiomeetone