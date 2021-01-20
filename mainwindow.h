#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QSettings>
#include <QByteArray>
#include <QDesktopWidget>
#include <QApplication>
#include <QCloseEvent>
#include <QWidget>
#include <QtSql/QSqlDatabase>
#include <QList>
#include <QTableView>
#include <QSqlQuery>
#include <QSortFilterProxyModel>
#include <QRegExp>
#include <QDate>

#include <QDir>

#include <QLine>

#include <QtPrintSupport>
#include <QPrintPreviewDialog>
#include <QPagedPaintDevice>
#include <QPrinterInfo>
#include <QPainter>
#include <QPrinter>
#include <QHeaderView>
#include <QMarginsF>

#include <QTextDocument>

#include "finddialog.h"
#include "mysqltablemodel.h"
#include "myform.h"

#include <QDebug>

const QString PREFIX = "otpi_";
//const QString PATH_TO_DB = "D:/CPP/MyProects/DB_OTPI_SDI_4/TestDB.db";
const QString PATH_TO_DB = "/DB_OTPI.db"; //файл базы данных создастся сам!!!
const QString DRIVER_DB = "QSQLITE";
const QString MY_STYLE_CSS_FILE = ":/res/mystyle.css";

namespace Ui {
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  explicit MainWindow(QWidget *parent, const QString &fileName);
  ~MainWindow();

public:
  bool save();
  bool saveAs();

protected:
  void closeEvent(QCloseEvent *event);

private slots:
  void on_actionQuit_triggered();
  void on_actionSave_triggered();
  void on_actionOpen_triggered();
  void on_actionPasteRow_triggered();
  void on_actionDelRow_triggered();
  void on_actionNew_triggered();
  void on_actionSaveAs_triggered();
  void on_actionFind_triggered();
  void acceptorCloseFindDialogSlot();
  void acceptFindTextFromFindDialog(const QString &findText);
  bool on_actionConvertToCSV_triggered();
  void on_tableViewUi_pressed(const QModelIndex &index);
  void on_tableViewUi_doubleClicked(const QModelIndex &index);
  void on_actionPrinter_triggered();
  void printPreview(QPrinter *);
  void on_actionResetFind_triggered();

private:
  Ui::MainWindow *ui;
  bool connectToDb();
  void createViewTableAndSqlModel(const QString &tableName);
  void init();
  bool saveFile(const QString &fileNAme);
  void setCurrentFile(const QString &fileName);
  bool maybeSave();
  MainWindow * findMainWindow(const QString &fileName);
  void loadFile(const QString &fileName);
  void writeSettings();
  void readSettings();
  void setTableName(const QString &tableName);
  bool createNewTable(const QString &tableName);
  bool mySearchTableInDataBase(const QString &tableName);
  bool copyInSaveTableIsNoNameTable(const QString &tableName);
  bool copyInSaveTableIsTableToNewNameTable(const QString &newTableName);
  bool dropTableNoName()const;
  bool dropTable(const QString &tableName)const;
  void setTableAndFileNames(const QString &fileName, const QString tbName);
  void connections();
  void createSortProxyModel(/*const QString &findText*/const QRegExp &patternSearch);
  QRegExp mySetPattern(const QString &searchText);
  bool loadingStyleFileCss();

private:
  QString curFile; //путь к текущему файлу
  bool isUntitled; //флаг наличия имени и пути
  MySqlTableModel * mySqlTableModel;
  QSqlDatabase db;
  QString tableName;
  FindDialog * findDialog;
  bool findDialogIsShow;
  QSortFilterProxyModel * sortModel;
  MyForm *myEditForm;
};

#endif // MAINWINDOW_H
