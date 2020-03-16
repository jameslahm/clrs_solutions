#include "mainwindow.h"
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QPushButton>
#include"label.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    QHBoxLayout* hLayOut=new QHBoxLayout();
    QVBoxLayout* vLayOut=new QVBoxLayout();
    MyLabel* label=new MyLabel();
    label->setStyleSheet("border:2px solid black");
    hLayOut->addWidget(label);
    QPushButton* clearButton=new QPushButton();
    clearButton->setText("清除所有点");
    QPushButton* solveButton=new QPushButton();
    solveButton->setText("寻找最近点对");
    QPushButton* randomButton=new QPushButton();
    randomButton->setText("随机生成点对");
    QLabel* resLabel=new QLabel();
    resLabel->setStyleSheet("border:2px solid black");
    vLayOut->addWidget(clearButton);
    vLayOut->addWidget(solveButton);
    vLayOut->addWidget(randomButton);
    vLayOut->addWidget(resLabel);
    hLayOut->addLayout(vLayOut);
    hLayOut->setStretch(0,4);
    hLayOut->setStretch(1,1);
    QWidget* central=new QWidget();
    central->setLayout(hLayOut);
    setCentralWidget(central);

    connect(clearButton,&QPushButton::clicked,label,&MyLabel::clearPoints);
    connect(solveButton,&QPushButton::clicked,label,&MyLabel::solvePoints);
    connect(label,&MyLabel::solveFinished,resLabel,&MyLabel::setText);
    connect(randomButton,&QPushButton::clicked,label,&MyLabel::randomGeneratePoints);
}

MainWindow::~MainWindow()
{
}

QSize MainWindow::sizeHint()const{
    return QSize(1200,800);
}
