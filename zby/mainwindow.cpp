#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextCodec.h>
#include <QtScript/QScriptEngine>
#include <QtScript/QScriptValue>
#include <QtScript/QScriptValueIterator>
#include <qmessagebox.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec *codec = QTextCodec::codecForName("GB2312");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
}
void MainWindow::replyFinished(QNetworkReply *reply)
{
        QString all = reply->readAll();
        QScriptValue value;
        QScriptEngine engine;
        value = engine.evaluate("value = " + QString(all));
        QScriptValueIterator it(value);
        while (it.hasNext()) {
           it.next();
           if("msg"==it.name()&& "book_not_found"== it.value().toString())
           {
               QMessageBox::information(0, "error!",QString(QObject::tr("Input ID errors\nPlease re-enter")));
               ui->ID->clear();
               return;
           }
           if("title"==it.name())ui->title->setText(it.value().toString());
           if("author"==it.name())ui->author->setText(it.value().toString());
           if("isbn10"==it.name())ui->isbn10->setText(it.value().toString());
           if("pages"==it.name())ui->pages->setText(it.value().toString());
           if("price"==it.name())ui->price->setText(it.value().toString());
           if("publisher"==it.name())ui->publisher->setText(it.value().toString());
           if("pubdate"==it.name())ui->pubdate->setText(it.value().toString());
           if("summary"==it.name())ui->ss->setText(it.value().toString());
        }
        reply->deleteLater();   //最后要释放reply对象
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_chaxun_clicked()
{
    S1="https://api.douban.com/v2/book/";
    S2=ui->ID->text();
    //设置QTextCodec可以显示中文
    QTextCodec *codec = QTextCodec::codecForName("utf-8");
    QTextCodec::setCodecForLocale(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForTr(codec);
    QNetworkRequest request;
    request.setUrl(QUrl(S1+S2));
    manager = new QNetworkAccessManager(this);  //新建QNetworkAccessManager对象
    connect(manager,SIGNAL(finished(QNetworkReply*)),  //关联信号和槽
                this,SLOT(replyFinished(QNetworkReply*)));
    manager->get(QNetworkRequest(request)); //发送请求
}
