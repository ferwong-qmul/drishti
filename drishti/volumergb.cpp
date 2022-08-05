#include "global.h"
#include "volumergb.h"
#include "staticfunctions.h"
#include "mainwindowui.h"
#include "xmlheaderfunctions.h"

#include <QFileDialog>

Vec VolumeRGB::getSubvolumeMin() { return m_dataMin; }
Vec VolumeRGB::getSubvolumeMax() { return m_dataMax; }

Vec VolumeRGB::getSubvolumeSize() { return m_subvolumeSize; }
Vec VolumeRGB::getSubvolumeTextureSize() { return m_subvolumeTextureSize; }
int VolumeRGB::getSubvolumeSubsamplingLevel() { return m_subvolumeSubsamplingLevel; }
unsigned char* VolumeRGB::getSubvolumeTexture() { return m_subvolumeTexture; }

Vec VolumeRGB::getDragSubvolumeTextureSize() { return m_dragSubvolumeTextureSize; }
int VolumeRGB::getDragSubvolumeSubsamplingLevel() { return m_dragSubvolumeSubsamplingLevel; }
uchar* VolumeRGB::getDragSubvolumeTexture() { return m_dragSubvolumeTexture; }

QList<QString> VolumeRGB::volumeFiles() { return m_volumeFiles; }

int*
VolumeRGB::getSubvolume1dHistogram(int vn)
{
  if (vn == 0)
    return m_subvolume1dHistogramR;
  if (vn == 1)
    return m_subvolume1dHistogramG;
  if (vn == 2)
    return m_subvolume1dHistogramB;
  if (vn == 3)
    return m_subvolume1dHistogramA;

  return 0;
}
int*
VolumeRGB::getDrag1dHistogram(int vn)
{
  if (vn == 0)
    return m_drag1dHistogramR;
  if (vn == 1)
    return m_drag1dHistogramG;
  if (vn == 2)
    return m_drag1dHistogramB;
  if (vn == 3)
    return m_drag1dHistogramA;

  return 0;
}

int*
VolumeRGB::getSubvolume2dHistogram(int vn)
{
  if (vn == 0)
    return m_subvolume2dHistogramR;
  if (vn == 1)
    return m_subvolume2dHistogramG;
  if (vn == 2)
    return m_subvolume2dHistogramB;
  if (vn == 3)
    return m_subvolume2dHistogramA;

  return 0;
}
int*
VolumeRGB::getDrag2dHistogram(int vn)
{
  if (vn == 0)
    return m_drag2dHistogramR;
  if (vn == 1)
    return m_drag2dHistogramG;
  if (vn == 2)
    return m_drag2dHistogramB;
  if (vn == 3)
    return m_drag2dHistogramA;

  return 0;
}

void
VolumeRGB::setVolumeFiles(QList<QString> volfiles)
{
  m_volumeFiles.clear();
  m_volumeFiles += volfiles;
}

VolumeRGB::VolumeRGB() :
  VolumeRGBBase()
{
  m_volnum = 0;
  m_dataMin = Vec(0,0,0);
  m_dataMax = Vec(0,0,0);
  
  m_volumeFiles.clear();

  m_dragSubvolumeTexture = 0;
  m_subvolumeTexture = 0;

  m_subvolume1dHistogramR = new int[256];
  m_subvolume2dHistogramR = new int[256*256];

  m_subvolume1dHistogramG = new int[256];
  m_subvolume2dHistogramG = new int[256*256];

  m_subvolume1dHistogramB = new int[256];
  m_subvolume2dHistogramB = new int[256*256];

  m_subvolume1dHistogramA = new int[256];
  m_subvolume2dHistogramA = new int[256*256];

  memset(m_subvolume1dHistogramR, 0, 256*4);
  memset(m_subvolume2dHistogramR, 0, 256*256*4);

  memset(m_subvolume1dHistogramG, 0, 256*4);
  memset(m_subvolume2dHistogramG, 0, 256*256*4);

  memset(m_subvolume1dHistogramB, 0, 256*4);
  memset(m_subvolume2dHistogramB, 0, 256*256*4);

  memset(m_subvolume1dHistogramA, 0, 256*4);
  memset(m_subvolume2dHistogramA, 0, 256*256*4);



  m_drag1dHistogramR = new int[256];
  m_drag2dHistogramR = new int[256*256];

  m_drag1dHistogramG = new int[256];
  m_drag2dHistogramG = new int[256*256];

  m_drag1dHistogramB = new int[256];
  m_drag2dHistogramB = new int[256*256];

  m_drag1dHistogramA = new int[256];
  m_drag2dHistogramA = new int[256*256];

  memset(m_drag1dHistogramR, 0, 256*4);
  memset(m_drag2dHistogramR, 0, 256*256*4);

  memset(m_drag1dHistogramG, 0, 256*4);
  memset(m_drag2dHistogramG, 0, 256*256*4);

  memset(m_drag1dHistogramB, 0, 256*4);
  memset(m_drag2dHistogramB, 0, 256*256*4);

  memset(m_drag1dHistogramA, 0, 256*4);
  memset(m_drag2dHistogramA, 0, 256*256*4);



  m_flhist1DR = new float[256];     
  m_flhist2DR = new float[256*256]; 
  m_flhist1DG = new float[256];     
  m_flhist2DG = new float[256*256]; 
  m_flhist1DB = new float[256];     
  m_flhist2DB = new float[256*256]; 
  m_flhist1DA = new float[256];     
  m_flhist2DA = new float[256*256]; 

  m_sliceTemp = 0;

  m_texColumns = 0;
  m_texRows = 0;
}

