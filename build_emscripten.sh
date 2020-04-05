#!/bin/bash
./configure --without-zlib --without-lzo2 --without-sse --without-lzma --without-threads --enable-dedicated
make -C objs/lang clean all
make -C objs/setting clean all
emconfigure sh -c 'PKG_CONFIG_PATH=/extralibs/lib/pkgconfig ./configure --ignore-extra-parameters --without-lzo2 --without-sse --without-threads --without-zlib --without-lzma --with-sigaction="0" --with-sigaltstack="0"'
emmake make
