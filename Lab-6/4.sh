#/usr/bin/env bash
if (( $# < 3 ))
then
  echo "Usage:"
  echo "\$1 - alghoritm (rsa/dsa)"
  echo "\$2 - key file name"
  echo "\$3 - length key"
  echo "aborted"
  exit
fi
echo "Generate private key..."
openssl gen$1 -out $2.pem $3
echo "Generate public key..."
openssl $1 -in $2.pem -pubout -out $2.pem.pub
echo "Complete."
