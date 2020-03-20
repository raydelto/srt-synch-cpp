#pragma once
#include <QMainWindow>
#include <QScopedPointer>

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
};
