#ifndef MEMINFODIALOG_H
#define MEMINFODIALOG_H

#include <QDialog>

namespace Ui {
class MemInfoDialog;
}

class MemInfoDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MemInfoDialog(QWidget *parent = nullptr);
    ~MemInfoDialog();

private:
    Ui::MemInfoDialog *ui;
};

#endif // MEMINFODIALOG_H
