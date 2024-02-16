#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "QDialog"
#include "ctunes.h"
#include "InvalidRateException.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    CTunes ctunes;
    int codigo = ctunes.getcodigo(0);

    ui->setupUi(this);

    QString codigoString = QString::number(codigo);
    ui->lineEdit_codigo->setText(codigoString);


}

MainWindow::~MainWindow()
{
    //delete ui;
}

/*void MainWindow::on_pushButton_clicked()
{
   // QMessageBox:: information(this,"hello",QString("helloword"));

    ui->stackedWidget->setCurrentIndex(0);


}*/






void MainWindow::on_return_B_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(7);

}

void MainWindow::on_return_B_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_return_B_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_return_B_4_clicked()
{
     ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_return_B_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_return_B_6_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_add_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}


void MainWindow::on_review_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_dowload_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_song_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_info_Button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}




void MainWindow::on_exit_Button_clicked()
{
    exit(0);
    if(ui->radioButton_0->isChecked()||ui->radioButton_1->isChecked()||ui->radioButton_2->isChecked()||ui->radioButton_3->isChecked()||ui->radioButton_4->isChecked()||ui->radioButton_5->isChecked()){
        QMessageBox:: information(this,"Review",QString("Cancion calificada correctamente"));
    }else{
        QMessageBox:: information(this,"Review",QString("No es posible calificada esta cancion"));
    }

}





void MainWindow::on_add_Button_2_clicked()
{

    CTunes ctunes;
try {
    int codigo = ctunes.getcodigo(0);

    QString codigoString = QString::number(codigo);
    ui->lineEdit_codigo->setText(codigoString);

    QString nombre = ui->lineEdit_nombre->text();
    QString cantante = ui->lineEdit_Artista->text();
    QString generoString = ui->comboBox_genero->currentText();
    Genero::Generos generoEnum;

    // Convertir el QString a std::string
    std::string generoStdString = generoString.toStdString();

    // Convertir el std::string a Genero::Generos
    if (generoStdString == "POP") {
        generoEnum = Genero::POP;
    } else if (generoStdString == "ROCK") {
        generoEnum = Genero::ROCK;
    } else if (generoStdString == "RAP") {
        generoEnum = Genero::RAP;
    } else if (generoStdString == "DANCE") {
        generoEnum = Genero::DANCE;
    } else if (generoStdString == "REGGAE") {
        generoEnum = Genero::REGGAE;
    } else if (generoStdString == "ELECTRONICA") {
        generoEnum = Genero::ELECTRONICA;
    } else if (generoStdString == "RANCHERA") {
        generoEnum = Genero::RANCHERA;
    }

    double precio = ui->lineEdit_precio->text().toDouble();
    QString duracion = ui->lineEdit_duracion->text();

    if (nombre.isEmpty() || cantante.isEmpty() || generoString.isEmpty() || precio == 0 || duracion.isEmpty()) {
        throw std::runtime_error("Por favor, complete todos los campos.");
    }


    ctunes.addSong(nombre.toStdString(), cantante.toStdString(), generoEnum, precio, duracion.toStdString());

    QMessageBox::information(this, "Éxito", "Canción agregada correctamente.");
    ui->lineEdit_nombre->setText("");
    ui->lineEdit_Artista->setText("");
    ui->lineEdit_precio->setText("");
    ui->lineEdit_duracion->setText("");

} catch (std::exception& e) {
    QMessageBox::warning(this, "Error", e.what());
}

}


void MainWindow::on_review_Botton_clicked()
{
    int code = ui->lineEdit_codigo_R->text().toInt();
    int stars = 0;
    if (ui->radioButton_0->isChecked()) {
        stars = 0;
    } else if (ui->radioButton_1->isChecked()) {
        stars = 1;
    } else if (ui->radioButton_2->isChecked()) {
        stars = 2;
    } else if (ui->radioButton_3->isChecked()) {
        stars = 3;
    } else if (ui->radioButton_4->isChecked()) {
        stars = 4;
    } else if (ui->radioButton_5->isChecked()) {
        stars = 5;
    } else {
        QMessageBox::warning(this, "Error", "Por favor, seleccione una calificación.");
        return;
    }

    CTunes ctunes;

    try {
        ctunes.reviewSong(code, stars);
        QMessageBox::information(this, "Éxito", "La canción ha sido calificada correctamente.");
    } catch (InvalidRateException& e) {
        QMessageBox::warning(this, "Error", "Código de canción inválido.");
    }




}


void MainWindow::on_dowload_Button_2_clicked()
{
    try {
    CTunes ctunes;

    int code = ui->lineEdit_code_dowload->text().toInt();
    string  cliente = ui->lineEdit_cliente_dowload->text().toStdString();

    if (cliente.empty()) {
        throw std::runtime_error("Por favor, ingrese el cliente o codigo.");
    }


    string message = ctunes.downloadSong(code, cliente);
    QString clienteQString = QString::fromStdString(message);

    ui->dowload_text->setText(clienteQString);
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }


}

void MainWindow::on_infoSong_Button_clicked()
{
    CTunes ctunes;
    try {
    int code = ui->lineEdit_info_code->text().toInt();

    if (code <= 0) {
        throw std::runtime_error("Por favor, ingrese un código válido.");
    }
    string message = ctunes.infoSong(code);
    QString clienteQString = QString::fromStdString(message);
    ui->textEdit_infoSong->setText(clienteQString);
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }
}


void MainWindow::on_update_SButton_clicked()
{
    try {
    CTunes ctunes;

    QString filename = ui->lineEdit_songs->text();
    if (filename.isEmpty()) {
        throw std::runtime_error("Por favor, ingrese un nombre de archivo válido.");
    }
    string message = ctunes.songs(filename.toStdString());
    ui->TextEdit_song->setPlainText(QString::fromStdString(message));
    } catch (std::exception& e) {
        QMessageBox::warning(this, "Error", e.what());
    }

}

