#ifndef CTUNES_H
#define CTUNES_H


#include <fstream>
#include <fstream>
#include <iostream>
#include <Genero.h>
#include <QFile>

using namespace std;
class CTunes
{
public:
    CTunes();
    int getcodigo(long);
    void addSong(string, string, Genero::Generos ,double,string);
    void reviewSong(int, int);
    string downloadSong(int , string );
    string songs(string);
    string infoSong(int);
    QFile codigosFile;
    QFile downloadsFile;
    QFile songsFile;
    Genero::Generos stringToGenero(const std::string& generoString);




};


#endif // CTUNES_H
