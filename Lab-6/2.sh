#/usr/bin/env bash
if (( $# < 2 ))
then
  echo "Usage:"
  echo "\$1 - encryption (aes-128-cbc for example. ./manual.sh for help)"
  echo "\$2 - secret"
  echo "\$3 - file name"
  echo "aborted"
  exit
fi
echo "Encrypt $3"
openssl enc -e -$1 -in $3 -out task1_"$3".enc -k $2
echo "Complete."
