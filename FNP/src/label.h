#ifndef LABEL_H
#define LABEL_H
#include<QLabel>
#include<QWidget>
#include<vector>
#include<string>
#include"fnp.h"

class MyLabel:public QLabel{
    Q_OBJECT
signals:
    void solveFinished(QString);
public:
    std::vector<Point*> vec;

    void paintEvent(QPaintEvent* event);
    void mousePressEvent(QMouseEvent* event);

    void clearPoints();
    void solvePoints();

    void randomGeneratePoints();

    bool isSolved=false;
    RES result;
};


#endif // LABEL_H
