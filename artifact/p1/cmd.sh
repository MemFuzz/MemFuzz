giflib: ./gif2rgb @@
libjpeg: ./djpeg @@
mozjpeg: ./djpeg @@
libpng: ./pngfix @@
libzip: ./ziptool -c @@ cat 0
openjpeg: ./opj_compress -i @@.png -o b.jp2
miniz: ./open @@
podofo: ./podofoload @@
xpdf: ./pdfinfo @@
poppler: ./pdfinfo @@
xfig: ./xfig -update @@
zlib: ./minizip @@
qpdf: ./qpdf @@
imageMagick: ./readWriteImages @@
mupdf: ./mutool draw @@

