TEMPLATE = subdirs

SUBDIRS = analyze \
          dicom \
          grd \
	  imagestack \
	  metaimage \
          nc \
	  raw \
	  rawslabs \
	  rawslices \
	  tiff \
	  tom \
	  txm \
          vgi
          
win32 {
SUBDIRS += nc4 \
           nifti \
           nrrd
}
