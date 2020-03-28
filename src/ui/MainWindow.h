#pragma once
#include <QMainWindow>
#include <QScopedPointer>
#include <memory>
#include "../io/Synchronizer.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    
  private:
    QScopedPointer<Ui::MainWindow> m_ui;
    std::shared_ptr<raydelto::Synchronizer> m_synchronizer;
    void ShowMessage(QString title, QString body);
};
