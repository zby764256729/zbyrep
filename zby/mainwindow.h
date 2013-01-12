#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
  void replyFinished(QNetworkReply *);
  void on_chaxun_clicked();

private:
    Ui::MainWindow *ui;
    QNetworkAccessManager *manager;
    QString S1;
    QString S2;
};

#endif // MAINWINDOW_H
