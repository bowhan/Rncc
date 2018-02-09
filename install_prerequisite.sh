#!/bin/bash

declare -r LemonSource='http://lemon.cs.elte.hu/pub/sources/lemon-1.3.1.tar.gz'
declare -r LemonDir='lemon-1.3.1'
curl "${LemonSource}" | tar xvzf -
cd $LemonDir && mkdir build && cd build && cmake .. && make && sudo make install