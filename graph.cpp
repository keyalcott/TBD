#include "graph.h"
#include "ui_graph.h"

#include <QTextStream>
#include <QDebug>
#include <QtSql/QSqlError>
#include <QtSql/QSqlRecord>
#include <QtSql/QSqlTableModel>
#include <QDateEdit>
#include <QDate>

graph::graph(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::graph)
{
    ui->setupUi(this);
    this->setWindowTitle("Статистика по заболеваемости и возрасту больных");

    QSqlQuery model= QSqlQuery(db);

    QBarSet*set0=new QBarSet("От 60 до 50 лет");
    QBarSet*set1=new QBarSet("От 50 до 40 лет");
    QBarSet*set2=new QBarSet("От 40 до 30 лет");
    QBarSet*set3=new QBarSet("Младше 30 лет");

    QSqlQuery query;
    QString find,mon,is;
    int m=2;
    for (int i = 0; i<11; ++i){
        mon=QString::number(m);
        is=QString::number(i+1);
        find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
        "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1990-01-01' "
        "and patients.birth<='2000-12-31' and inspections.date_in>='2020-"+is+"-01' and inspections.date_in<'2020-"+mon+"-01'";
        query.exec(find);
        query.first();
        *set3<<query.value(0).toInt();
        m++;
        //query.next();
    }
    find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
    "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1990-01-01' "
    "and patients.birth<='2000-12-31' and inspections.date_in>='2020-12-01' and inspections.date_in<'2020-12-31'";
    query.exec(find);
    query.first();
    *set3<<query.value(0).toInt();

    int t=2;
    for (int i = 0; i<11; ++i){
        mon=QString::number(t);
        is=QString::number(i+1);
        find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
        "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1980-01-01' "
        "and patients.birth<='1990-12-31' and inspections.date_in>='2020-"+is+"-01' and inspections.date_in<'2020-"+mon+"-01'";
        query.exec(find);
        query.first();
        *set2<<query.value(0).toInt();
        t++;
        //query.next();
    }
    find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
    "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1980-01-01' "
    "and patients.birth<='1990-12-31' and inspections.date_in>='2020-12-01' and inspections.date_in<'2020-12-31'";
    query.exec(find);
    query.first();
    *set2<<query.value(0).toInt();

    int p=2;
    for (int i = 0; i<11; ++i){
        mon=QString::number(p);
        is=QString::number(i+1);
        find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
        "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1970-01-01' "
        "and patients.birth<='1980-12-31' and inspections.date_in>='2020-"+is+"-01' and inspections.date_in<'2020-"+mon+"-01'";
        query.exec(find);
        query.first();
        *set1<<query.value(0).toInt();
        p++;
        //query.next();
    }
    find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
    "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1970-01-01' "
    "and patients.birth<='1980-12-31' and inspections.date_in>='2020-12-01' and inspections.date_in<'2020-12-31'";
    query.exec(find);
    query.first();
    *set1<<query.value(0).toInt();

    int r=2;
    for (int i = 0; i<11; ++i){
        mon=QString::number(r);
        is=QString::number(i+1);
        find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
        "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1960-01-01' "
        "and patients.birth<='1970-12-31' and inspections.date_in>='2020-"+is+"-01' and inspections.date_in<'2020-"+mon+"-01'";
        query.exec(find);
        query.first();
        *set0<<query.value(0).toInt();
        r++;
        //query.next();
    }
    find="select count(patients.patient_id) from hospital_schema.patients join hospital_schema.inspections on "
    "hospital_schema.patients.patient_id=hospital_schema.inspections.patient_id where patients.birth>='1960-01-01' "
    "and patients.birth<='1970-12-31' and inspections.date_in>='2020-12-01' and inspections.date_in<'2020-12-31'";
    query.exec(find);
    query.first();
    *set0<<query.value(0).toInt();

    QBarSeries*series=new QBarSeries();
    series->append(set0);
    series->append(set1);
    series->append(set2);
    series->append(set3);
    QChart *chart=new QChart();
    chart->addSeries(series);
    chart->setTitle("Статистика заболеваемых по возростам");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    QStringList categories;
    categories<<"Январь"<<"Февраль"<<"Март"<<"Апрель"<<"Май"<<"Июнь"<<"Июль"<<"Август"<<"Сентябрь"<<"Октябрь"<<"Ноябрь"<<"Декабрь";
    QBarCategoryAxis*axis= new QBarCategoryAxis();
    axis->append(categories);
    chart->createDefaultAxes();
    chart->setAxisX(axis,series);
    QChartView *chartView= new QChartView(chart);
    chartView->setParent(ui->horizontalFrame);
}

graph::~graph()
{
    delete ui;
}
