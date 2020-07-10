#pragma once
#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QPushButton>
#include <QMenuBar>
#include <QToolBar>
#include <QPushButton>
#include <QStatusBar>
#include <QLabel>
#include <QDockWidget>
#include <QTextEdit>
#include <QFileDialog>
#include <QFile>
#include <QTextCodec>
#include <QMessageBox>

namespace Ui {
class About;
}

class About : public QWidget
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = nullptr);
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
