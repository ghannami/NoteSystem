#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Global.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Global::i();
}

MainWindow::~MainWindow()
{
    delete ui;
}