VolumeRGB::~VolumeRGB()
{
  if(m_flhist1DR) delete [] m_flhist1DR;
  if(m_flhist2DR) delete [] m_flhist2DR;
  if(m_flhist1DG) delete [] m_flhist1DG;
  if(m_flhist2DG) delete [] m_flhist2DG;
  if(m_flhist1DB) delete [] m_flhist1DB;
  if(m_flhist2DB) delete [] m_flhist2DB;
  if(m_flhist1DA) delete [] m_flhist1DA;
  if(m_flhist2DA) delete [] m_flhist2DA;
  m_flhist1DR = 0;
  m_flhist2DR = 0;
  m_flhist1DG = 0;
  m_flhist2DG = 0;
  m_flhist1DB = 0;
  m_flhist2DB = 0;
  m_flhist1DA = 0;
  m_flhist2DA = 0;

  if(m_dragSubvolumeTexture) delete [] m_dragSubvolumeTexture;
  if(m_subvolumeTexture) delete [] m_subvolumeTexture;

  if(m_subvolume1dHistogramR) delete [] m_subvolume1dHistogramR;
  if(m_subvolume2dHistogramR) delete [] m_subvolume2dHistogramR;
  if(m_subvolume1dHistogramG) delete [] m_subvolume1dHistogramG;
  if(m_subvolume2dHistogramG) delete [] m_subvolume2dHistogramG;
  if(m_subvolume1dHistogramB) delete [] m_subvolume1dHistogramB;
  if(m_subvolume2dHistogramB) delete [] m_subvolume2dHistogramB;
  if(m_subvolume1dHistogramA) delete [] m_subvolume1dHistogramA;
  if(m_subvolume2dHistogramA) delete [] m_subvolume2dHistogramA;

  m_subvolumeTexture = 0;
  m_subvolume1dHistogramR = 0;
  m_subvolume2dHistogramR = 0;
  m_subvolume1dHistogramG = 0;
  m_subvolume2dHistogramG = 0;
  m_subvolume1dHistogramB = 0;
  m_subvolume2dHistogramB = 0;
  m_subvolume1dHistogramA = 0;
  m_subvolume2dHistogramA = 0;


  if(m_drag1dHistogramR) delete [] m_drag1dHistogramR;
  if(m_drag2dHistogramR) delete [] m_drag2dHistogramR;
  if(m_drag1dHistogramG) delete [] m_drag1dHistogramG;
  if(m_drag2dHistogramG) delete [] m_drag2dHistogramG;
  if(m_drag1dHistogramB) delete [] m_drag1dHistogramB;
  if(m_drag2dHistogramB) delete [] m_drag2dHistogramB;
  if(m_drag1dHistogramA) delete [] m_drag1dHistogramA;
  if(m_drag2dHistogramA) delete [] m_drag2dHistogramA;

  m_drag1dHistogramR = 0;
  m_drag2dHistogramR = 0;
  m_drag1dHistogramG = 0;
  m_drag2dHistogramG = 0;
  m_drag1dHistogramB = 0;
  m_drag2dHistogramB = 0;
  m_drag1dHistogramA = 0;
  m_drag2dHistogramA = 0;


  m_volumeFiles.clear();

  if(m_sliceTemp) delete [] m_sliceTemp;
  m_sliceTemp = 0;
}

