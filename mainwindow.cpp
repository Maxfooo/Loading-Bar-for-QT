#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // init log
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(clearLog()));

    init_loading_bar_test();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::log(QString str)
{
    ui->textBrowser->append(str);
}

void MainWindow::clearLog()
{
    ui->textBrowser->clear();
}

/*************************************************/
// LOADING BAR TEST
/*************************************************/
void MainWindow::init_loading_bar_test()
{
    loading_bar = new LoadingBar(ui->lineEdit, this);
    connect(loading_bar, SIGNAL(repr(QString)), this, SLOT(log(QString)));
    connect(ui->pushButton_4, SIGNAL(clicked()), loading_bar, SLOT(disp_stats()));
    connect(ui->pushButton, SIGNAL(clicked()), loading_bar, SLOT(start()));
    connect(ui->pushButton_2, SIGNAL(clicked()), loading_bar, SLOT(stop()));

    // Set Bar Color
    ui->comboBox->addItem("Green");
    ui->comboBox->addItem("Red");
    ui->comboBox->addItem("Blue");
    ui->comboBox->addItem("Black");

    // Set Bar Speed
    ui->comboBox_2->addItem("Slow");
    ui->comboBox_2->addItem("Normal");
    ui->comboBox_2->addItem("Fast");
    ui->comboBox_2->addItem("Very Fast");
}


void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0: loading_bar->setBarColor(Qt::green); break;
        case 1: loading_bar->setBarColor(Qt::red); break;
        case 2: loading_bar->setBarColor(Qt::blue); break;
        default: loading_bar->setBarColor(Qt::black);
    }
}

void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    switch (index)
    {
        case 0: loading_bar->setInterval(LoadingBar::SLOW); break;
        case 1: loading_bar->setInterval(LoadingBar::NORMAL); break;
        case 2: loading_bar->setInterval(LoadingBar::FAST); break;
        default: loading_bar->setInterval(LoadingBar::VERY_FAST);
    }
}
