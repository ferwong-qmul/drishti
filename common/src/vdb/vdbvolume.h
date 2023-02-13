#ifndef VDBVOLUME
#define VDBVOLUME

#include <QVector>
#include <QVector3D>
#include <QVector4D>

// To jointly use QT and OpenVDB use the following preprocessor instruction
// before including openvdb.h.  The problem arises because Qt defines a Q_FOREACH
// macro which conflicts with the foreach methods in 'openvdb/util/NodeMask.h'.
// To remove this conflict, just un-define this macro wherever both openvdb and Qt
// are being included together. 
#ifdef foreach
  #undef foreach
#endif
// tbb/profiling.h has a function called emit()
// hence need to undef emit keyword in Qt
#undef emit
// a workaround to avoid imath_half_to_float_table linker error
#define IMATH_HALF_NO_LOOKUP_TABLE
#include <openvdb/openvdb.h>
#include <openvdb/Grid.h>
#include <math.h>

class VdbVolume
{
 public :
  VdbVolume();
  ~VdbVolume();
  
  void generateVDB(unsigned char*, int, int, int);

  void mean(int width=1, int iterations=1);
  void gaussian(int width=1, int iterations=1);
  void dilate(int iter=1);
  
  void generateMesh(double isovalue, QVector<QVector3D>&, QVector<QVector3D>&, QVector<int>&);
  

 private :
  openvdb::FloatGrid::Ptr m_vdbGrid; 
};


#endif VDBVOLUME
