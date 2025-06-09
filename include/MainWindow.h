#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QColorDialog> // <- nuevo include

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    
private slots:
    void on_buttonClicked();

private:
    QLabel      *label_;
    QPushButton *button_;

    QLineEdit *nombreEdit_;  // Campo específico para nombre
    QLineEdit *carreraEdit_; // Campo específico para carrera
    QLineEdit *edadEdit_;    // Campo específico para edad
    
    QTextEdit *textEdit_;
};
