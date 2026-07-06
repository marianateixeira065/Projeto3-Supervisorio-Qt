#ifndef PLOTTER_H
#define PLOTTER_H

#include <QWidget>
#include <vector>

class Plotter : public QWidget
{
    Q_OBJECT
private:
    std::vector<double> tempos;
    std::vector<double> valores;

public:
    explicit Plotter(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void setDados(std::vector<double> t, std::vector<double> v);
};

#endif
