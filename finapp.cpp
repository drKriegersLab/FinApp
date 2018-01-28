#include "finapp.h"
#include "ui_finapp.h"
#include <QTableWidgetItem>
#include <QFont>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QScatterSeries>
#include <QtCharts/QValueAxis>
#include <QtCharts/QLogValueAxis>
#include <QtWidgets/QLabel>

#include "tablemanager.h"

FinApp::FinApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinApp)
{
    ui->setupUi(this);
    string filename = "/home/drkrieger/01_PetProjects/FinApp/xml_base/2017_01.csv";
    DbMng = new DatabaseManager(100000, filename);
    TableMng = new TableManager(DbMng);
    GraphMng = new GraphManager(DbMng);

    //TableDbManager = new TableManager(filename);

}

FinApp::~FinApp()
{
    delete ui;
}

void FinApp::on_actionOpen_triggered()
{
    /* TEMPLATE
    ui->tableWidget->setRowCount(3);
    ui->tableWidget->setColumnCount(3);
    QStringList label_list;
    label_list<<"A"<<"B"<<"C";
    ui->tableWidget->setHorizontalHeaderLabels(label_list);
    ui->tableWidget->setItem(1,1, new QTableWidgetItem(QString::number(12)));
    */

    // initialize the table
    int num_of_records = TableMng->getNumOfRecords();
    ui->tableWidget->setRowCount(num_of_records);
    ui->tableWidget->setColumnCount(NUM_OF_LABELS);
    ui->tableWidget->setHorizontalHeaderLabels(TableMng->getLabels());

    // iterate over each record and set the corresponding cells in the table
    TransactionRecord record;
    for (int cyc_record = 0; cyc_record < num_of_records; cyc_record++){
        // get the record
        TableMng->getTransactionRecord(cyc_record, &record);
        // set the cells
        //QTableWidgetItem CellObject = new QTableWidgetItem();
        //CellObject.setText(QString::number(record.change));
        QFont Font;
        Font.setPixelSize(11);
        ui->tableWidget->setFont(Font);
        ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->tableWidget->setItem(cyc_record, LABEL_CHANGE, new QTableWidgetItem(QString::number(record.change)));
        ui->tableWidget->setItem(cyc_record, LABEL_BALANCE, new QTableWidgetItem(QString::number(record.balance)));
        ui->tableWidget->setItem(cyc_record, LABEL_TR_NAME, new QTableWidgetItem(QString::fromStdString(record.tr_name)));
        ui->tableWidget->setItem(cyc_record, LABEL_PARTNER_ID, new QTableWidgetItem(QString::fromStdString(record.partner_id)));
        ui->tableWidget->setItem(cyc_record, LABEL_TR_TYPE, new QTableWidgetItem(QString::fromStdString(record.tr_type)));
    }
    /* TEMPLATE */
    /*
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    QtCharts::QChart *chart = new QtCharts::QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Simple line chart example");
        */

    // create the chart
    QtCharts::QChartView *chartView = new QtCharts::QChartView(GraphMng->getGraphAllTransaction());
        //QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
    // set up the view
    chartView->setRenderHint(QPainter::Antialiasing);
    QGridLayout *ChartLayout = new QGridLayout;
    ChartLayout->addWidget(chartView, 1, 1);
    ui->frame_graphs->setLayout(ChartLayout);
    ui->frame_graphs->setFrameShape(QFrame::NoFrame);

}

/*
 * DEBUG PROMPTS
 * */
void FinApp::dropDebugPrompt(string message) {
    cout << "[FinApp] : " << message << endl;
}
