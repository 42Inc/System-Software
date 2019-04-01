#/usr/bin/env bash
if (( $# < 3 ))
then
  echo "Usage:"
  echo "\$1 - encryption (aes-128-cbc for example. ./manual.sh for help)"
  echo "\$2 - secret"
  echo "\$3 - file name"
  echo "aborted"
  exit
fi
echo "Decrypt task1_$3.enc"
openssl enc -d -$1 -in task1_"$3".enc -out task1_"$3".dec -k $2
echo "Complete."
