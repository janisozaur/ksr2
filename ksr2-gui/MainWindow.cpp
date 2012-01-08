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
    on_quantTriRadioButton_toggled(false);
    on_quantTriRadioButton_toggled(true);
    connect(this, SIGNAL(valuesToSet(QList<double>)), SLOT(setValues(QList<double>)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_quantTriRadioButton_toggled(bool checked)
{
    Range r = (ui->quantAbsRadioButton->isChecked() ? Absolute : Relative);
    mFunctionType = Triangle;
    addSpinBoxes(checked, 3, r);
}

void MainWindow::on_quantTraRadioButton_toggled(bool checked)
{
    Range r = (ui->quantAbsRadioButton->isChecked() ? Absolute : Relative);
    mFunctionType = Trapezoid;
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
    bool ok = true;
    QList<double> values;
    for (int i = 0; i < sbList.size(); i++) {
        double val = sbList.at(i)->text().toDouble();
        if (i > 0 && values.last() > val) {
            ok = false;
        }
        values << val;
    }
    if (!ok) {
        QString err = "problem with values";
        qDebug() << err;
        ui->statusBar->showMessage(err, 2000);
        return;
    }
    Range r = (ui->quantAbsRadioButton->isChecked() ? Absolute : Relative);
    const QString name = ui->quantifierNameLineEdit->text();
    if (name.isNull() || name.isEmpty()) {
        QString err = "problem with name";
        qDebug() << err;
        ui->statusBar->showMessage(err, 2000);
        return;
    }
    if (ui->quantifiersListWidget->findItems(name, Qt::MatchFixedString).size() > 0) {
        QString err = "such item already exists";
        qDebug() << err;
        ui->statusBar->showMessage(err, 2000);
        return;
    }
    Quantifier q(name, values, r, (mFunctionType == Triangle ? "TRIANGLE" : "TRAPEZOID"), this);
    //qDebug() << q << (void *)q << qobject_cast<QObject *>(q);
    QVariant v = QVariant::fromValue(q);
    QListWidgetItem *item = new QListWidgetItem(q.quantName());
    item->setData(Qt::UserRole, v);
    ui->quantifiersListWidget->addItem(item);
    ui->statusBar->showMessage(QString("quantifier \"%1\" added successfully").arg(name), 2000);
    QTextStream stream(stdout);
    stream << (q) << endl;
}

void MainWindow::setValues(QList<double> values)
{
    QList<QAbstractSpinBox *> sbList = ui->quantifierValuesGroupBox->findChildren<QAbstractSpinBox *>();
    qDebug() << "sizes:" << sbList.size() << values.size();
    for (int i = 0; i < values.size(); i++) {
        sbList[i]->setProperty("value", values.at(i));
    }
}

void MainWindow::on_quantifiersListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (current == nullptr) {
        ui->quantifierDeletePushButton->setEnabled(false);
    } else {
        ui->quantifierDeletePushButton->setEnabled(true);
        QListWidgetItem *li = ui->quantifiersListWidget->item(ui->quantifiersListWidget->currentRow());
        QVariant v = li->data(Qt::UserRole);
        Quantifier q = v.value<Quantifier>();
        if (q.typeName() == "TRAPEZOID") {
            ui->quantTraRadioButton->setChecked(true);
        } else {
            ui->quantTriRadioButton->setChecked(true);
        }
        if (q.range() == Relative) {
            ui->quantRelRadioButton->setChecked(true);
        } else {
            ui->quantAbsRadioButton->setChecked(true);
        }
        emit valuesToSet(q.values());
        ui->quantifierNameLineEdit->setText(q.quantName());
    }
}

void MainWindow::on_quantifierDeletePushButton_clicked()
{
    QListWidgetItem *li = ui->quantifiersListWidget->takeItem(ui->quantifiersListWidget->currentRow());
    QVariant v = li->data(Qt::UserRole);
    qDebug() << "type: " << v.typeName();
    qDebug() << "can convert:" << v.canConvert<Quantifier>();
    Quantifier q = v.value<Quantifier>();
    qDebug() << "removing" << q.quantName();
}
