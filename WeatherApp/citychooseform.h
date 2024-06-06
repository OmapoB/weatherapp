#ifndef CITYCHOOSEFORM_H
#define CITYCHOOSEFORM_H

#include <QMainWindow>

namespace Ui {
class CityChooseForm;
}

class CityChooseForm : public QMainWindow
{
    Q_OBJECT

public:
    explicit CityChooseForm(QWidget *parent = nullptr);
    ~CityChooseForm();

private slots:
    void on_cityEnterButton_clicked();

private:
    Ui::CityChooseForm *ui;
};

#endif // CITYCHOOSEFORM_H
