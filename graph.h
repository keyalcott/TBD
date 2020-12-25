#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlTableModel>
#include <QtCharts>
#include <QChartView>
#include <QBarSet>
#include <QBarSeries>
#include <QAreaSeries>

namespace Ui {
class graph;
}

class graph : public QDialog
{
    Q_OBJECT

public:
    explicit graph(QWidget *parent = nullptr);
    ~graph();

private:
    QSqlDatabase db;
    QSqlTableModel *model;
    QSqlQuery *query;
    Ui::graph *ui;
};

#endif // GRAPH_H
