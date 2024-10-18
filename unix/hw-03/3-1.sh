#!/bin/bash

var=defined
echo $var
echo ${var:-default}
echo ${var1:-deault}
echo $var1
echo ${var1:=string}
echo $var1
echo ${var:+new}

