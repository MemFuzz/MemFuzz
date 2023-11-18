giflib: gif2rgb @@
libjpeg: djpeg_libjpeg -bmp @@
mozjpeg: djpeg_moz -bmp @@
libpng: pngfix @@
libzip: ziptool -c @@ cat 0
openjpeg: opj_decompress -i @@.jp2 -o b.bmp
miniz: extract @@
podofo: podofocolor dummy @@ /dev/null
xpdf: pdftops_xpdf -f 2 -l 4 -level2 -noembt1 -preload -nocrop -noshrink -nocenter -pagecrop -userunit -duplex -upw rome @@ /dev/null
poppler: pdftops_poppler -f 2 -l 4 -level2 -noembt1 -preload -nocrop -noshrink -nocenter -pagecrop -userunit -duplex -upw rome @@ /dev/null
xfig: fig2dev @@ -L pdf /tmp/null
zlib: miniunz -l @@
qpdf: qpdf @@ /dev/null
imageMagick: convert @@ /tmp/a.jpg
mupdf: mutool draw @@

