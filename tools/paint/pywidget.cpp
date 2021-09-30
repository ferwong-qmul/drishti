#include "pywidget.h"
#include "global.h"
#include "staticfunctions.h"

#include <QVBoxLayout>
#include <QMessageBox>
#include <QFileDialog>

#pragma push_macro("slots")
#undef slots
#include "Python.h"
#pragma pop_macro("slots")

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include "numpy/arrayobject.h"

void
PyWidget::setFilename(QString volfile)
{
  QStringList pvlnames = StaticFunctions::getPvlNamesFromHeader(volfile);
  if (pvlnames.count() > 0)
    m_fileName = pvlnames[0];
  else
    m_fileName = volfile;
    

  m_maskName = m_fileName;
  m_maskName.chop(6);
  m_maskName += QString("mask.sc");

  m_fileName += ".001";
  m_plainTextEdit->appendPlainText(m_fileName);
  m_plainTextEdit->appendPlainText(m_maskName+"\n");
}

void
PyWidget::setSize(int d, int w, int h)
{
  m_d = d;
  m_w = w;
  m_h = h;
}

void
PyWidget::setVolPtr(uchar* v)
{
  m_volPtr = v;
}

void
PyWidget::setMaskPtr(uchar* m)
{
  m_maskPtr = m;
}
  

PyWidget::PyWidget(QWidget *parent)
: QWidget(parent)
{
  m_d = m_w = m_h = 0;
  m_volPtr = m_maskPtr = 0;
  
  m_plainTextEdit = new QPlainTextEdit(this);
  m_plainTextEdit->setReadOnly(true);

  m_lineEdit = new QLineEdit(this);
  m_lineEdit->setClearButtonEnabled(true);

  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget(m_plainTextEdit);
  layout->addWidget(m_lineEdit);
  setLayout(layout);
  show();

  QFont font;
  font.setPointSize(10);
  m_plainTextEdit->setFont(font);
  m_lineEdit->setFont(font);

  m_process = new QProcess();

  connect(m_process, SIGNAL(readyReadStandardOutput()),
	  this, SLOT(readOutput()));
  connect(m_process, SIGNAL(readyReadStandardError()),
	  this, SLOT(readError()));

  connect(m_lineEdit, SIGNAL(returnPressed()),
	  this, SLOT(processLine()));

  connect(m_process, static_cast<void(QProcess::*)(int, QProcess::ExitStatus)>(&QProcess::finished),
	  this, &PyWidget::close);

  m_process->start("cmd.exe");

  initPy();
}

PyWidget::~PyWidget()
{  
  emit pyWidgetClosed();
  Py_Finalize();

  m_process->close();
}

int
PyWidget::initPy()
{
  Py_Initialize();

  import_array(); // used by numpy
}


int
PyWidget::runPythonCode(QString moduleName, QString funcName)
{
  const int ND = 3;
  npy_intp dims[3] {m_d, m_w, m_h};
      
  // Convert it to a NumPy array.
  PyObject *volArray = PyArray_SimpleNewFromData(ND,
						 dims,
						 NPY_INT8,
						 reinterpret_cast<void*>(m_volPtr));

  PyObject *maskArray = PyArray_SimpleNewFromData(ND,
						  dims,
						  NPY_INT8,
						  reinterpret_cast<void*>(m_maskPtr));
  if (!volArray || !maskArray)
    {
      QMessageBox::information(0,"", "Some problem with PyArray point creation");
      return -1;
    }
  

  //PyArrayObject *vol_arr = reinterpret_cast<PyArrayObject*>(volArray);
  //PyArrayObject *mask_arr = reinterpret_cast<PyArrayObject*>(maskArray);

  // import moduleName.funcName
  const char *module_name = moduleName.toLatin1().data();
  PyObject *pName = PyUnicode_FromString(module_name);
  if (!pName)
    {
      QMessageBox::information(0, "", moduleName+" not found");
      Py_DECREF(volArray);
      Py_DECREF(maskArray);
      return -1;
    }

  PyObject *pModule = PyImport_Import(pName);
  Py_DECREF(pName);
  if (!pModule)
    {
      QMessageBox::information(0, "", "failed to import "+moduleName);
      Py_DECREF(volArray);
      Py_DECREF(maskArray);
      return -1;
    }

  const char *func_name = funcName.toLatin1().data();
  PyObject *pFunc = PyObject_GetAttrString(pModule, func_name);
  if (!pFunc)
    {
      QMessageBox::information(0, "", funcName+" not found");
      Py_DECREF(pModule);
      return -1;
    }

  if (!PyCallable_Check(pFunc))
    {
      QMessageBox::information(0, "", moduleName + "." + funcName + " is not callable.");
      Py_DECREF(pFunc);
      return -1;
  }

  PyObject *pReturn = PyObject_CallFunctionObjArgs(pFunc, volArray, maskArray, NULL);
  if (!pReturn)
    {
      QMessageBox::information(0, "", "Call to " + funcName +" failed");
      Py_DECREF(pFunc);
      return -1;
    }

  QMessageBox::information(0, "", "done");

  return 0;
}

void
PyWidget::readOutput()
{
  m_plainTextEdit->appendPlainText(m_process->readAllStandardOutput());
}
void
PyWidget::readError()
{
  m_plainTextEdit->appendPlainText(m_process->readAllStandardError());
}
void
PyWidget::processLine()
{
  QString command = m_lineEdit->text();

  QStringList sl = command.split(" ", QString::SkipEmptyParts);
  if (sl.count() == 0)
    return;
  
  if (sl[0] == QString("exit"))
    {
      m_process->kill();
      return;
    }
  
  if (sl.count() == 2 && sl[0] == QString("run"))
    {
      runPythonCode(sl[1], sl[2]);
      return;
    }
  else if (sl.count() >= 2 && StaticFunctions::checkExtension(sl[0], ".py"))
    {
      QString scriptdir = qApp->applicationDirPath() +
	                  QDir::separator() + "assets" +
	                  QDir::separator() + "scripts";
      QString script = scriptdir + QDir::separator() + sl[0];

      QString volflnm = m_fileName;
      QStringList result = sl.filter("volume=");
      if (result.count() >= 1)
	volflnm = QFileInfo(m_fileName).absolutePath() + QDir::separator() + result[0].split("=")[1];

      QString tagflnm;
      result = sl.filter("output=");
      if (result.count() >= 1)
	tagflnm = QFileInfo(m_fileName).absolutePath() + QDir::separator() + result[0].split("=")[1];
      
      
      QString cmd = "python "+script+" volume="+volflnm+" mask="+m_maskName+" output="+tagflnm;
      if (sl.count() > 1)
	{
	  for (int s=1; s<sl.count(); s++)
	    {
	      if (!sl[s].contains("volume=", Qt::CaseInsensitive) &&
		  !sl[s].contains("output=", Qt::CaseInsensitive))
		cmd += " "+sl[s];
	    }
	}
      m_process->write(cmd.toLatin1() + "\n");

      //m_lineEdit->clear();
      return;
    }  
  

  m_process->write(command.toLatin1() + "\n");
  //m_lineEdit->clear();
}
