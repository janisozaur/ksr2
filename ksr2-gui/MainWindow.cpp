#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Quantifier.h"

#include <QFormLayout>
#include <QSpinBox>

#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quantTriRadioButton_toggled(bool checked)
{
    Range r = (ui->quantAbsRadioButton->isChecked() ? Absolute : Relative);
    addSpinBoxes(checked, 3, r);
}

void MainWindow::on_quantTraRadioButton_toggled(bool checked)
{
    Range r = (ui->quantAbsRadioButton->isChecked() ? Absolute : Relative);
    addSpinBoxes(checked, 4, r);
}

void MainWindow::addSpinBoxes(bool checked, int count, Range range)
{
    if (checked) {
        QWidget *w = new QWidget(ui->quantifierValuesGroupBox);
        if (ui->quantifierValuesGroupBox->layout() == 0) {
            QHBoxLayout *hbl = new QHBoxLayout(ui->quantifierValuesGroupBox);
            ui->quantifierValuesGroupBox->setLayout(hbl);
        }
        ui->quantifierValuesGroupBox->layout()->addWidget(w);
        QFormLayout *fl = new QFormLayout(w);
        for (int i = 0; i < count; i++) {
            QAbstractSpinBox *asb;
            if (range == Absolute) {
                QSpinBox *sb = new QSpinBox(w);
                sb->setMinimum(0);
                sb->setMaximum(10000);
                asb = sb;
            } else {
                QDoubleSpinBox *sb = new QDoubleSpinBox(w);
                sb->setMinimum(0);
                sb->setMaximum(1);
                sb->setSingleStep(0.05);
                asb = sb;
            }
            fl->addRow(QString(QChar('A' + i)), asb);
        }
    } else {
        QLayout *fl = ui->quantifierValuesGroupBox->layout();
        if (fl != nullptr && fl->count() > 0) {
            QWidget *w = fl->takeAt(0)->widget();
            delete w;
            // there is no mem-leak here, qt handles qobject's children by itself
        }
    }
}

void MainWindow::on_quantRelRadioButton_toggled(bool checked)
{
    if (checked == false) {
        mCount = ui->quantifierValuesGroupBox->findChildren<QAbstractSpinBox *>().size();
    }
    addSpinBoxes(checked, mCount, Relative);
}

void MainWindow::on_quantAbsRadioButton_toggled(bool checked)
{
    if (checked == false) {
        mCount = ui->quantifierValuesGroupBox->findChildren<QAbstractSpinBox *>().size();
    }
    addSpinBoxes(checked, mCount, Absolute);
}

void MainWindow::on_quantifierAddPushButton_clicked()
{
    QList<QAbstractSpinBox *> sbList = ui->quantifierValuesGroupBox->findChildren<QAbstractSpinBox *>();
    QList<double> values;
    for (int i = 0; i < sbList.size(); i++) {
        values << sbList.at(i)->text().toDouble();
    }
    Range r = (ui->quantAbsRadioButton->isChecked() ? Absolute : Relative);
    Quantifier *q = new Quantifier(ui->quantifierNameLineEdit->text(), values, r, this);
    QVariant v(QMetaType::QObjectStar, q);
    QListWidgetItem *item = new QListWidgetItem(q->quantName());
    item->setData(Qt::UserRole, v);
    ui->quantifiersListWidget->addItem(item);
}
