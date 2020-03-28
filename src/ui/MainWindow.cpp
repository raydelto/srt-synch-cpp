#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include "MainWindow.h"
#include "ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_synchronizer(std::make_shared<raydelto::Synchronizer>())
{
    this->setFixedSize(658, 253);
    m_ui->setupUi(this);

    auto saveToFile = [&]() {
        QString fileName = QFileDialog::getSaveFileName(this,
                                                        "Synchronized SRT file path", "",
                                                        "SRT files (*.srt);;All Files (*)");

        if (fileName.isEmpty())
            return;
        else
        {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly))
            {
                ShowMessage("Unable to open file", file.errorString());
                return;
            }
            m_ui->txtDestinationFileLocation->setPlainText(fileName);
        }
    };

    auto loadFile = [&]() {
        QString fileName = QFileDialog::getOpenFileName(this,
                                                        "Original SRT file path", "",
                                                        "SRT files (*.srt);;All Files (*)");

        if (fileName.isEmpty())
            return;
        else
        {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly))
            {
                ShowMessage("Unable to open file", file.errorString());
                return;
            }
            m_ui->txtOriginalFileLocation->setPlainText(fileName);
        }
    };

    auto processFile = [&]() {
        if( m_ui->txtOriginalFileLocation->toPlainText().isEmpty() || m_ui->txtDestinationFileLocation->toPlainText().isEmpty())
        {
            ShowMessage("Select valid SRT Paths", "Please select valid SRT Paths");            
            return; 
        }
        raydelto::Time variation(m_ui->spnHours->value(), m_ui->spnMinutes->value(), m_ui->spnSeconds->value(), m_ui->spnMilliseconds->value());
        m_synchronizer->Process(m_ui->txtOriginalFileLocation->toPlainText().toStdString(), m_ui->txtDestinationFileLocation->toPlainText().toStdString(), variation);
        ShowMessage("SRT Synchronized Successfully", "Your synchronized subtitles have been written to " + m_ui->txtDestinationFileLocation->toPlainText());

    };

    connect(m_ui->btnProcess, &QPushButton::clicked, this, processFile);
    connect(m_ui->btnBrowseSourceFile, &QPushButton::clicked, this, loadFile);
    connect(m_ui->btnBrowseDestinationFile, &QPushButton::clicked, this, saveToFile);
}


void MainWindow::ShowMessage(QString title, QString body)
{
    QMessageBox msgBox( "", body,  QMessageBox::Information, 0, 0, 0, nullptr, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
    msgBox.QDialog::setWindowTitle(title);
    msgBox.exec();
}

MainWindow::~MainWindow()
{
}