bool
VolumeRGB::loadVolume(const char *flnm, bool redo)
{
  m_volnum = 0;
  m_dataMin = Vec(0,0,0);
  m_dataMax = Vec(0,0,0);

  m_volumeFiles.clear();
  m_volumeFiles.append(flnm);

  VolumeInformation vInfo;
  VolumeInformation::setVolumeInformation(vInfo);

  bool ok = VolumeRGBBase::loadVolume(flnm, redo);

  int nRGB = 3;
  if (Global::volumeType() == Global::RGBAVolume)
    nRGB = 4;
  m_sliceTemp = new unsigned char [nRGB*m_width*m_height];

  return ok;
}

bool
VolumeRGB::setSubvolume(Vec boxMin, Vec boxMax,
			int volnum,
			bool force)
{  
  if (Global::volumeType() != Global::DummyVolume &&
      volnum >= m_volumeFiles.count())
    {
      QMessageBox::information(0, "SubVolume Update",
			       QString("%1 greater than %2 volumes").\
			       arg(volnum).\
			       arg(m_volumeFiles.count()));
      return false;
    }

  int n_depth, n_width, n_height;

  XmlHeaderFunctions::getDimensionsFromHeader(m_volumeFiles[volnum],
					      n_depth, n_width, n_height);

  //----------------
  int nRGB = 3;
  if (Global::volumeType() == Global::RGBAVolume)
    nRGB = 4;
  //---------------

  int slabSize = XmlHeaderFunctions::getSlabsizeFromHeader(m_volumeFiles[volnum]);
  QString rgbfile = m_volumeFiles[volnum];
  rgbfile.chop(6);
  VolumeFileManager rgbaFileManager[4];
  QString rFilename = rgbfile + QString("red");
  QString gFilename = rgbfile + QString("green");
  QString bFilename = rgbfile + QString("blue");
  QString aFilename = rgbfile + QString("alpha");

  m_rgbaFileManager[0].setBaseFilename(rFilename);
  m_rgbaFileManager[1].setBaseFilename(gFilename);
  m_rgbaFileManager[2].setBaseFilename(bFilename);
  m_rgbaFileManager[3].setBaseFilename(aFilename);
  for(int a=0; a<nRGB; a++)
    {
      m_rgbaFileManager[a].setDepth(n_depth);
      m_rgbaFileManager[a].setWidth(n_width);
      m_rgbaFileManager[a].setHeight(n_height);
      m_rgbaFileManager[a].setHeaderSize(13);
      m_rgbaFileManager[a].setSlabSize(slabSize);
    }
  //----------------


  boxMin = StaticFunctions::clampVec(Vec(0,0,0),
				     boxMin,
				     Vec(n_height-1, n_width-1, n_depth-1));
  boxMax = StaticFunctions::clampVec(Vec(0,0,0),
				     boxMax,
				     Vec(n_height-1, n_width-1, n_depth-1));

  if (force == false)
    {
      if (m_volnum == volnum &&
	  (m_dataMin-boxMin).squaredNorm() < 0.1 &&
	  (m_dataMax-boxMax).squaredNorm() < 0.1)
	// no change in dataMin and dataMax values
	  return false;
    }

  m_volnum = volnum;
  m_dataMin = boxMin;
  m_dataMax = boxMax;

  m_subvolumeSize = m_dataMax - m_dataMin + Vec(1,1,1); 

  int availMem = Global::textureMemorySize()-8*Global::actualDragVolSize();
  m_subvolumeSubsamplingLevel = StaticFunctions::getSubsamplingLevel(availMem,
								     Global::maxArrayTextureLayers(),
								     nRGB, boxMin, boxMax);

  //-------------
  int lenx = m_subvolumeSize.x;
  int leny = m_subvolumeSize.y;
  int lenz = m_subvolumeSize.z;
  int lenx2 = lenx/m_subvolumeSubsamplingLevel;
  int leny2 = leny/m_subvolumeSubsamplingLevel;
  int lenz2 = lenz/m_subvolumeSubsamplingLevel;
  m_subvolumeTextureSize = Vec(lenx2, leny2, lenz2);
  //-------------

  if (m_subvolumeTexture) delete [] m_subvolumeTexture;
  m_subvolumeTexture = 0;

  if (m_dragSubvolumeTexture) delete [] m_dragSubvolumeTexture;
  m_dragSubvolumeTexture = 0;

  return true;
}

