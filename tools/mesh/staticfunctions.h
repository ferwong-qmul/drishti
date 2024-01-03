#ifndef STATICFUNCTIONS_H
#define STATICFUNCTIONS_H

#include <GL/glew.h>
#include <QGLViewer/qglviewer.h>
using namespace qglviewer;

#include <QMessageBox>
#include <QVector3D>


#define DEG2RAD(angle) angle*3.1415926535897931/180.0
#define RAD2DEG(angle) angle*180.0/3.1415926535897931
#define VECPRODUCT(a, b) Vec(a.x*b.x, a.y*b.y, a.z*b.z)
#define VECDIVIDE(a, b) Vec(a.x/b.x, a.y/b.y, a.z/b.z)

class StaticFunctions
{
 public :
  static Vec getVec(QString);

  static int getPowerOf2(int);

  static Vec interpolate(Vec, Vec, float);

  static Vec clampVec(Vec, Vec, Vec);
  static Vec maxVec(Vec, Vec);
  static Vec minVec(Vec, Vec);

  static int getSubsamplingLevel(int, int, int, Vec, Vec);

  static void getRotationBetweenVectors(Vec, Vec, Vec&, float&);

  static QGradientStops resampleGradientStops(QGradientStops, int mapSize = 100);
  static void initQColorDialog();

  static void drawEnclosingCube(Vec*, Vec);
  static void drawEnclosingCube(Vec, Vec, bool allFaces = false);
  static void drawEnclosingCubeWithTransformation(Vec, Vec,
						  double*,
						  Vec);

  static void drawAxis(Vec, Vec, Vec, Vec, bool bothSides = false, int lw = 1);


  static int getScaledown(int, int);

  static void pushOrthoView(float, float, float, float);
  static void popOrthoView();
  static void drawQuad(float, float, float, float, float);

  static bool checkExtension(QString, const char*);
  static bool checkURLs(QList<QUrl>, const char*);

  static bool checkExtension(QString, QStringList);
  static bool checkURLs(QList<QUrl>, QStringList);

  static float calculateAngle(Vec, Vec, Vec);

  static bool getClip(Vec, QList<Vec>, QList<Vec>);

  static QSize getImageSize(int, int);

  static float remapKeyframe(int, float);
  static float easeIn(float);
  static float easeOut(float);
  static float smoothstep(float);
  static float smoothstep(float, float, float);


  static QVector<Vec> generateUnitSphere(int);

  static bool inTriangle(Vec, Vec, Vec, Vec);

  static QString replaceDirectory(QString, QString);

  static void convertFromGLImage(QImage&, int, int);

  static void savePvlHeader(QString,
			    bool, QString,
			    int, int, int,
			    int, int, int,
			    float, float, float,
			    QList<float>, QList<int>,
			    QString,
			    int);

  static void renderText(int, int,
			 QString, QFont,
			 QColor, QColor,
			 bool useTextPath = false);
  static QImage renderText(QString, QFont,
			   QColor, QColor,
			   bool border = true);
  static QImage renderText(QStringList, QFont,
			   QColor, QColor,
			   bool border = true);
  static void renderRotatedText(int, int,
				QString, QFont,
				QColor, QColor,
				float, bool,
				bool useTextPath = false);

  static float projectOnBall(float, float);
  static Quaternion deformedBallQuaternion(int, int,
					   qreal, qreal,
					   qreal, qreal,
					   const Camera* const);

  static void copyGradientFile(QString);

  static void loadTexture(QImage, GLuint);

  static bool intersectRayPlane(QVector3D, QVector3D,
				QVector3D, QVector3D,
				QVector3D, QVector3D,
				float&, float&);

  static void savePLY(QVector<float>,
		      QVector<float>,
		      QVector<float>,
		      QVector<uint>,
		      double*,
		      QString);

  static void splitBinarySTL(QString);





  static void generateHistograms(float*, float*, int*, int*);
  static bool xmlHeaderFile(QString);
  static void getDimensionsFromHeader(QString, int&, int&, int&);
  static Vec getVoxelSizeFromHeader(QString);
  static QString getVoxelUnitFromHeader(QString);
  static int getSlabsizeFromHeader(QString);
  static int getPvlVoxelTypeFromHeader(QString);
  static int getPvlHeadersizeFromHeader(QString);
  static int getRawHeadersizeFromHeader(QString);
  static QStringList getPvlNamesFromHeader(QString);
  static QStringList getRawNamesFromHeader(QString);


};

#endif
