#!/bin/bash
./configure --with-zlib --without-lzo2 --without-sse --without-lzma --without-threads --enable-dedicated
make -C objs/lang all
make -C objs/setting all
emconfigure sh -c './configure --ignore-extra-parameters --without-lzo2 --without-sse --without-threads --with-zlib --without-lzma --with-sigaction="0" --with-sigaltstack="0"' CFLAGS="-s USE_ZLIB=1" LDFLAGS="-s USE_ZLIB=1"
emmake make -j$(nproc)