VolumeInformation
VolumeRGB::volInfo(int vnum)
{
  VolumeInformation pvlInfo;

  if (vnum < 0 || vnum >= m_volumeFiles.count())
    {
      QMessageBox::information(0, "Volume Information",
			       QString("%1 greater than %2 volumes").\
			       arg(vnum).\
			       arg(m_volumeFiles.count()));
      VolumeInformation::setVolumeInformation(pvlInfo);
      return pvlInfo;
    }


  if (VolumeInformation::volInfo(m_volumeFiles[vnum].toLatin1().data(),
				 pvlInfo) == false)
    {
      QMessageBox::information(0, "Volume Information",
			       QString("Invalid netCDF file %1").\
			       arg(m_volumeFiles[vnum]));
    }
  else
    {
      Global::setRelativeVoxelScaling(pvlInfo.relativeVoxelScaling);
      VolumeInformation::setVolumeInformation(pvlInfo);
    }

  return pvlInfo;
}

void
VolumeRGB::getColumnsAndRows(int &ncols, int &nrows)
{
  ncols = m_texColumns;
  nrows = m_texRows;
}

void
VolumeRGB::getSliceTextureSize(int& texX, int& texY)
{
  texX = m_texWidth;
  texY = m_texHeight;
}

Vec VolumeRGB::getDragTextureInfo() { return m_dragTextureInfo; }

void
VolumeRGB::getDragTextureSize(int& dtexX, int& dtexY)
{
  dtexX = m_dragTexWidth;
  dtexY = m_dragTexHeight;
}


QList<Vec>
VolumeRGB::getSliceTextureSizeSlabs()
{
  //---------------
  int nRGB = 3;
  if (Global::volumeType() == Global::RGBAVolume)
    nRGB = 4;
  //---------------

  MainWindowUI::mainWindowUI()->menubar->parentWidget()->\
    setWindowTitle(QString("Generating slabs limits"));
  Global::progressBar()->show();

  int nrows, ncols;
  QList<Vec> slabinfo = Global::getSlabs(m_subvolumeSubsamplingLevel,
					 nRGB,
					 m_dataMin, m_dataMax,
					 nrows, ncols);

  if (slabinfo.count() > 1)
    {
      m_dragTextureInfo = slabinfo[0];
      int dlenx2 = int(m_subvolumeSize.x)/int(m_dragTextureInfo.z);
      int dleny2 = int(m_subvolumeSize.y)/int(m_dragTextureInfo.z);
      m_dragTexWidth = int(m_dragTextureInfo.x)*dlenx2;
      m_dragTexHeight = int(m_dragTextureInfo.y)*dleny2;
    }
  else
    {
      m_dragTextureInfo = Vec(ncols, nrows, m_subvolumeSubsamplingLevel);
      int dlenx2 = int(m_subvolumeSize.x)/m_subvolumeSubsamplingLevel;
      int dleny2 = int(m_subvolumeSize.y)/m_subvolumeSubsamplingLevel;
      m_dragTexWidth = ncols*dlenx2;
      m_dragTexHeight = nrows*dleny2;
    }

  Global::progressBar()->setValue(10);
  
  m_texColumns = ncols;
  m_texRows = nrows;

  int lenx = m_subvolumeSize.x;
  int leny = m_subvolumeSize.y;
  int lenx2 = lenx/m_subvolumeSubsamplingLevel;
  int leny2 = leny/m_subvolumeSubsamplingLevel;

  m_texWidth = ncols*lenx2;
  m_texHeight = nrows*leny2;

  Global::progressBar()->setValue(50);

  Global::progressBar()->setValue(100);
  Global::hideProgressBar();

  return slabinfo;
}

