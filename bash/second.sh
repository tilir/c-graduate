#!/bin/bash

#------------------------------------------------------------------------------
#
# Source code for MIPT course on informatics
# Page with slides: http://cs.mipt.ru/wp/?page_id=7775
# Licensed after GNU GPL v3
#
#------------------------------------------------------------------------------
#
# Script creating files in folder
#
#------------------------------------------------------------------------------

mkdir -p $folder
for i in $(seq 1 1 $border)
do
  echo "processing: $i"
  echo $i > "myfolder/$i.in"
done
