#include "calc.h"

#include <QButtonGroup>

#include "../Controller/controller.h"
#include "ui_calc.h"

bool Point = true;
int Bracers = 0;
bool graf = false;
QLineSeries *series;
QChart *chart;
QChartView *chartView;

calc::calc(QWidget *parent) : QMainWindow(parent), ui(new Ui::calc) {
  ui->setupUi(this);

  for (int i = 0; i < 10; i++) {
    QString butName = "Button" + QString::number(i);
    QPushButton *temp = calc::findChild<QPushButton *>(butName);
    ui->buttonGroupNumbers->setId(temp, i);
  }

  connect(ui->buttonGroupNumbers, SIGNAL(buttonReleased(int)), this,
          SLOT(NumPressed(int)));

  connect(ui->Buttonadd, SIGNAL(released()), this, SLOT(MathButtonPressed()));
  connect(ui->Buttonsub, SIGNAL(released()), this, SLOT(MathButtonPressed()));
  connect(ui->Buttonmul, SIGNAL(released()), this, SLOT(MathButtonPressed()));
  connect(ui->Buttondiv, SIGNAL(released()), this, SLOT(MathButtonPressed()));
  connect(ui->Buttonmod, SIGNAL(released()), this, SLOT(MathButtonPressed()));
  connect(ui->Buttonpow, SIGNAL(released()), this, SLOT(MathButtonPressed()));

  connect(ui->ButtonAC, SIGNAL(released()), this, SLOT(ACButtonPressed()));

  connect(ui->ButtonPoint, SIGNAL(released()), this,
          SLOT(PointButtonPressed()));
  connect(ui->Buttoneq, SIGNAL(released()), this, SLOT(EQButtonPressed()));
  connect(ui->Buttonopen, SIGNAL(released()), this, SLOT(OpenButtonPressed()));
  connect(ui->Buttonclose, SIGNAL(released()), this,
          SLOT(CloseButtonPressed()));

  connect(ui->Buttonsin, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttoncos, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttontan, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttonasin, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttonacos, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttonatan, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttonln, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttonlog, SIGNAL(released()), this, SLOT(AdvButtonPressed()));
  connect(ui->Buttonsqrt, SIGNAL(released()), this, SLOT(AdvButtonPressed()));

  connect(ui->Buttonx, SIGNAL(released()), this, SLOT(XButtonPressed()));
  connect(ui->Buttonsign, SIGNAL(released()), this, SLOT(SignButtonPressed()));
}

calc::~calc() { delete ui; }

void calc::SetButtonsNums(bool b) {
  ui->Button0->setEnabled(b);
  ui->Button1->setEnabled(b);
  ui->Button2->setEnabled(b);
  ui->Button3->setEnabled(b);
  ui->Button4->setEnabled(b);
  ui->Button5->setEnabled(b);
  ui->Button6->setEnabled(b);
  ui->Button7->setEnabled(b);
  ui->Button8->setEnabled(b);
  ui->Button9->setEnabled(b);
}

void calc::SetButtonsBinar(bool b) {
  ui->Buttonadd->setEnabled(b);
  ui->Buttonsub->setEnabled(b);
  ui->Buttonmul->setEnabled(b);
  ui->Buttondiv->setEnabled(b);
  ui->Buttonpow->setEnabled(b);
  ui->Buttonmod->setEnabled(b);
}

void calc::SetButtonsUnar(bool b) {
  ui->Buttonsin->setEnabled(b);
  ui->Buttoncos->setEnabled(b);
  ui->Buttontan->setEnabled(b);
  ui->Buttonln->setEnabled(b);
  ui->Buttonasin->setEnabled(b);
  ui->Buttonacos->setEnabled(b);
  ui->Buttonatan->setEnabled(b);
  ui->Buttonlog->setEnabled(b);
  ui->Buttonsqrt->setEnabled(b);
}

