#! /bin/bash

set -x

lshw -C display
lspci | grep "VGA"
