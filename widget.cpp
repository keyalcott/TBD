#include "widget.h"
#include "ui_widget.h"
#include <QTextStream>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
#include <QDateEdit>
#include <QDate>
#include <graph.h>

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("База данных поликлиники за 2020");
    db=QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hospital");
    db.setUserName("postgres");
    db.setPassword("12345");
    if(!db.open()){
        qDebug()<<db.lastError().text();
        return;
    }
    else {
        qDebug()<<"Succsess!";
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

QSqlQueryModel *model=new QSqlQueryModel;

QString str, str1;
str=ui->lineEdit->text();
str1="select doctor_id, symptoms, diagnosis, medicine, date_in, p_name, gender, "
"birth, home, phone from hospital_schema.patients inner join hospital_schema.inspections on "
"hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where "
"inspections.place_in = 'дом'and inspections.date_in='";
str1=str1+str+"'";

    model->setQuery(str1);
    ui->tableView->setModel(model);

}
void Widget::on_pushButton_2_clicked()
{
    QSqlQueryModel *model=new QSqlQueryModel;
QString str, str1;
str=ui->lineEdit_2->text();
str1="select count (distinct hospital_schema.patients.patient_id) "
"from hospital_schema.patients inner "
"join hospital_schema.inspections on hospital_schema.patients.patient_id="
"hospital_schema.inspections.patient_id where inspections.diagnosis = '";
str1=str1+str+"'";
    model->setQuery(str1);
    ui->tableView->setModel(model);
}

void Widget::on_pushButton_3_clicked()
{
QSqlQueryModel *model=new QSqlQueryModel;
QString str="", str1="";
str1="select side_effects from hospital_schema.medicines where title = '";
str=ui->lineEdit_3->text();
str1=str1+str+"'";
 model->setQuery(str1);
    ui->tableView->setModel(model);
}

void Widget::on_pushButton_4_clicked()
{
    QString log;
    log = ui->lineEdit_5->text();
QSqlQueryModel *model=new QSqlQueryModel;
QString str, str1="";
str1="select * from hospital_schema.table where doctor_id="+log;
str=ui->lineEdit_4->text();
int n = str.length();
if(n==0){model->setQuery(str1);
    ui->tableView->setModel(model);}
else{
    str1=str1+" and date_next='"+str+"'";
    model->setQuery(str1);
        ui->tableView->setModel(model);
}
}

void Widget::on_pushButton_7_clicked()
{
    QString log, pass, str;
    log = ui->lineEdit_5->text();
    pass = ui->lineEdit_6->text();

    QSqlQuery query=QSqlQuery(db);
    str="select d_password, doctor_id from hospital_schema.doctors where doctor_id=";
    str=str+log+" and d_password='"+pass+"'";

    if (query.exec(str)){
            ui->pushButton->setEnabled(true);
            ui->pushButton_2->setEnabled(true);
            ui->pushButton_3->setEnabled(true);
            ui->pushButton_4->setEnabled(true);
            ui->pushButton_5->setEnabled(true);
            ui->pushButton_6->setEnabled(true);
            ui->pushButton_12->setEnabled(false);
            ui->pushButton_13->setEnabled(false);
            ui->pushButton_8->setEnabled(true);
            ui->lineEdit_6->setText("");

            QSqlQueryModel *model=new QSqlQueryModel;
            model->setQuery("select p_name,gender,birth from hospital_schema.patients "
            "inner join hospital_schema.inspections on inspections.patient_id=patients.patient_id"
            " where inspections.doctor_id="+log);
            ui->tableView->setModel(model);
    }
}

void Widget::on_pushButton_14_clicked()
{
    QString fio, str;
    fio = ui->lineEdit_7->text();

    QSqlQuery query=QSqlQuery(db);
    str="select p_name from hospital_schema.patients where p_name='"+fio+"'";

    if(query.exec(str)){
        ui->pushButton_12->setEnabled(true);
        ui->pushButton_13->setEnabled(true);
        ui->pushButton->setEnabled(false);
        ui->pushButton_2->setEnabled(false);
        ui->pushButton_3->setEnabled(false);
        ui->pushButton_4->setEnabled(false);
        ui->pushButton_5->setEnabled(false);
        ui->pushButton_6->setEnabled(false);
        ui->pushButton_8->setEnabled(false);
    }
}
//    ui->label_2->setText(str);
void Widget::on_pushButton_12_clicked()
{
    QString fio, str;
    fio = ui->lineEdit_7->text();

    QSqlQueryModel *model=new QSqlQueryModel;
    str="select p_name, place_in, diagnosis, medicine, date_in from "
    "hospital_schema.inspections inner join hospital_schema.patients "
    "on hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.p_name='"+fio+"'";
    model->setQuery(str);
    ui->tableView->setModel(model);
}

void Widget::on_pushButton_13_clicked()
{
    QString fio, str;
    fio = ui->lineEdit_7->text();

    QSqlQueryModel *model=new QSqlQueryModel;

    str="select p_name, d_name, date_next from hospital_schema.patients join "
    "hospital_schema.table on hospital_schema.patients.patient_id=hospital_schema.table.patient_id "
    "join hospital_schema.doctors on hospital_schema.table.doctor_id="
    "hospital_schema.doctors.doctor_id where patients.p_name='"+fio+"'";
    model->setQuery(str);
    ui->tableView->setModel(model);
}
 //   ui->label_2->setText(str);
void Widget::on_pushButton_5_clicked()
{
    QString str, mon, n;
    mon = ui->lineEdit_8->text();
    int m=mon.toInt();
    m++;
    n = QString::number(m);
    QSqlQueryModel *model=new QSqlQueryModel;
    if (m==13) str="select count(patient_id) from hospital_schema.inspections where date_in>='2020-12-01' and date_in<='2020-12-31'";
    else str="select count(patient_id) from hospital_schema.inspections where date_in>='2020-"+mon+"-01' and date_in<'2020-"+n+"-01'";
    model->setQuery(str);

    ui->tableView->setModel(model);
}

void Widget::on_pushButton_6_clicked()
{
    QString ot, du, str;
    ot = ui->lineEdit_9->text();
    du = ui->lineEdit_10->text();
    int to=ot.toInt();
    int ud=du.toInt();
    to=2020-to;
    ud=2020-ud;
    ot=QString::number(to);
    du=QString::number(ud);

    QSqlQueryModel *model=new QSqlQueryModel;
    str="select count(patient_id) from hospital_schema.patients where birth<='"+ot+"-12-31' and birth>='"+du+"-01-01'";
    model->setQuery(str);
    ui->tableView->setModel(model);
}

void Widget::on_pushButton_8_clicked()
{
    graph window;
    window.setModal(true);
    window.exec();
}
