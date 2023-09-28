#ifndef SLICES_H
#define SLICES_H

#include <QtGui>
#include <QHBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>

#include "imagewidget.h"

class Slices : public QWidget
{
  Q_OBJECT
  
 public :
  Slices(QWidget *);

  void setByteSize(int);
  void setGridSize(int, int, int);
  void setSliceType(int);
  int currSlice() { return m_slider->value(); }
  
  void setVolPtr(uchar *);
  void setMaskPtr(uchar *);

  void resetSliceType();
  void setBox(int, int, int, int, int, int);
  void getBox(int&, int&, int&, int&, int&, int&);
  void processPrevSliceTags();
  void loadLookupTable(QImage);

  void saveImage();
  void saveImageSequence();

  void setRawValue(QList<int>);

  void reloadSlice();

  void setModeType(int);

  void setLarge(bool);
  bool enlarged() { return m_maximized; }

  void setShowPosition(bool);

  void setMinGrad(float g) { m_imageWidget->setMinGrad(g); }
  void setMaxGrad(float g) { m_imageWidget->setMaxGrad(g); }
  void setGradType(int g) { m_imageWidget->setGradType(g); }

 signals :
  void changeLayout();
  void sliceChanged(int);
  void xPos(int);
  void yPos(int);
  void saveWork();

  void getRawValue(int, int, int);
  void viewerUpdate();
  void tagDSlice(int, uchar*);
  void tagWSlice(int, uchar*);
  void tagHSlice(int, uchar*);

  void applyMaskOperation(int, int, int);
  void updateViewerBox(int, int, int, int, int, int);

  void saveMask();

  void shrinkwrap(Vec, Vec,
		  int, bool, int,
		  bool,
		  int, int, int,
		  int);
  void connectedRegion(int, int, int,
		       Vec, Vec,
		       int, int);
    
 public slots :
   void updateTagColors();
   void setHLine(int);
   void setVLine(int);
   void setSlice(int);

   void disconnectSlider();
   void reconnectSlider();

   void setSliceNumber(int);
   
   void sliceNumChanged();
   
   //void bbupdated(Vec, Vec);
   void fitImage() { m_imageWidget->zoom9Clicked(); }

   void setAutoGenSuperPixels(bool);
   void setHideSuperPixels(bool);
   void setSuperPixelSize(int);

   void updateSliderLimits();
   void resetSliderLimits();

   void zoomToSelection() { m_imageWidget->zoom9Clicked(); }
  
  
 private:
    ImageWidget *m_imageWidget;
    
    QPushButton *m_zoom0;
    QPushButton *m_zoom9;
    QPushButton *m_zoomUp;
    QPushButton *m_zoomDown;
    QPushButton *m_changeLayout;

    QLineEdit *m_sliceNum;

    QSlider *m_slider;

    bool m_maximized;

    int m_Depth, m_Width, m_Height;
    int m_s0, m_s1;
  
    void createMenu(QHBoxLayout*, QVBoxLayout*);
};



#endif