void calc::NumPressed(int n) {
  if (Point) ui->ButtonPoint->setEnabled(true);
  SetButtonsBinar(true);
  QString displayVal = ui->Display->text();
  if (QString::compare(displayVal, "0", Qt::CaseInsensitive) == 0) {
    ui->Display->setText(QString::number(n));
  } else {
    ui->Display->setText(ui->Display->text() + QString::number(n));
  }
  if (Bracers == 0)
    ui->Buttoneq->setEnabled(true);
  else
    ui->Buttonclose->setEnabled(true);
  ui->Buttonopen->setEnabled(false);
  SetButtonsUnar(false);
  ui->Buttonx->setEnabled(false);
  ui->Buttonsign->setEnabled(false);
}

void calc::MathButtonPressed() {
  Point = true;
  QString displayVal = ui->Display->text();
  QPushButton *button = (QPushButton *)sender();
  QString butVal = button->text();
  if (butVal == "pow") butVal = "^";
  ui->Display->setText(displayVal + " " + butVal + " ");
  SetButtonsBinar(false);
  ui->Buttoneq->setEnabled(false);
  ui->Buttonopen->setEnabled(true);
  ui->Buttonclose->setEnabled(false);
  SetButtonsUnar(true);
  SetButtonsNums(true);
  ui->Buttonx->setEnabled(true);
  ui->Buttonsign->setEnabled(true);
  ui->ButtonPoint->setEnabled(false);
}

void calc::ACButtonPressed() {
  ui->Display->setText("0");
  Point = true;
  Bracers = 0;
  graf = false;
  SetButtonsUnar(true);
  SetButtonsBinar(true);
  ui->ButtonPoint->setEnabled(true);
  ui->Buttonopen->setEnabled(true);
  SetButtonsNums(true);
  ui->Buttonx->setEnabled(true);
  ui->lineEdit->setEnabled(false);
  ui->lineEdit_2->setEnabled(false);
  ui->lineEdit_3->setEnabled(false);
  ui->lineEdit_4->setEnabled(false);
  ui->Buttonsign->setEnabled(true);
  ui->frame->hide();
}

void calc::PointButtonPressed() {
  QString displayVal = ui->Display->text();
  ui->Display->setText(displayVal + ".");
  Point = false;
  ui->ButtonPoint->setEnabled(false);
  SetButtonsBinar(false);
  ui->Buttoneq->setEnabled(false);
  SetButtonsUnar(false);
  ui->Buttonx->setEnabled(false);
}

void calc::EQButtonPressed() {
  double x = ui->lineEdit->text().toDouble();
  QString val = ui->Display->text();
  if (graf) {
    double xmin = ui->lineEdit->text().toDouble();
    double xmax = ui->lineEdit_2->text().toDouble();
    double ymin = ui->lineEdit_3->text().toDouble();
    double ymax = ui->lineEdit_4->text().toDouble();

    if (xmax - xmin > 0.0001 && ymax - ymin > 0.0001) {
      series = new QLineSeries();
      for (; x <= xmax; x = x + (xmax - xmin) / 100) {
        s21::Calculator calc = s21::Calculator(&x);
        Controller cont(&calc);
        double y = cont.Calculate(val.toStdString());
        series->append(x, y);
      }
      chart = new QChart();
      chartView = new QChartView(chart);
      chartView->setRenderHint(QPainter::Antialiasing);
      chart->legend()->hide();
      chart->addSeries(series);
      chart->createDefaultAxes();
      chart->axes(Qt::Vertical).first()->setRange(ymin, ymax);
      chartView->setParent(ui->frame);
      chartView->resize(780, 390);
      chartView->show();
      ui->frame->show();
    }

  } else {
    s21::Calculator calc;
    Controller cont(&calc);
    std::string t = val.toStdString();
    double res = cont.Calculate(t);
    QString text;
    text.setNum(res, 'f', 7);
    ui->Display->setText(text);
    if (std::isnan(res) || res == INFINITY || res == -INFINITY) {
      SetButtonsNums(false);
      ui->Buttonsign->setEnabled(false);
      ui->ButtonPoint->setEnabled(false);
    } else {
      if (QString::number(res, 'f', -1).contains('.')) {
        Point = false;
        ui->ButtonPoint->setEnabled(false);
      } else {
        Point = true;
        ui->ButtonPoint->setEnabled(true);
      }
      if (res != 0) {
        ui->Buttonsign->setEnabled(false);
      } else {
        ui->Buttonsign->setEnabled(true);
      }
      SetButtonsNums(true);
    }
    ui->Buttonopen->setEnabled(false);
    ui->Buttonclose->setEnabled(false);
    ui->Buttonx->setEnabled(false);
  }
}

