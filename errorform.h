#ifndef ERRORFORM_H
#define ERRORFORM_H

#include <QWidget>

namespace Ui {
class errorForm;
}

class errorForm : public QWidget {
    Q_OBJECT

 public:
    explicit errorForm(QWidget *parent = nullptr);
    void setError();
    ~errorForm();

 private:
    Ui::errorForm *ui;
};

#endif  // ERRORFORM_H