//----------------------------
// for array texture
//----------------------------
uchar*
VolumeRGB::getSubvolume()
{
  //---------------
  int nRGB = 3;
  if (Global::volumeType() == Global::RGBAVolume)
    nRGB = 4;
  //---------------

  int lod = m_subvolumeSubsamplingLevel;

  int minx = m_dataMin.x;
  int miny = m_dataMin.y;
  int minz = m_dataMin.z;
  
  int maxx = m_dataMax.x;
  int maxy = m_dataMax.y;
  int maxz = m_dataMax.z;

  int lenx = m_subvolumeSize.x;
  int leny = m_subvolumeSize.y;
  int lenz = m_subvolumeSize.z;

  int lenx2 = m_subvolumeTextureSize.x;
  int leny2 = m_subvolumeTextureSize.y;
  int lenz2 = m_subvolumeTextureSize.z;

  //-------- for dragTexure ---------------
  int dtlod = m_dragTextureInfo.z;
  int dtlenx2 = lenx/dtlod;
  int dtleny2 = leny/dtlod;
  int dtlenz2 = lenz/dtlod;
  float stp = (float)dtlod/(float)m_subvolumeSubsamplingLevel;
  //---------------------------------------


  m_dragSubvolumeSubsamplingLevel = dtlod;
  m_dragSubvolumeTextureSize = Vec(dtlenx2, dtleny2, dtlenz2);
  
  if (m_subvolumeTexture) delete [] m_subvolumeTexture;
  if (m_dragSubvolumeTexture) delete [] m_dragSubvolumeTexture;

  m_subvolumeTexture = new uchar[nRGB*lenx2*leny2*lenz2];
  m_dragSubvolumeTexture = new uchar[nRGB*dtlenx2*dtleny2*dtlenz2];

  Global::progressBar()->show();

  int totcount = 2*lod-1;
  int count=0;
  unsigned char **volX;
  volX = 0;
  if (lod > 1)
    {
      volX = new unsigned char*[totcount];
      for(int i=0; i<totcount; i++)
	volX[i] = new unsigned char[nRGB*leny2*lenx2];
    }  

  int nbytes = m_width*m_height;
  uchar *tmp = new uchar[nRGB*nbytes];

  int kmin = minz/m_subvolumeSubsamplingLevel;
  int kmax = maxz/m_subvolumeSubsamplingLevel;

  int imin = minx/m_subvolumeSubsamplingLevel;
  int jmin = miny/m_subvolumeSubsamplingLevel;
  
  int kslc = 0;

  // additional slice at the top and bottom
  for(int k=minz; k<=maxz; k++)
    {
      Global::progressBar()->setValue((int)(100.0*(float)(kslc)/(float)(lenz2)));
      if (kslc%100==0) qApp->processEvents();

      if (k >= 0 && k < m_depth)
	{
	  for (int a=0; a<nRGB; a++)
	    {
	      uchar *vslice = m_rgbaFileManager[a].getSlice(k);
	      memcpy(tmp, vslice, nbytes);

	      for (int ij=0; ij<m_width*m_height; ij++)
		m_sliceTemp[nRGB*ij+a] = tmp[ij];
	    }
	}
      else
	{
	  memset(m_sliceTemp, 0, nRGB*m_width*m_height);
	}

      bool doHist = false;
      //------------------------
      if (lod > 1)
	{
	  int ji=0;
	  for(int j=0; j<leny2; j++)
	    { 
	      int y = miny + j*lod;
	      int loy = qMax(miny+0, y-lod+1);
	      int hiy = qMin(miny+leny-1, y+lod-1);
	      for(int i=0; i<lenx2; i++) 
		{ 
		  int x = minx + i*lod; 
		  int lox = qMax(minx+0, x-lod+1); 
		  int hix = qMin(minx+lenx-1, x+lod-1);
		  float sumv[4] = {0, 0, 0, 0}; 
		  for(int jy=loy; jy<=hiy; jy++) 
		    {
		      for(int ix=lox; ix<=hix; ix++) 
			{
			  int idx = jy*m_height+ix;
			  for(int a=0; a<nRGB; a++)
			    sumv[a] += m_sliceTemp[nRGB*idx+a];
			}
		    }

		  for(int a=0; a<nRGB; a++)
		    tmp[nRGB*ji+a] = sumv[a]/((hiy-loy+1)*(hix-lox+1)); 

		  ji++;
		}
	    }
	  memcpy(m_sliceTemp, tmp, nRGB*leny2*lenx2);

	  unsigned char *vptr;
	  vptr = volX[0];
	  for (int c=0; c<totcount-1; c++)
	    volX[c] = volX[c+1];
	  volX[totcount-1] = vptr;
	  
	  memcpy(volX[totcount-1], m_sliceTemp, nRGB*leny2*lenx2);
      
	  count ++;
	  if (count == totcount)
	    {
	      for(int j=0; j<nRGB*leny2*lenx2; j++)
		{
		  float sum=0;
		  for(int x=0; x<totcount; x++)
		    sum += volX[x][j];
		  m_sliceTemp[j] = sum/totcount;
		}
	      
	      count = totcount/2;

	      
	      // copy into array texture
	      memcpy(m_subvolumeTexture + nRGB*kslc*lenx2*leny2,
		     m_sliceTemp,
		     nRGB*lenx2*leny2);
	      //---

	      //---
	      int ji=0;
	      for(int j=0; j<dtleny2; j++)
		{ 
		  int y = j*stp;
		  for(int i=0; i<dtlenx2; i++) 
		    { 
		      int x = i*stp; 
		      for(int a=0; a<nRGB; a++)
			tmp[nRGB*ji+a] = m_sliceTemp[nRGB*(y*lenx2+x)+a];
		      ji++;
		    }
		}
	      // copy into drag array texture
	      int dtkslc = qBound(0, (int)(kslc/stp), dtlenz2-1);
	      memcpy(m_dragSubvolumeTexture + nRGB*dtkslc*dtlenx2*dtleny2,
		     tmp,
		     nRGB*dtlenx2*dtleny2);
	      //---

	      
	      doHist = true;
	    }
	} // lod > 1
      //------------------------
      else
	{
	  for(int j=0; j<leny2; j++)
	    memcpy(m_sliceTemp + nRGB*j*lenx2,
		   m_sliceTemp + nRGB*((j+miny)*m_height + minx),
		   nRGB*lenx2);

	  // copy into array texture
	  memcpy(m_subvolumeTexture + nRGB*kslc*lenx2*leny2,
		 m_sliceTemp,
		 nRGB*lenx2*leny2);
	  //---

	  //---
	  int ji=0;
	  for(int j=0; j<dtleny2; j++)
	    { 
	      int y = j*stp;
	      for(int i=0; i<dtlenx2; i++) 
		{ 
		  int x = i*stp; 
		  for(int a=0; a<nRGB; a++)
		    tmp[nRGB*ji+a] = m_sliceTemp[nRGB*(y*lenx2+x)+a];
		  ji++;
		}
	    }
	  // copy into drag array texture
	  int dtkslc = qBound(0, (int)(kslc/stp), dtlenz2-1);
	  memcpy(m_dragSubvolumeTexture + nRGB*dtkslc*dtlenx2*dtleny2,
		 tmp,
		 nRGB*dtlenx2*dtleny2);
	  //---

	  
	  doHist = true;
	}
      //---------------------
      for(int ji=0; ji<leny2*lenx2; ji++)
	{
	  uchar r = m_sliceTemp[nRGB*ji];
	  uchar g = m_sliceTemp[nRGB*ji+1];
	  uchar b = m_sliceTemp[nRGB*ji+2];
	  
	  m_flhist1DR[r]++;  m_flhist2DR[g*256 + r]++;
	  m_flhist1DG[g]++;  m_flhist2DG[b*256 + g]++;
	  m_flhist1DB[b]++;  m_flhist2DB[r*256 + b]++;

	  if (nRGB == 4)
	    {
	      uchar a = m_sliceTemp[nRGB*ji+3];
	      uchar rgb = qMax(r, qMax(g, b));
	      m_flhist1DA[a]++; m_flhist2DA[rgb*256 + a]++;
	    }
	}
      //---------------------

      kslc ++;
    } // look over k
  
  delete [] tmp;

  if (lod > 1)
    {
      for(int i=0; i<totcount; i++)
	delete [] volX[i];
      delete [] volX;
    }

  Global::progressBar()->setValue(100);
  MainWindowUI::mainWindowUI()->statusBar->showMessage("Ready");

  return m_subvolumeTexture;
}


