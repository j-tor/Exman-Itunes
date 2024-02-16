#include "ctunes.h"
#include "InvalidRateException.h"
#include <ctunes.h>
#include <string>
#include <QFile>
#include <QByteArray>
#include <QIODevice>
#include <QDebug>
#include <QDate>
#include <QMessageBox>
#include <mainwindow.h>
#include <QTextStream>





using namespace std;

struct cancion{
    int code;
    QString nombre;
    QString cantante;
    QString genero;
    double precio;
    string duracion;
    int estrellas;
    int reviews;
};

struct descarga
{
    int codedown;
    QString fecha;
    int codesong;
    QString cliente;
    double precio;
};

// Constructor
CTunes::CTunes() {

    QFile codigosFile("codigos.itn");
    QFile songsFile("songs.itn");
    QFile downloadsFile("downloads.itn");
    QFile file("txtFile.txt");



    QDataStream out(&codigosFile);
    QDataStream in(&codigosFile);
    QDataStream insongs(&songsFile);
    QDataStream downloadin(&downloadsFile);

    codigosFile.open(QIODevice::ReadWrite);
    downloadsFile.open(QIODevice::ReadWrite);
    songsFile.open(QIODevice::ReadWrite);
    if(!codigosFile.isOpen()||!downloadsFile.isOpen()||!songsFile.isOpen()){
        exit(0);
    }
    qint64 size = codigosFile.size();
    if(size==0 ){
        int codecancion = 1;
        int codedownload = 1;
        in << codecancion;
        codigosFile.seek(codigosFile.size());
        in << codedownload;
    }

}



int CTunes::getcodigo(long offset) {


   QFile codigosFile("codigos.itn");
    if (!codigosFile.open(QIODevice::ReadWrite)) {
        qDebug() << "Failed to open codigos file.";
        throw std::runtime_error("Failed to open codigos file.");
    }

        QDataStream codigosadd(&codigosFile);
        //codigosFile.seek(offset);
        //int tempcodesong;
        //codigosadd >> tempcodesong;

        /*codigosFile.seek(offset);
        int suma = tempcodesong+1;
        codigosadd << suma;
        QDataStream codigosread(&codigosFile);
        codigosread <<suma;*/

       codigosFile.seek(offset);
        int tempo;
        codigosadd>>tempo;
        codigosFile.seek(offset);
        int mas= tempo+1;
        codigosadd<<mas;

    return tempo++;

}



void CTunes::addSong(string nombre, string cantante, Genero::Generos generoCantante, double precio,string duracion) {

    string genero;
    if (generoCantante == Genero::POP) {
        genero = "Pop";
    } else if (generoCantante == Genero::ROCK) {
        genero = "Rock";
    } else if (generoCantante == Genero::RAP) {
        genero = "Rap";
    } else if (generoCantante == Genero::DANCE) {
        genero = "Dance";
    } else if (generoCantante == Genero::REGGAE) {
        genero = "Raggae";
    } else if (generoCantante == Genero::ELECTRONICA) {
        genero = "Electronica";
    } else if (generoCantante == Genero::RANCHERA) {
        genero = "Ranchera";
    }

    getcodigo(0);
    int nextCode = getcodigo(0);

    QFile songsFile("songs.itn");
    if (!songsFile.open(QIODevice::Append | QIODevice::Text)) {
        // Handle file open failure
        qDebug() << "Failed to open songs file.";
        throw std::runtime_error("Failed to open songs file.");
    }

    struct cancion newSong;
    newSong.code = nextCode;
    newSong.nombre = QString::fromStdString(nombre);
    newSong.cantante = QString::fromStdString(cantante);
    newSong.genero = QString::fromStdString(genero);
    newSong.precio = precio;
    newSong.duracion = duracion;
    newSong.estrellas = 0;
    newSong.reviews = 0;

    if (songsFile.seek(songsFile.size())) {
    QDataStream out(&songsFile);
    out << nextCode;
    out << QString::fromStdString(nombre);
    out << QString::fromStdString(cantante);
    out << QString::fromStdString(genero);
    out << precio;
    out << 0;
    out << 0;

    songsFile.close();
    } else {
        qDebug() << "Failed to seek to the end of the songs file.";
        throw std::runtime_error("Failed to seek to the end of the songs file.");
    }
}

string CTunes::downloadSong(int codeSong, string cliente){

    QFile songsFile("songs.itn");
    QFile downloadsFile("downloads.itn");

    if (!songsFile.open(QIODevice::ReadOnly) || !downloadsFile.open(QIODevice::Append)) {
        return "Failed to open files.";
    }

    QDataStream inSongs(&songsFile);
    QDataStream outDownloads(&downloadsFile);

    bool songFound = false;
    cancion song;

    songsFile.seek(0);

    while (!inSongs.atEnd()) {
        inSongs >> song.code >> song.nombre >> song.cantante >> song.genero >> song.precio >> song.estrellas >> song.reviews;
        if (song.code == codeSong) {
            songFound = true;            
            break;
        }
    }

    if (!songFound){
        return "Invalid code!! Song not found.";
    }

    getcodigo(4);
    int nextDownloadCode = getcodigo(4);
    if (nextDownloadCode == -1) {        
        return "Error getting next download code.";
    }


    descarga newDownload;
    newDownload.codedown = nextDownloadCode;
    newDownload.fecha = QDateTime::currentDateTime().toString();
    newDownload.codesong = codeSong;
    newDownload.cliente = QString::fromStdString(cliente);
    newDownload.precio = song.precio;

    outDownloads << newDownload.codedown << newDownload.fecha << newDownload.codesong << newDownload.cliente << newDownload.precio;

    songsFile.close();
    downloadsFile.close();

    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << song.precio;
    std::string formattedPrice = ss.str();


    return "GRACIAS!! " + cliente + " por descargar " + song.nombre.toStdString() + " (Código de descarga: " + std::to_string(nextDownloadCode) +
           ", Fecha: " + newDownload.fecha.toStdString() + ", Código de canción: " + std::to_string(codeSong) +
           ") a un costo de Lps." + formattedPrice;}




