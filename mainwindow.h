#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "loadingbar.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void log(QString str);
    void clearLog();

private slots:

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    LoadingBar* loading_bar;

    // TEST INITS
    void init_loading_bar_test();
};

#endif // MAINWINDOW_H