void calc::OpenButtonPressed() {
  QString displayVal = ui->Display->text();
  if (QString::compare(displayVal, "0", Qt::CaseInsensitive) == 0) {
    ui->Display->setText("(");
  } else {
    ui->Display->setText(displayVal + "(");
  }

  ui->ButtonPoint->setEnabled(false);
  SetButtonsBinar(false);
  ui->Buttoneq->setEnabled(false);
  Bracers++;
  SetButtonsUnar(true);
  SetButtonsNums(true);
  ui->Buttonx->setEnabled(true);
  ui->Buttonsign->setEnabled(true);
}

void calc::CloseButtonPressed() {
  QString displayVal = ui->Display->text();
  ui->Display->setText(displayVal + ")");
  Bracers--;
  ui->ButtonPoint->setEnabled(false);
  SetButtonsBinar(true);
  if (Bracers < 1) ui->Buttonclose->setEnabled(false);
  if (Bracers == 0)
    ui->Buttoneq->setEnabled(true);
  else
    ui->Buttoneq->setEnabled(false);
  SetButtonsNums(false);
  ui->Buttonx->setEnabled(false);
  SetButtonsUnar(false);
  ui->Buttonsign->setEnabled(false);
}

void calc::AdvButtonPressed() {
  QString displayVal = ui->Display->text();
  QPushButton *button = (QPushButton *)sender();
  QString butVal = button->text();
  if (QString::compare(displayVal, "0", Qt::CaseInsensitive) == 0) {
    ui->Display->setText(butVal + "(");
  } else {
    ui->Display->setText(displayVal + butVal + "(");
  }
  Bracers++;
  ui->ButtonPoint->setEnabled(false);
  SetButtonsBinar(false);
  ui->Buttoneq->setEnabled(false);
  ui->Buttonsign->setEnabled(true);
}

void calc::XButtonPressed() {
  QString displayVal = ui->Display->text();
  if (QString::compare(displayVal, "0", Qt::CaseInsensitive) == 0) {
    ui->Display->setText("x");
  } else {
    ui->Display->setText(displayVal + 'x');
  }
  graf = true;
  ui->ButtonPoint->setEnabled(false);
  SetButtonsBinar(true);
  if (Bracers == 0)
    ui->Buttoneq->setEnabled(true);
  else
    ui->Buttonclose->setEnabled(true);
  SetButtonsNums(false);
  ui->Buttonx->setEnabled(false);
  SetButtonsUnar(false);
  ui->ButtonPoint->setEnabled(false);
  ui->Buttonopen->setEnabled(false);
  ui->lineEdit->setEnabled(true);
  ui->lineEdit_2->setEnabled(true);
  ui->lineEdit_3->setEnabled(true);
  ui->lineEdit_4->setEnabled(true);
  ui->Buttonsign->setEnabled(false);
}

void calc::SignButtonPressed() {
  Point = true;
  QString displayVal = ui->Display->text();
  if (displayVal.endsWith('-', Qt::CaseInsensitive)) {
    displayVal.chop(1);
    ui->Display->setText(displayVal + "+");
  } else if (displayVal.endsWith('+', Qt::CaseInsensitive)) {
    displayVal.chop(1);
    ui->Display->setText(displayVal + "-");
  } else if (QString::compare(displayVal, "0", Qt::CaseInsensitive) == 0) {
    ui->Display->setText("-");
  } else {
    ui->Display->setText(displayVal + "-");
  }
  SetButtonsBinar(false);
  ui->Buttoneq->setEnabled(false);
  ui->Buttonopen->setEnabled(true);
  ui->Buttonclose->setEnabled(false);
  SetButtonsUnar(true);
  SetButtonsNums(true);
  ui->Buttonx->setEnabled(true);
}
