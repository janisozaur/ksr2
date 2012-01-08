#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Common.h"

#include <QListWidgetItem>
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void addSpinBoxes(bool checked, int mCount, Range range);

private slots:
    void on_quantTriRadioButton_toggled(bool checked);

    void on_quantTraRadioButton_toggled(bool checked);

    void on_quantRelRadioButton_toggled(bool checked);

    void on_quantAbsRadioButton_toggled(bool checked);

    void on_quantifierAddPushButton_clicked();

    void on_quantifiersListWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

    void on_quantifierDeletePushButton_clicked();

    void setValues(QList<double> values);

private:
    Ui::MainWindow *ui;
    int mCount;
    FunctionType mFunctionType;

signals:
    void valuesToSet(QList<double> values);
};

#endif // MAINWINDOW_H
