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
#include "graphmanager.h"
#include <QMessageBox>
#include <sstream>


//#include "tablemanager.h"

FinApp::FinApp(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FinApp) {
        ui->setupUi(this);
        //string filename = "/home/drkrieger/01_PetProjects/FinApp/xml_base/2017_01.csv";
        //TableDbManager = new TableManager(filename);

        // set filter selector combo boxes to unvisible
        ui->filterSelector1->setVisible(false);
        ui->filterSelector2->setVisible(false);       
        ui->filterSelector3->setVisible(false);

        // connect filterSelector comboboxes manually to them main event handler
        connect(ui->filterSelector1, SIGNAL(currentTextChanged(QString)), this, SLOT(on_filterSelector_currentTextChanged(QString)));
        connect(ui->filterSelector2, SIGNAL(currentTextChanged(QString)), this, SLOT(on_filterSelector_currentTextChanged(QString)));
        connect(ui->filterSelector3, SIGNAL(currentTextChanged(QString)), this, SLOT(on_filterSelector_currentTextChanged(QString)));

        // the content of comboboxes is defined in the first one only. Collect the list into a vector named combobox_items
        for(int cyc_filter_items = 0; cyc_filter_items < ui->filterSelector->count(); cyc_filter_items++) {
            filter_items.push_back(ui->filterSelector->itemText(cyc_filter_items));
        }

        initGraphView();
        // set up graph view's checkboxes
        connect(ui->checkBoxGraphSel_all, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged_all(int)));
        connect(ui->checkBoxGraphSel_income, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged_income(int)));
        connect(ui->checkBoxGraphSel_expenditure, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged_expenditure(int)));
        connect(ui->checkBoxGraphSel_exp_all, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged_exp_all(int)));
        connect(ui->checkBoxGraphSel_exp_paypass, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged_exp_paypass(int)));
        connect(ui->checkBoxGraphSel_exp_cashout, SIGNAL(stateChanged(int)), this, SLOT(checkBoxStateChanged_exp_cashout(int)));

        // store main checkboxes to the main_checkboxes (managing of exclusive checked status)
        main_checkboxes.push_back(ui->checkBoxGraphSel_all);
        main_checkboxes.push_back(ui->checkBoxGraphSel_income);
        main_checkboxes.push_back(ui->checkBoxGraphSel_expenditure);
    }

FinApp::~FinApp() {
    delete ui;
}

void FinApp::initGraphView() {
    ChartLayout = new QGridLayout();
    ui->frame_graphs->setLayout(ChartLayout);
    ui->frame_graphs->setFrameShape(QFrame::NoFrame);
}

void FinApp::on_actionOpen_triggered() {
    QString filename = QFileDialog::getOpenFileName(this, "Open source file", "/home/drkrieger/01_PetProjects/FinApp/xml_base/", "CSV files (*.csv)");

    //DbMng = new DatabaseManager(100000, filename.toStdString());
    DbFull = new DataBase(100000, filename.toStdString());
    //TableMng = new TableManager(DbMng);
    //GraphMng = new GraphManager(DbMng);
    full_database = DbFull->getAllTransactions();
    filtered_database = full_database;

    showTableSelectedTransactions(filtered_database);

    //Graph = new GraphManager(ChartLayout, filtered_database, "not title :-(");
    //GraphManager::createGraphChartView(ChartLayout, filtered_database, "no title :-)");
    //showTableAllTransactions();
    //showGraphAllTransactions();
}

/*
 * Handler of text change's event for all filter selector comboboxes
 * It reveals the next filter selector and exclude the used items from the possibilities.
 * */
void FinApp::on_filterSelector_currentTextChanged(const QString &current_text)
{

    filtered_database = DatabaseManager::selectFilter(current_text, filtered_database);
    showTableSelectedTransactions(filtered_database);
    //DataBase selected_database = DataBase(filtered_database);
    //Graph->addSeries(selected_database.getAllTransactions());


    // store the selected item to the list
    filter_selected_items.push_back(current_text);
    filter_selector_counter++;

    bool flag_found = false;

    // masking out the connection --> with this way the first change will not trigger this handler function
    ui->filterSelector1->blockSignals(true);
    ui->filterSelector2->blockSignals(true);
    ui->filterSelector3->blockSignals(true);

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




    // unmask the connections
    ui->filterSelector1->blockSignals(false);
    ui->filterSelector2->blockSignals(false);
    ui->filterSelector3->blockSignals(false);
}

