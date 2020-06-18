#!/bin/bash
cd "${0%/*}"
emmake make -C .. -j4 &&
cp ../bin/openttd openttd.bc &&
rm -f ../bin/openttd ../bin/openttd.exe &&
emcc openttd.bc -o final_html/index.html -O0 -s USE_SDL=2 -s USE_ZLIB=1 -s STB_IMAGE=1 -s ALLOW_MEMORY_GROWTH=1 --preload-file ../bin@/ --preload-file content@/ --pre-js pre.js --shell-file shell.html -s TOTAL_MEMORY=39714816 -s ERROR_ON_UNDEFINED_SYMBOLS=0  -s FORCE_FILESYSTEM=1 -lidbfs.js
