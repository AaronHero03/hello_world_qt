#include "MainWindow.h"
#include <QMenuBar>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QApplication> 

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      label_(new QLabel("Formulario para entrar al Tec", this)),
      button_(new QPushButton("Presióname", this)),
      nombreEdit_(new QLineEdit(this)),
      carreraEdit_(new QLineEdit(this)),
      edadEdit_(new QLineEdit(this)),
      textEdit_(new QTextEdit(this))
{
    
    // 1) Configurar la ventana principal
    setWindowTitle("Formulario de admisiones 2025");
    resize(600, 400);

    // Cambia el tema de toda la app a un estilo oscuro simple
    qApp->setStyleSheet(R"(
        QMainWindow { background-color: #232629; }
        QLabel { color: #f0f0f0; font-size: 14px; }
        QLineEdit, QTextEdit {
            background: #31363b;
            color: #f0f0f0;
            border: 1px solid #555;
            border-radius: 4px;
        }
        QPushButton {
            background: #3daee9;
            color: #fff;
            border-radius: 4px;
            padding: 5px 10px;
        }
        QPushButton:hover {
            background: #50bfff;
        }
        QMenuBar, QMenu, QStatusBar, QToolBar {
            background: #232629;
            color: #f0f0f0;
        }
        QMenu::item:selected {
            background: #3daee9;
        }
    )");

    // 2) Barra de menú con acción "Salir"
    QMenu *menuArchivo = menuBar()->addMenu("&Archivo");
    QMenu *menuEditar = menuBar()->addMenu("&Editar");

    QAction *exitAction = menuArchivo->addAction("Salir");
    QAction *secondAction = menuEditar->addAction("Segunda Acción");
    connect(exitAction, &QAction::triggered, this, &QMainWindow::close);
    connect(secondAction, &QAction::triggered, this, &QMainWindow::close);

    // 3) Barra de estado
    statusBar()->showMessage("Listo");

    // 4) Barra de herramientas que reutiliza la acción "Salir"
    QToolBar *toolbar = addToolBar("Principal");
    toolbar->addAction(exitAction);
    toolbar->addAction(secondAction);

    // 5) Conectar el botón al slot
    connect(button_, &QPushButton::clicked, this, &MainWindow::on_buttonClicked);

    ////////////////////////////////////////////////////////////////////////////


    // 6) Crear un widget central con layout
    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    // Layout vertical principal
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(label_);

    // Layout horizontal para QLabel + QLineEdit + QPushButton
    QHBoxLayout *nombre = new QHBoxLayout;
    nombre->addWidget(new QLabel("Nombre", this));
    nombre->addWidget(nombreEdit_);
    vbox->addLayout(nombre);

    // Layout horizontal para QLabel + QLineEdit + QPushButton
    QHBoxLayout *carrera = new QHBoxLayout;
    carrera->addWidget(new QLabel("Carrera", this));
    carrera->addWidget(carreraEdit_);
    vbox->addLayout(carrera);

    // Layout horizontal para QLabel + QLineEdit + QPushButton
    QHBoxLayout *edad = new QHBoxLayout;
    edad->addWidget(new QLabel("Edad", this));
    edad->addWidget(edadEdit_);
    vbox->addLayout(edad);

    vbox->addWidget(button_);

    // QLabel y QTextEdit para mostrar líneas
    vbox->addWidget(new QLabel("Editor de Texto:", this));
    vbox->addWidget(textEdit_);

    central->setLayout(vbox);

}

MainWindow::~MainWindow()
{
    // Qt libera los hijos automáticamente
}

void MainWindow::on_buttonClicked()
{
    // Obtener valores de todos los campos
    QString nombre = nombreEdit_->text();
    QString carrera = carreraEdit_->text();
    QString edad = edadEdit_->text();

    // Validación
    if(nombre.isEmpty() || carrera.isEmpty() || edad.isEmpty()) {
        QMessageBox::warning(this, "Advertencia", "Todos los campos son obligatorios.");
        return;
    }

    // Mostrar datos en el área de texto
    QString datos = QString("Nombre: %1\nCarrera: %2\nEdad: %3\n")
                    .arg(nombre)
                    .arg(carrera)
                    .arg(edad);
    
    textEdit_->append(datos);
    
    // Limpiar campos después de enviar
    nombreEdit_->clear();
    carreraEdit_->clear();
    edadEdit_->clear();
}
