
#ifndef SCRIPTEDITORVIEW_HH
#define SCRIPTEDITORVIEW_HH

#include <QMainWindow>
#include "TextEdit.hh"
#include "ScriptEditorController.hh"
//#include "ScriptEditorDelegate.hh"
#include "SoloFunctionsController.hh"

#include <QWidget>
#include <QAction>
#include <QLabel>
#include <QTextEdit>
#include <QToolBar>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QTreeView>
#include <QString>
// #include <QJSEngine>

class ScriptEditorView : public QMainWindow
{
    Q_OBJECT

public:

  //  ScriptEditorView(std::string fileName, QWidget *parent = 0);
  ScriptEditorView(QWidget *parent = 0);
  virtual ~ScriptEditorView();

  //  void setController(ScriptEditorController *controller);

  void init();

  void newDataReady();


  float myPow();

  vector<string> *getVariablesFromScriptEditor();
  vector<float> *getDataForVariableFromScriptEditor(int column, string fieldName);

  //void setSelectionToValue(QString value);
  void closeEvent();

public slots:
    void updateStatus(QTableWidgetItem *item);
    void updateTextEdit(QTableWidgetItem *item);
    void returnPressed();
    void acceptFormulaInput();
    void cancelFormulaInput();
    void displayHelp();
    void scriptComplete();
  //void clear();

  void notImplementedMessage();

  //void setupSoloFunctions(SoloFunctions *soloFunctions);

  void fieldNamesProvided(vector<string> fieldNames);
  //void fieldDataSent(vector<float> *data, int useless, int c);

  void applyChanges();

  //  void printQJSEngineContext();

signals:

  void needFieldNames();
  //void needDataForField(string fieldName, int r, int c);
  void applyVolumeEdits();
  void runOneTimeOnlyScript(QString oneTimeOnlyScript);
  void runForEachRayScript(QString forEachRayScript, bool useBoundary);
  void scriptEditorClosed();

protected:
    void setupContextMenu();
    void setupContents();
    void setupMenuBar();
    void createActions();
  //    void addVariableToScriptEditor(QString name, QJSValue value);

  /*
    bool runInputDialog(const QString &title,
                        const QString &c1Text,
                        const QString &c2Text,
                        const QString &opText,
                        const QString &outText,
                        QString *cell1, QString *cell2, QString *outCell);
  */
  void criticalMessage(std::string message);

  void openScriptFile();
  void importScriptFile();
  void saveScriptFile();

private:

  //ScriptEditorController *_controller;
    vector<std::string> _fieldNames;

    QToolBar *toolBar;

    QLabel *cellLabel;
    TextEdit *formulaInput;
    TextEdit *formulaInputForEachRay;
    QCheckBox *useBoundaryWidget;
    QTreeView *helpView;
    QHBoxLayout *scriptEditLayout;
    //QTextEdit *formulaInput;
  // ScriptEditorDelegate *formulaInput;
};

#endif // SCRIPTEDITORVIEW_H
