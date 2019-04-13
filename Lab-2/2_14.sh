#!/usr/bin/env bash

for i in `find -type f -name "*.txt"` ;
do
  cat $i >> ~/texttx.txt
done
