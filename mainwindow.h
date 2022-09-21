#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots: // Slots are functions that are called when a signal is emitted
    void startProcessingThread();
    void startProcessing();
    void inFileToolClicked();
    void outFolderToolClicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