void FinApp::on_buttonFilterReset_released()
{
    // set filter selectocheckBoxGraphSel_onr combo boxes to unvisible
    ui->filterSelector1->setVisible(false);
    ui->filterSelector2->setVisible(false);
    ui->filterSelector3->setVisible(false);

    // erase selected items
    filter_selected_items.clear();

    // reset filter selector's selector counter :-)
    filter_selector_counter = 0;

    // set the first filterSelector's field to default (masked, becasuse we don't want to trigger the handler function)
    ui->filterSelector->blockSignals(true);
    ui->filterSelector->setCurrentIndex(0);
    ui->filterSelector->blockSignals(false);

    // reset table
    filtered_database = full_database;
    showTableSelectedTransactions(filtered_database);
    //showGraphSelectedTransactions(filtered_database);
    //GraphManager::createGraphChartView(ChartLayout, filtered_database, "no title :-)");
    //Graph = new GraphManager(ChartLayout, filtered_database, "not title :-(");

}

void FinApp::setFilterSelectorItems(QComboBox *filterSelComboBox) {
    bool flag_found;

    filterSelComboBox->clear();
    // irerate over all pre-defined filter items
    for (int cyc_items = 0; cyc_items < filter_items.size(); cyc_items ++ ) {
        flag_found = false;

        // check that the current item is in the selected ones or not. If not, store it to the output combobox's item list
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

void FinApp::checkBoxStateChanged_all(int status) {
    if (status == 2) {
        clearGraphSelCheckBoxesExcept(ui->checkBoxGraphSel_all->text());

        Graph = new GraphManager(ChartLayout, DbFull->getAllTransactions(), "all changes");
    }
    // TODO: empty graph
}

void FinApp::checkBoxStateChanged_income(int status){
    if (status == 2) {
        clearGraphSelCheckBoxesExcept(ui->checkBoxGraphSel_income->text());
        DataBase selected_database = DataBase( DatabaseManager::selectFilter(STRING_SELECT_FIELD_INCOME, DbFull->getAllTransactions()));
        Graph = new GraphManager(ChartLayout, selected_database.getAllTransactions(), STRING_SELECT_FIELD_INCOME);

    }
    // TODO: empty graph
}

void FinApp::checkBoxStateChanged_expenditure(int status) {

    cout << ui->checkBoxGraphSel_expenditure->text().toStdString() << endl;
    if (status == 2) {
        // enable sub-checkboxes
        ui->checkBoxGraphSel_exp_all->setEnabled(true);
        ui->checkBoxGraphSel_exp_all->setChecked(true);

        ui->checkBoxGraphSel_exp_cashout->setEnabled(true);

        ui->checkBoxGraphSel_exp_paypass->setEnabled(true);

        clearGraphSelCheckBoxesExcept(ui->checkBoxGraphSel_expenditure->text());



    }
    else {
        // TODO: empty graph
        // disable and uncheck sub-checkboxes
        ui->checkBoxGraphSel_exp_all->setEnabled(false);
        ui->checkBoxGraphSel_exp_all->setChecked(false);

        ui->checkBoxGraphSel_exp_cashout->setEnabled(false);
        ui->checkBoxGraphSel_exp_cashout->setChecked(false);

        ui->checkBoxGraphSel_exp_paypass->setEnabled(false);
        ui->checkBoxGraphSel_exp_paypass->setChecked(false);
    }
}

void FinApp::checkBoxStateChanged_exp_all(int status) {
    // set graph
    DataBase selected_database = DataBase( DatabaseManager::selectFilter(STRING_SELECT_FIELD_EXPENDITURE, DbFull->getAllTransactions()));
    selected_database.negateTotalDataBase();
    Graph = new GraphManager(ChartLayout, selected_database.getAllTransactions(), STRING_SELECT_FIELD_EXPENDITURE);
}

void FinApp::checkBoxStateChanged_exp_cashout(int status) {

}

void FinApp::checkBoxStateChanged_exp_paypass(int status) {
    // set graph
}


void FinApp::clearGraphSelCheckBoxesExcept(QString except_checkbox_name) {
    for (int cyc_checkbox = 0; cyc_checkbox < main_checkboxes.size(); cyc_checkbox++) {
        if (main_checkboxes[cyc_checkbox]->text() != except_checkbox_name) {
            main_checkboxes[cyc_checkbox]->setChecked(false);
        }
    }
}

/*
 * DEBUG PROMPTS
 * */
void FinApp::dropDebugPrompt(string message) {
    cout << "[FinApp] : " << message << endl;
}
