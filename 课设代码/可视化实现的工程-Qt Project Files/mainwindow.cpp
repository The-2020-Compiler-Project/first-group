#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "compile.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //状态栏
    QStatusBar * stBar = statusBar();
    setStatusBar(stBar);
    QLabel * label = new QLabel("Compile Task : GUI Made By CR",this);
    stBar->addWidget(label);
    ui->pushButton_2->setEnabled(false);
    ui->actionOpen_and_Run->setEnabled(false);
    // 信号与槽的连接
    connect(ui->pushButton,&QPushButton::clicked,[=](){
        //path
        path = QFileDialog::getOpenFileName(this,"Open File","D:/QT project/Compile/compile");
        //read
        QFile fp(path);
        fp.open(QIODevice::ReadWrite);
        QByteArray arr = fp.readAll();
        ui->textEdit->setText(arr);
        fp.close();
        QString path2 = "D:/QT project/Compile/compile/error.txt";
        QFile fp2(path2);
        fp2.open((QIODevice::WriteOnly));
        fp2.write(arr);
        fp2.close();
        ui->pushButton_2->setEnabled(true);
        ui->actionOpen_and_Run->setEnabled(true);
    });
    connect(ui->actionOpen,&QAction::triggered,[=](){
        //path
        path = QFileDialog::getOpenFileName(this,"Open File","D:/QT project/Compile/compile");
        //read
        QFile fp(path);
        fp.open(QIODevice::ReadWrite);
        QByteArray arr = fp.readAll();
        ui->textEdit->setText(arr);
        fp.close();
        QString path2 = "D:/QT project/Compile/compile/error.txt";
        QFile fp2(path2);
        fp2.open((QIODevice::WriteOnly));
        fp2.write(arr);
        fp2.close();
        ui->pushButton_2->setEnabled(true);
        ui->actionOpen_and_Run->setEnabled(true);
    });
    connect(ui->actionSave,&QAction::triggered,[=](){
        QString arr = ui->textEdit->toPlainText();
        QString path2 = "D:/QT project/Compile/compile/save.txt";
        QFile fp2(path2);
        fp2.open((QIODevice::WriteOnly));
        fp2.write(arr.toUtf8());
        fp2.close();
        QString path3 = "D:/QT project/Compile/compile/error.txt";
        QFile fp3(path3);
        fp3.open((QIODevice::WriteOnly));
        fp3.write(arr.toUtf8());
        fp3.close();
        ui->pushButton_2->setEnabled(true);
        ui->actionOpen_and_Run->setEnabled(true);
    });
    connect(ui->actionClose,&QAction::triggered,this,&MainWindow::close);
    connect(ui->actionAbout_this_Compiler,&QAction::triggered,&aboutwight,&About::show);
    connect(ui->actionRun,&QAction::triggered,ui->pushButton_2,&QPushButton::clicked);
    connect(ui->pushButton_2,&QPushButton::clicked,[=](){
        int flag = compilemain();
        if(flag == 100)
        {
            QMessageBox::warning( this,"warning", "Error，Please Check Your Code.\nYou may find some information in ./log.txt");
            this->close();
        }
        else
        {
            QString path2 = "D:/QT project/Compile/compile/final.asm";
            QFile fp(path2);
            fp.open(QIODevice::ReadWrite);
            QByteArray arr = fp.readAll();
            ui->textEdit_2->setText(arr);
            fp.close();
            ui->pushButton_2->setEnabled(false);
            ui->actionOpen_and_Run->setEnabled(false);
        }
    });
    connect(ui->actionOpen_and_Run,&QAction::triggered,[=](){
        //path
        path = QFileDialog::getOpenFileName(this,"Open File","D:/QT project/Compile/compile");
        //read
        QFile fp(path);
        fp.open(QIODevice::ReadWrite);
        QByteArray arr = fp.readAll();
        ui->textEdit->setText(arr);
        fp.close();
        QString path2 = "D:/QT project/Compile/compile/error.txt";
        QFile fp2(path2);
        fp2.open((QIODevice::WriteOnly));
        fp2.write(arr);
        fp2.close();
        int flag = compilemain();
        if(flag == 100)
        {
            QMessageBox::warning( this,"warning", "Error，Please Check Your Code.\nYou may find some information in ./log.txt");
            this->close();
        }
        else
        {
            QString path3 = "D:/QT project/Compile/compile/final.asm";
            QFile fp3(path3);
            fp3.open(QIODevice::ReadWrite);
            QByteArray arr2 = fp3.readAll();
            ui->textEdit_2->setText(arr2);
            fp3.close();
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