void
VolumeRGB::startHistogramCalculation()
{
  memset(m_flhist1DR, 0, 256*4);
  memset(m_flhist2DR, 0, 256*256*4);
  memset(m_flhist1DG, 0, 256*4);
  memset(m_flhist2DG, 0, 256*256*4);
  memset(m_flhist1DB, 0, 256*4);
  memset(m_flhist2DB, 0, 256*256*4);
  memset(m_flhist1DA, 0, 256*4);
  memset(m_flhist2DA, 0, 256*256*4);
}

void
VolumeRGB::endHistogramCalculation()
{
  StaticFunctions::generateHistograms(m_flhist1DR, m_flhist2DR,
				      m_subvolume1dHistogramR,
				      m_subvolume2dHistogramR);
  StaticFunctions::generateHistograms(m_flhist1DG, m_flhist2DG,
				      m_subvolume1dHistogramG,
				      m_subvolume2dHistogramG);
  StaticFunctions::generateHistograms(m_flhist1DB, m_flhist2DB,
				      m_subvolume1dHistogramB,
				      m_subvolume2dHistogramB);
  if (Global::volumeType() == Global::RGBAVolume)
    StaticFunctions::generateHistograms(m_flhist1DA, m_flhist2DA,
					m_subvolume1dHistogramA,
					m_subvolume2dHistogramA);
}


