#include "finapp.h"
#include "ui_finapp.h"
#include <QFileDialog>
#include <QObject>
#include <QDebug>
//#include <QTableWidgetItem>
//#include <QFont>
//#include <QtWidgets/QApplication>
//#include <QtWidgets/QMainWindow>
//#include <QtCharts/QChartView>
//#include <QtCharts/QLineSeries>
//#include <QtCharts/QScatterSeries>
//#include <QtCharts/QValueAxis>
//#include <QtCharts/QLogValueAxis>
//#include <QtWidgets/QLabel>
#include <QMessageBox>


//#include "tablemanager.h"

FinApp::FinApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinApp) {
        ui->setupUi(this);
        //string filename = "/home/drkrieger/01_PetProjects/FinApp/xml_base/2017_01.csv";
        //TableDbManager = new TableManager(filename);

        // connect manually the other comboboxes to the first one's handler function
        connect(ui->filterSelector1, SIGNAL(currentTextChanged(QString)), this, SLOT(on_filterSelector_currentTextChanged(QString)));
        ui->filterSelector1->setVisible(false);

        connect(ui->filterSelector2, SIGNAL(currentTextChanged(QString)), this, SLOT(on_filterSelector_currentTextChanged(QString)));
        ui->filterSelector2->setVisible(false);

        connect(ui->filterSelector3, SIGNAL(currentTextChanged(QString)), this, SLOT(on_filterSelector_currentTextChanged(QString)));
        ui->filterSelector3->setVisible(false);

        // the content of comboboxes is defined in the first one only. Collect the list into a vector named combobox_items

        for(int cyc_filter_items = 0; cyc_filter_items < ui->filterSelector->count(); cyc_filter_items++) {
            filter_items.push_back(ui->filterSelector->itemText(cyc_filter_items));
        }
    }

FinApp::~FinApp() {
    delete ui;
}

void FinApp::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open source file", "/home/drkrieger/01_PetProjects/FinApp/xml_base/", "CSV files (*.csv)");

    DbMng = new DatabaseManager(100000, filename.toStdString());
    TableMng = new TableManager(DbMng);
    GraphMng = new GraphManager(DbMng);

    showTableAllTransactions();
    showGraphAllTransactions();



}

/*
 * DEBUG PROMPTS
 * */
void FinApp::dropDebugPrompt(string message) {
    cout << "[FinApp] : " << message << endl;
}


void FinApp::setFilterSelectorItems(QComboBox *filterSelComboBox) {
    bool flag_found;

    for (int cyc_items = 0; cyc_items < filter_items.size(); cyc_items ++ ) {
        flag_found = false;

        for (int cyc_selected_items = 0; cyc_selected_items < filter_selected_items.size(); cyc_selected_items++) {
            //if (QString::compare(combobox_items[cyc_items],combobox_selected_items[cyc_selected_items], Qt::CaseInsensitive)) {
            if (filter_items[cyc_items] == filter_selected_items[cyc_selected_items]) {
                flag_found = true;
                break;
            }
        }

        if (!flag_found) {
            filterSelComboBox->addItem(filter_items[cyc_items]);
        }
    }
}

/*
 * Handler of text change's event for all filter selector comboboxes
 * It reveals the next filter selector and exclude the used items from the possibilities.
 * */

void FinApp::on_filterSelector_currentTextChanged(const QString &current_text)
{
    //QMessageBox::information(this, "muhaha", current_text);

    // store the selected item to the list
    filter_selected_items.push_back(current_text);
    filter_selector_counter++;

    bool flag_found = false;

    // reveal the next filter selector and set its items
    qInfo() << filter_selector_counter;
    switch (filter_selector_counter) {
    case 1:
        ui->filterSelector1->setVisible(true);
        setFilterSelectorItems(ui->filterSelector1);
        break;
    case 2:
        ui->filterSelector2->setVisible(true);
        setFilterSelectorItems(ui->filterSelector2);
        break;
    case 3:
        ui->filterSelector3->setVisible(true);
        setFilterSelectorItems(ui->filterSelector3);
        break;
    default:
        break;
    }
}
