#pragma once
#ifndef _variabili_h
#define _variabili_h
const char* nomedispositivo = "CADOLAB100";  // WiFi Nome

String Progetto = "CADOLAB100";
String NomeProg = "RELE PASSO PASSO WEB";
String Versione = "01";

int conta;

int ingresso1;
int ingresso2;
int ingresso3;
int ingresso4;
int ingresso5;
int ingresso6;
int ingresso7;
int ingresso8;

int sensib[9];
int uscita[9];

int Pubblicazioni = 0;

int Pagina = 0;

char relcmd[] = "qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGH";
String myStringsOn[] =  {"Luce Mansarda", "Luce 2", "Luce 3", "Luce 4", "Luce 5", "Luce 6", "Luce 7", "Luce 8"};
#endif