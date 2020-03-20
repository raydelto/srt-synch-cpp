#include <QPushButton>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
: QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);
    auto pushed = []()
    {
        printf("que gorpe!\n");
    };
    connect(m_ui->btnSaludar, &QPushButton::clicked, this, pushed);
}

MainWindow::~MainWindow()
{
    printf("Destroying window\n");
}