void CTunes::reviewSong(int code, int stars) {
    QFile songsFile("songs.itn");

    if (!songsFile.open(QIODevice::ReadWrite)) {
        throw std::runtime_error("Failed to open songs file for reviewing.");
    }

    QDataStream inSongs(&songsFile);

    bool songFound = false;
    cancion song;
int rate = 0;
    songsFile.seek(0);

    while (!inSongs.atEnd()) {
        inSongs >> song.code >> song.nombre >> song.cantante >> song.genero >> song.precio >> song.estrellas >> song.reviews;
        if (song.code == code) {
            songFound = true;
            break;
        }else{
            throw InvalidRateException(rate);

        }
    }


    if (!songFound) {
        songsFile.close();
        throw InvalidRateException(rate);
    }


    // Check if stars is within the range 0-5
    if (stars < 0 || stars > 5) {
        songsFile.close();
        throw   InvalidRateException(rate);
    }
//QString::fromStdString(song.duracion)
    song.estrellas += stars;
    song.reviews++;

    QByteArray songData;
    QDataStream dataStream(&songData, QIODevice::WriteOnly);
    dataStream << song.code << song.nombre << song.cantante << song.genero << song.precio  << song.estrellas <<  song.reviews;

    songsFile.seek(0);
    while (!inSongs.atEnd()) {
        qint64 pos = songsFile.pos();
        inSongs >> song.code;
        if (song.code == code) {
            songsFile.seek(pos);
            songsFile.write(songData);
            break;
        }
    }

    songsFile.close();
}

string CTunes::infoSong(int codeSong) {

    QFile songsFile("songs.itn");
    QFile downloadsFile("downloads.itn");

    if (!songsFile.open(QIODevice::ReadOnly) || !downloadsFile.open(QIODevice::ReadOnly)) {
        return "Failed to open files.";
    }

    QDataStream inSongs(&songsFile);

    bool songFound = false;
    cancion song;
    songsFile.seek(0);

    while (!inSongs.atEnd()) {
        inSongs >> song.code >> song.nombre >> song.cantante >> song.genero >> song.precio >> song.estrellas >> song.reviews;

        if (song.code == codeSong) {
            songFound = true;
            break;
        }
    }


    if (!songFound) {
        qDebug() << "Song with code" << codeSong << "not found.";
        return "Song not found.";
    }

    QString songDetails;
    songDetails += "Code: " + QString::number(song.code) + "\n";
    songDetails += "Nombre: " + song.nombre + "\n";
    songDetails += "Cantante: " + song.cantante + "\n";
    songDetails += "Genero: " + song.genero + "\n";
    songDetails += "Precio: " + QString::number(song.precio) + "\n";
    songDetails += "Estrellas: " + QString::number(song.estrellas) + "\n";
    songDetails += "Reviews: " + QString::number(song.reviews) + "\n";

    descarga download;
    QDataStream inDownloads(&downloadsFile);

    int downloadCount=0;

    songDetails += "Downloads:\n";
    downloadsFile.seek(0);
    while (!inDownloads.atEnd()) {
        inDownloads >> download.codedown >> download.fecha >> download.codesong >> download.cliente >> download.precio ;

        if (download.codesong == song.code) {
            downloadCount++;
            songDetails += "Código de descarga: " + QString::number(download.codedown) + "\n";
            songDetails += "Fecha: " + download.fecha + "\n";
            songDetails += "Cliente: " + download.cliente + "\n";
            songDetails += "Precio: " + QString::number(download.precio) + "\n";
            break;
        }
    }

    songDetails += "Total de descargas para esta canción: " + QString::number(downloadCount) + "\n";

    songsFile.close();
    downloadsFile.close();

    return songDetails.toStdString();
}



string CTunes::songs(string txtFile) {

    QString direccion= "C:/Users/aleja/Documents/ITunes/songs/"+QString::fromStdString(txtFile)+".txt";
    QFile Filetxt (direccion);
    QTextStream escritura(&Filetxt);
    Filetxt.open(QIODevice::ReadWrite);
    Filetxt.resize(0);

    string data="";
    QFile songsFile("songs.itn");
    if (!songsFile.open(QIODevice::ReadOnly)) {
        return "Failed to open songs file.";
    }
    QDataStream Songs(&songsFile);
    cancion Song;
    songsFile.seek(0);

    while(!songsFile.atEnd()){
        Songs>>Song.code>>Song.nombre>>Song.cantante>>Song.genero>>Song.precio>>Song.estrellas>>Song.reviews;
        escritura <<"CODIGO: "<< Song.code<<" - TITULO: " << Song.nombre <<" - CANTANTE: "<< Song.cantante <<" - PRECIO: "<< Song.precio <<" - RATING: "<< Song.reviews<<".\n" ;
        data+="CODIGO:"+QString::number(Song.code).toStdString()+" - TITULO:" + Song.nombre.toStdString()+" - CANTANTE: "+ Song.cantante.toStdString() +" - PRECIO: "+QString::number(Song.precio).toStdString()  +" - RATING: "+QString::number(Song.reviews).toStdString() +".\n" ;
    }
    songsFile.close();
    return data;
}





