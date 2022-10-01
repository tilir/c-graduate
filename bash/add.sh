#!/bin/bash

#------------------------------------------------------------------------------
#
# Source code for MIPT course on informatics
# Page with slides: http://cs.mipt.ru/wp/?page_id=7775
# Licensed after GNU GPL v3
#
#------------------------------------------------------------------------------
#
# function example in bash
#
#------------------------------------------------------------------------------

function myfunc {
  local value=$(( $1 + $2 )) 
  echo $value
}

value=100
myfunc 10 15
echo $value