void
VolumeRGB::maskRawVolume(unsigned char *lut,
			 QList<Vec> clipPos,
			 QList<Vec> clipNormal,
			 QList<CropObject> crops)
{
  QString imgflnm;
  imgflnm = QFileDialog::getSaveFileName(0,
			 "Save images with basename as",
		         Global::previousDirectory(),
			 "Image Files (*.png *.tif *.bmp *.jpg)");

  if (imgflnm.isEmpty())
    return;

  QFileInfo f(imgflnm);	
  QChar fillChar = '0';
  QImage timage;

  MainWindowUI::mainWindowUI()->menubar->parentWidget()->setWindowTitle("Saving image stack");
  Global::progressBar()->show();

  //---------------
  int nRGB = 3;
  if (Global::volumeType() == Global::RGBAVolume)
    nRGB = 4;
  //---------------


  int minx = m_dataMin.x;
  int maxx = m_dataMax.x;
  int miny = m_dataMin.y;
  int maxy = m_dataMax.y;
  int minz = m_dataMin.z;
  int maxz = m_dataMax.z;
  int lenx = m_subvolumeSize.x;
  int leny = m_subvolumeSize.y;
  int lenz = m_subvolumeSize.z;

  Vec voxelScaling = Global::voxelScaling();

  uchar *vol;
  vol = new uchar[4*leny*lenx];

  uchar *rgb;
  rgb = new uchar[4*leny*lenx];


  QImage img = QImage(rgb,
		      lenx, leny,
		      QImage::Format_ARGB32);      

  int lsize = 4*256*256;

  for(int z=minz; z<=maxz; z++)
    {
      memset(vol, 255, 4*leny*lenx);
      memset(rgb, 0, 4*leny*lenx);

      for (int q=0; q<nRGB; q++)
	{
	  uchar *vslice = m_rgbaFileManager[q].getSlice(z);
	  
	  for(int y=miny; y<=maxy; y++)
	    for(int x=minx; x<=maxx; x++)
	      {
		int ij = y*m_height + x;
		int idx = (y-miny)*lenx + (x-minx);
		vol[4*idx+q] = vslice[ij];
	      }
	}


      for(int y=miny; y<=maxy; y++)
	for(int x=minx; x<=maxx; x++)
	  {
	    int idx = (y-miny)*lenx + (x-minx);

	    Vec po = Vec(x, y, z);
	    po = VECPRODUCT(po, voxelScaling);

	    bool ok = StaticFunctions::getClip(po, clipPos, clipNormal);

	    for(int ci=0; ci<crops.count(); ci++)
	      ok &= crops[ci].checkCropped(po);

	    // apply clipping
	    if (ok)
	      {
		uchar r = vol[4*idx+0];
		uchar g = vol[4*idx+1];
		uchar b = vol[4*idx+2];
		uchar a = vol[4*idx+3];

		float opac = (lut[4*(256*g + r)+3]/255.0f);
		opac *= (lut[lsize + 4*(256*b + g)+3]/255.0f);
		opac *= (lut[2*lsize + 4*(256*r + b)+3]/255.0f);
		if (nRGB == 4)
		  {
		    uchar a = vol[4+idx + 3];
		    uchar rgb = qMax(r, qMax(g, b));
		    opac *= (lut[3*lsize + 4*(256*rgb + a)+3]/255.0f);
		  }

		if (opac > 0)
		  {
		    rgb[4*idx+0] = b * opac;
		    rgb[4*idx+1] = g * opac;
		    rgb[4*idx+2] = r * opac;
		    rgb[4*idx+3] = a * opac;
		  }
	      }
	  }

      QString flname = f.absolutePath() + QDir::separator() +
	               f.baseName();
      flname += QString("%1").arg((int)z, 5, 10, fillChar);
      flname += ".";
      flname += f.completeSuffix();

      img.save(flname);
      Global::progressBar()->setValue((int)(100*(float)(z-minz)/(float)lenz));
      qApp->processEvents();
    }

  delete [] vol;
  delete [] rgb;

  Global::progressBar()->setValue(100);
  Global::hideProgressBar();
}

