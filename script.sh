#! /bin/sh
#
# run.sh
# Copyright (C) 2015 gbersac <gbersac@e2r3p18.42.fr>
#
# Distributed under terms of the MIT license.
#


#!/bin/sh 
DYLD_LIBRARY_PATH=. \
DYLD_INSERT_LIBRARIES="ft_malloc.so" \ 
DYLD_FORCE_FLAT_NAMESPACE=1 \
$@

