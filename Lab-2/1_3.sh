#!/usr/bin/env bash
mkdir $HOME/cat1
mkdir $HOME/cat1/cat2
mkdir $HOME/cat1/cat3
mkdir $HOME/cat1/cat2/cat3
mkdir $HOME/cat1/cat3/cat4
mkdir $HOME/cat1/cat2/cat5
mkdir $HOME/cat1/cat2/cat3/cat6
mkdir $HOME/cat1/cat2/cat3/cat7
mkdir $HOME/cat1/cat8
ln -s $HOME/cat1/cat2/cat3/cat6 $HOME/cat1/cat8/link
