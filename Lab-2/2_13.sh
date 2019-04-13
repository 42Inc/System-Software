#!/usr/bin/env bash
FILE=$HOME/.bashrc
RUN=0
COMPILE=0
RESULT=0

while getopts "f:crd:" opt
do
case $opt in
f) FILE=$OPTARG;;
c) COMPILE=1;;
r) RUN=1;;
d) DIR=$OPTARG;;
esac
done

if [[ $DIR ]]
then
  if [ -d $DIR ]
  then
    ls $DIR
  fi
fi

if [[ $FILE ]]
then
  if [ -f $FILE ]
  then
    cat $FILE
  fi
fi

if [[ $COMPILE == 1 ]]
then
  if [[ $FILE ]]
  then
    if [ -f $FILE ]
    then
      RESULT="$(gcc $FILE)"
    fi
  fi
fi

if [[ $RUN == 1 ]]
then
  if [[ $RESULT ]]
  then
    ./a.out
  fi
fi
