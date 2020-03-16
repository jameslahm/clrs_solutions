#include"label.h"
#include"fnp.h"
#include<string>
#include<QPainter>
#include<QMouseEvent>
#include<QPen>
#include<QColor>
#include<QInputDialog>
void MyLabel::mousePressEvent(QMouseEvent* event){
    Point* p=new Point(event->x(),event->y());
    vec.push_back(p);
    update();
}

void MyLabel::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPen pen;
    pen.setColor(QColor(0,0,0));
    pen.setWidth(4);
    painter.setPen(pen);
    foreach(Point* p,vec){
        painter.drawPoint(QPointF(p->x,p->y));
    }
    if(isSolved){
        painter.drawLine(QPointF(result.second.first->x,result.second.first->y),QPointF(result.second.second->x,result.second.second->y));
    }
}

void MyLabel::clearPoints(){
    for(int i=0;i<vec.size();i++){
        delete vec[i];
    }
    vec.clear();
    isSolved=false;
    update();
}

void MyLabel::solvePoints(){
    RES res=findNeaestPoints(vec);
    std::string s="最近距离: "+std::to_string(res.first)+"\n"+"点对: ("+std::to_string(res.second.first->x)+","+std::to_string(res.second.first->y)+")";
    s=s+" ("+std::to_string(res.second.second->x)+","+std::to_string(res.second.second->y)+")";
    emit solveFinished(QString::fromStdString(s));
    result=res;
    isSolved=true;
    update();
}

void MyLabel::randomGeneratePoints(){
    bool ok;
    int n=QInputDialog::getInt(dynamic_cast<QWidget*>(this->parent()),"Input","请输入要随机生成点的数目",QLineEdit::Normal,100,10000000,100,&ok);
    if(ok){
        vec=randomPoints(n);
    }
    isSolved=false;
    update();
}
