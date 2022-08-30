#!/bin/bash

#------------------------------------------------------------------------------
#
# Source code for MIPT course on informatics
# Page with slides: http://cs.mipt.ru/wp/?page_id=7775
# Licensed after GNU GPL v3
#
#------------------------------------------------------------------------------
#
# shifting and arithmetical substitution in bash
#
# Try:
# $ ./shifted.sh carl clara 'john smith' "martin luther king"
#
#------------------------------------------------------------------------------

i=1;
j=$#;
while [ $i -le $j ] 
do
  echo "Param $i: $1";
  i=$((i + 1));
  shift 1;
done
