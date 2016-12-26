#ifndef BOOKINFO_H
#define BOOKINFO_H

#include <QDialog>

namespace Ui {
class BookInfo;
}

class BookInfo : public QDialog
{
    Q_OBJECT

public:
    explicit BookInfo(QWidget *parent = 0);
    ~BookInfo();

private:
    Ui::BookInfo *ui;
};

#endif // BOOKINFO_H
