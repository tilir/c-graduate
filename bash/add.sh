#!/bin/bash
function myfunc {
  local value=$(( $1 + $2 )) 
  echo $value
}

value=100
myfunc 10 15
echo $value
