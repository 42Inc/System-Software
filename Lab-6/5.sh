#/usr/bin/env bash
if (( $# < 2 ))
then
  echo "Usage:"
  echo "\$1 - key file"
  echo "\$2 - file name"
  echo "aborted"
  exit
fi
echo "Encrypt $2"
openssl rsautl -encrypt -inkey $1.pub -pubin -in $2 -out task2_"$2".enc
echo "Complete."
