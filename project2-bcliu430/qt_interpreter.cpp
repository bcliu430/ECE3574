#include "qt_interpreter.hpp"

#include <QDebug>
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>

//#define pie (atan2(0, -1));

void QtInterpreter::parseAndEvaluate(QString entry){
    std::stringstream ss;
    qDebug() << entry;

    string str = entry.toStdString();
    ss << str;
    Tokenize t(ss);
    if(t.AST()){
        root = t.getResult();

    }
    else {
        qDebug() << "cannot parse";
        QString err = QString::fromStdString("Error: fail to parse");
        emit error(err);
        return;
//        qDebug() << error;
    }

   if (root.Leaf().size() ==0){
     if(root.getExpression().type == StringT){
         string str = root.getExpression().StringV;
         qDebug() <<QString::fromStdString(str);
         if (str == "pi"){
            Expression ans = env.PI();
         }
         else if (env.bool_map.find(str) != env.bool_map.end()) {
             bool B = env.bool_map[str];
             Expression ans(B);
         }
         else if (env.double_map.find(str) != env.double_map.end()){
             double d = env.double_map[str];
             Expression ans(d);
         }
         else{
           QString err = QString::fromStdString("Error: cannot evaluate");
           emit error(err);
           return;
         }
     }
   }

  try {
      Expression ans = t.postordertraversal(root);
      display(ans);

  }
  catch (const InterpreterSemanticError &err) {
      qDebug() << "Error: ";
    }



}

void QtInterpreter::display(Expression e){
    if(e.getExpression().type == BoolT){
        if (e.getExpression().BoolV){
            out = QString::fromStdString("True");
        } else{
            out = QString::fromStdString("False");
        }
    }   else if (e.getExpression().type == DoubleT){
          double dou =  e.getExpression().DoubleV;
          out = QString::number(dou);
    }   else if (e.getExpression().type == StringT){
        string str =  e.getExpression().StringV;
        if (str == "draw"){
            out = QString::fromStdString("(None)");
            emit info(out);
              for ( unsigned s =0; s< e.Leaf().size(); s++){
                    if(e.getleaf(s).getExpression().type == PointT){
                      double x = std::get<0>(e.getleaf(s).getExpression().PointV), y = std::get<1>(e.getleaf(s).getExpression().PointV);
                      QGraphicsEllipseItem *point = new QGraphicsEllipseItem(x-2,y-2,4,4);
                      point -> setBrush(QBrush(Qt::black));
                      item = point;
                  } else if(e.getleaf(s).getExpression().type == LineT){
                        double x_start = std::get<0>(e.getleaf(s).getExpression().line_start),y_start = std::get<1>(e.getleaf(s).getExpression().line_start), x_end = std::get<0>(e.getleaf(s).getExpression().line_end),y_end = std::get<1>(e.getleaf(s).getExpression().line_end);
                        QGraphicsLineItem *line = new QGraphicsLineItem(x_start, y_start, x_end, y_end);
                        QPen pen(Qt::black);
                        line->setPen(pen);
                        item = line;
                  } else if(e.getleaf(s).getExpression().type == ArcT){
                        double x_cen = std::get<0>(e.getleaf(s).getExpression().arc_center),   y_cen = std::get<1>(e.getleaf(s).getExpression().arc_center),   x_start = std::get<0>(e.getleaf(s).getExpression().arc_start),   y_start = std::get<1>(e.getleaf(s).getExpression().arc_start), angle = e.getleaf(s).getExpression().arc_angle;
                        double dist = sqrt(pow(x_cen - x_start,2) + pow(y_cen - y_start, 2));
                        double start_ang = atan2((y_start - y_cen), (x_start - x_cen))*2880/(atan2(0, -1));
                        double span_ang = (start_ang + angle*180/(atan2(0, -1)))*16;
                        QGraphicsArcItem *arc = new QGraphicsArcItem();
                        arc -> setRect(x_cen - dist, y_cen -dist, 2*dist, 2*dist);
                        arc -> setStartAngle(start_ang);
                        arc -> setSpanAngle(span_ang);
                        item = arc;
                  }
              }
              emit drawGraphic(item);
              return;
        }
        out = QString::fromStdString(str);
    }  else if (e.getExpression().type == PointT){
          auto x = std::get<0>(e.getExpression().PointV), y = std::get<1>(e.getExpression().PointV);
          out = QString::number(x)+QString::fromStdString(",")+QString::number(y);
    }  else if (e.getExpression().type == LineT){
          auto x_start = std::get<0>(e.getExpression().line_start), y_start = std::get<1>(e.getExpression().line_start), x_stop  = std::get<0>(e.getExpression().line_end), y_stop  = std::get<1>(e.getExpression().line_end);
          out = QString::number(x_start)+QString::fromStdString(",")+  QString::number(y_start)+QString::fromStdString(")(")+ QString::number(x_stop) +QString::fromStdString(",")+  QString::number(y_stop);
    }  else if (e.getExpression().type == ArcT){
        auto x_center = std::get<0>(e.getExpression().arc_center), y_center = std::get<1>(e.getExpression().arc_center), x_start  = std::get<0>(e.getExpression().arc_start), y_start  = std::get<1>(e.getExpression().arc_start), angle    = e.getExpression().arc_angle;
        out = QString::fromStdString("(") + QString::number(x_center)+ QString::fromStdString(",") + QString::number(y_center)+ QString::fromStdString(")(")+ QString::number(x_start) + QString::fromStdString(",") + QString::number(y_start) + QString::fromStdString(")") + QString::number(angle);
    }
    out = QString::fromStdString("(")+out+ QString::fromStdString(")");
    emit info(out);
}

void QtInterpreter::read_file(std::istream &expre){
    Interpreter interp;
    bool ok = interp.parse(expre);
    if(!ok){
      QString err = QString::fromStdString("Error: fail to parse");
      qDebug() << "fail";
      emit error(err);
    }
    else{
        try {
            Expression ans = interp.eval();
            display(ans);
        }
        catch (const InterpreterSemanticError &e){
            QString err  = "Error: "+ QString::fromStdString(e.what());
            emit error(err);
        }
    }
}