void
VolumeRGB::saveOpacityVolume(unsigned char *lut,
			     QList<Vec> clipPos,
			     QList<Vec> clipNormal,
			     QList<CropObject> crops)
{
  QString opFile;

  opFile= QFileDialog::getSaveFileName(0,
				       "Save Opacity Volume",
				       Global::previousDirectory(),
				       "RAW Files (*.raw)");
  if (opFile.isEmpty())
    return;


  QFileInfo f(opFile);	
  QChar fillChar = '0';
  QImage timage;

  MainWindowUI::mainWindowUI()->menubar->parentWidget()->setWindowTitle("Saving image stack");
  Global::progressBar()->show();

  //---------------
  int nRGB = 3;
  if (Global::volumeType() == Global::RGBAVolume)
    nRGB = 4;
  //---------------


  int minx = m_dataMin.x;
  int maxx = m_dataMax.x;
  int miny = m_dataMin.y;
  int maxy = m_dataMax.y;
  int minz = m_dataMin.z;
  int maxz = m_dataMax.z;
  int lenx = m_subvolumeSize.x;
  int leny = m_subvolumeSize.y;
  int lenz = m_subvolumeSize.z;

  Vec voxelScaling = Global::voxelScaling();


  //*** max 1Gb per slab
  int opslabSize;
  opslabSize = (1024*1024*1024)/(leny*lenx);
  VolumeFileManager opFileManager;
  opFileManager.setBaseFilename(opFile);
  opFileManager.setDepth(lenz);
  opFileManager.setWidth(leny);
  opFileManager.setHeight(lenx);
  opFileManager.setHeaderSize(13);
  opFileManager.setSlabSize(opslabSize);
  opFileManager.createFile(true);

  uchar *opacity = new uchar [leny*lenx];

  uchar *vol;
  vol = new uchar[4*leny*lenx];


  int lsize = 4*256*256;

  for(int z=minz; z<=maxz; z++)
    {
      memset(vol, 255, 4*leny*lenx);

      for (int q=0; q<nRGB; q++)
	{
	  uchar *vslice = m_rgbaFileManager[q].getSlice(z);
	  
	  for(int y=miny; y<=maxy; y++)
	    for(int x=minx; x<=maxx; x++)
	      {
		int ij = y*m_height + x;
		int idx = (y-miny)*lenx + (x-minx);
		vol[4*idx+q] = vslice[ij];
	      }
	}


      for(int y=miny; y<=maxy; y++)
	for(int x=minx; x<=maxx; x++)
	  {
	    int idx = (y-miny)*lenx + (x-minx);

	    Vec po = Vec(x, y, z);
	    po = VECPRODUCT(po, voxelScaling);

	    bool ok = StaticFunctions::getClip(po, clipPos, clipNormal);

	    for(int ci=0; ci<crops.count(); ci++)
	      ok &= crops[ci].checkCropped(po);

	    // apply clipping
	    if (ok)
	      {
		uchar r = vol[4*idx+0];
		uchar g = vol[4*idx+1];
		uchar b = vol[4*idx+2];
		uchar a = vol[4*idx+3];

		float opac = (lut[4*(256*g + r)+3]/255.0f);
		opac *= (lut[lsize + 4*(256*b + g)+3]/255.0f);
		opac *= (lut[2*lsize + 4*(256*r + b)+3]/255.0f);
		if (nRGB == 4)
		  {
		    uchar a = vol[4+idx + 3];
		    uchar rgb = qMax(r, qMax(g, b));
		    opac *= (lut[3*lsize + 4*(256*rgb + a)+3]/255.0f);
		  }

		opacity[idx] = opac*255;
	      }
	  }

      opFileManager.setSlice(z-minz, opacity);
      Global::progressBar()->setValue((int)(100*(float)(z-minz)/(float)lenz));
      qApp->processEvents();
    }

  delete [] vol;
  delete [] opacity;


  MainWindowUI::mainWindowUI()->menubar->parentWidget()->\
    setWindowTitle(QString("Drishti"));
  Global::progressBar()->setValue(100);
  Global::hideProgressBar();

  QMessageBox::information(0, "Save Opacity Volume",
			   QString("Saved opacity volume to ")+opFile);
}
