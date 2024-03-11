#ifndef GRAFICA_H_INCLUDED
#define GRAFICA_H_INCLUDED
#include <graphics.h>
#include <winbgim.h>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

int buton_salveaza_schema(int x, int y)
{return x>=0&&x<=250&&y>=0&&y<=55;
}

int buton_incarca_schema(int x, int y)
{return x>=0&&x<=250&&y>=55&&y<=110;
}

int buton_x(int x, int y)
{return x>=0&&x<=250&&y>=165&&y<=220;
}

int buton_lista(int x, int y)
{return x>=0&&x<=250&&y>=110&&y<=165;
}

void Deseneaza_Ecran_Optiuni(int theme)
{char s[100];
int xText, yText;
int inaltimebuton = 83, latimebuton = 600;
  int inaltime = 750, latime = 1200;
if(theme==0)
setbkcolor(BLACK);
else  setbkcolor(COLOR(255, 229, 204));
        cleardevice();
    if(theme==0) setfillstyle(SOLID_FILL, COLOR(121, 15, 122));
    else setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
        bar(300, 103, 900, 186);
        bar(300, 246, 900, 329);
        bar(300, 389, 900, 472);
        //bar(300, 532, 900, 615);
        settextstyle(3, HORIZ_DIR, 3);
        strcpy(s, "LIGHT MODE");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 83 + 20 + (inaltimebuton - textheight(s)) / 2;
        if(theme==0) setbkcolor(COLOR(121, 15, 122));
    else setbkcolor(COLOR(204, 255, 255));
   // setcolor(BLACK);
    outtextxy(xText, yText, s);
    strcpy(s, "DARK MODE");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 226 + 20 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    strcpy(s, "BACK TO MAIN PAGE");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 369 + 20 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

}

void MeniuHelp(int pop_up, int fereastra, int theme)
{ char s[200];
int yt;
pop_up=initwindow(500, 450, "", 400, 100, 0 , 0);
setcurrentwindow(pop_up);
if(theme==0)
setbkcolor(COLOR(102, 0, 51));
else
    setbkcolor(COLOR(204, 255, 255));
cleardevice();
yt=10;
if(theme==0)
setcolor(WHITE);
else
setcolor(BLACK);
settextstyle(3, HORIZ_DIR, 1);
strcpy(s, "Informatii cu privire la utilizarea aplicatiei:");
outtextxy((500-textwidth(s))/2, yt, s);
yt+=20;
strcpy(s, "Pentru a aduaga un bloc nou, faceti click pe acesta in meniul");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "din dreapta.");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "Pentru a realiza o legatura intre 2 blocuri, faceti click pe cerculetul");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "de jos al primului bloc, apoi pe cerculetul de sus al celui");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "de-al doilea bloc.");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "Pentru a muta un bloc, faceti click pe acesta si miscati-l utilizand");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "cursorul mouse-ului, iar pentru a-l aseza in pozitia curenta, faceti");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "din nou click pe bloc.");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "Pentru a sterge un bloc, apasati click dreapta pe acesta.");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "Pentru a edita continutul unui bloc, faceti dublu click pe acesta.");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "Dupa ce ati finalizat schema, puteti rula programul prin apasarea .");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "butonului Run din meniul de sus.");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "Daca aveti erori de compilare, acestea vor fi semnalate prin");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "mesaje de eroare inainte de rularea propriu-zisa a programului,");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "care nu va avea loc decat dupa remedierea erorilor.");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "Pentru a vizualiza codul C++ al algoritmului descris de");
outtextxy(10, yt, s);
yt+=20;
strcpy(s, "schema, apasati butonul Generate Code din meniul de sus.");
outtextxy(10, yt, s);
yt+=40;
settextstyle(3, HORIZ_DIR, 2);
strcpy(s, "Apasati orice tasta pentru a inchide aceasta fereastra: ");
outtextxy(10, yt, s);
yt+=20;
getch();
closegraph(pop_up);
setcurrentwindow(fereastra);


}

int buton_schema_noua(int x, int y)
{return x>=300&&x<=900&&y>=103&&y<=186;

}

int buton_selecteaza_schema(int x, int y)
{return x>=300&&x<=900&&y>=246&&y<=329;
}

int buton_optiuni(int x, int y)
{return x>=300&&x<=900&&y>=389&&y<=472;
}


int buton_exit(int x, int y)
{return x>=300&&x<=900&&y>=532&&y<=610;
}

int buton_back(int x, int y)
{return x>=25&&x<=186&&y>=20&&y<=60;
}
int buton_options(int x, int y, int x1, int y1, int x2, int y2)
{return x>=x1 && x<=x2 && y>=y1 && y<=y2;
}
int Buton_Help(int x, int y, int x1, int y1, int x2, int y2)
{return x>=x1 && x<=x2 && y>=y1 && y<=y2;
}
void FereastraCitire(int fereastra, char s[350], int &valoare, int theme)
{
    int pop_up, functie=0;
    int tasta_apasata, cnt, flag;
    char nul[5], mesaj[350], numar[305], caracter;
    char caractere_ok[100]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890";
    nul[0]=0;
    pop_up=initwindow(300, 150, nul, 400, 300, 0, 0);
    setcurrentwindow(pop_up);
    if(theme==0)
    setbkcolor(COLOR(102, 0, 51));
    else setbkcolor(COLOR(204, 255, 255));
    cleardevice();
    line(0, 75, 300, 75);
    if(theme==0)
    setcolor(WHITE);
    else setcolor(BLACK);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(mesaj, "Introduceti numele variabilei,");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2, mesaj);
    strcpy(mesaj, "apoi apasati tasta Enter");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);
    tasta_apasata=getch();
    s[0]=0;
    cnt=-1;
    while(tasta_apasata!=13)
    {
        caracter=(char) tasta_apasata;
        if(caracter==8)
        {
            if(cnt<0)
            {if(theme==0)
                setcolor(WHITE);
                else
                    setcolor(BLACK);
                settextstyle(3, HORIZ_DIR, 1);
                strcpy(mesaj, "Nu exista niciun caracter de sters!");
                outtextxy((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), mesaj);
                delay(1500);
                if(theme==0)
                setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
                else
                setfillstyle(SOLID_FILL, COLOR(204, 255, 255));

                bar((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), (300-textwidth(mesaj))/2+textwidth(mesaj), 75+(75-2*textheight(mesaj))/2+textheight(s)+textheight(mesaj));
                tasta_apasata=getch();

            }
            else while(caracter==8 && cnt>-1)
                {
                    if(theme==0)
                    setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
                    else
                    setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
                    bar((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, (300-textwidth(s))/2+textwidth(s), 75+(75-2*textheight(s))/2+textheight(s));
                    if(theme==0)
                    setcolor(WHITE);
                    else setcolor(BLACK);
                    s[cnt]=0;
                    outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
                    cnt--;
                    tasta_apasata=getch();
                    caracter=(char) tasta_apasata;
                }
        }
        else  if(strchr(caractere_ok, caracter)==NULL)
        {
            strcpy(mesaj, "Caracter interzis in numele variabilei!");
            if(theme==0)
            setcolor(WHITE);
            else setcolor(BLACK);
            outtextxy((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), mesaj);
            delay(1500);
            if(theme==0)
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            else
                setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
            bar((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), (300-textwidth(mesaj))/2+textwidth(mesaj), 75+(75-2*textheight(mesaj))/2+textheight(s)+textheight(mesaj));
            tasta_apasata=getch();
            // caracter=(char) tasta_apasata;
        }
        else if(cnt==-1 && strchr("0123456789", caracter)!=NULL)
        {
            strcpy(mesaj, "Variabila nu poate incepe cu o cifra!");
            if(theme==0)
            setcolor(WHITE);
            else setcolor(BLACK);
            outtextxy((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), mesaj);
            delay(1500);
            if(theme==0)
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            else  setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
            bar((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), (300-textwidth(mesaj))/2+textwidth(mesaj), 75+(75-2*textheight(mesaj))/2+textheight(s)+textheight(mesaj));
            tasta_apasata=getch();
            caracter=(char) tasta_apasata;
        }
        else
        {if(cnt>4)
        {strcpy(mesaj, "Limita este de 6 caractere!");
        if(theme==0)
            setcolor(WHITE);
            else
            setcolor(BLACK);

            outtextxy((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), mesaj);
            delay(1000);
            if(theme==0)
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            else   setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
            bar((300-textwidth(mesaj))/2, 75+(75-2*textheight(mesaj))/2+textheight(s), (300-textwidth(mesaj))/2+textwidth(mesaj), 75+(75-2*textheight(mesaj))/2+textheight(s)+textheight(mesaj));
            tasta_apasata=getch();
            caracter=(char) tasta_apasata;
        }
        else{s[++cnt]=caracter;
            s[++cnt]=0;
            if(theme==0)
            setcolor(WHITE);
            else
            setcolor(BLACK);
            outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
            cnt--;
            tasta_apasata=getch();}
        }
    }

    closegraph(pop_up);
    setcurrentwindow(fereastra);

}

void Eroare_Compilare(int fereastra, char s[], int theme)
{
    int tasta_apasata, cnt, cif, flag, pop_up;
    char mesaj[350], numar[305], caracter;
    ///char caractere_ok[100]="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_1234567890"
    pop_up=initwindow(375, 125, "", 350, 150, 0, 0);
    setcurrentwindow(pop_up);
    if(theme==0)
    setbkcolor(COLOR(102, 0, 51));
    else
        setbkcolor(COLOR(204, 255, 255));
    cleardevice();
    if(theme==0)
    setcolor(WHITE);
    else  setcolor(BLACK);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(mesaj, s);
    outtextxy((375-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2, mesaj);
    strcpy(mesaj, "Apasati orice tasta pentru a continua");
    outtextxy((375-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);

    tasta_apasata=getch();
    cnt=-1;

        closegraph(pop_up);
        setcurrentwindow(fereastra);

}

void Citire_Val_Variabila(int fereastra, char s[350], char numevar[350], int pop_up, int &newline)
{

    int tasta_apasata, cnt;
    char nul[5], mesaj[350], text[305], caracter;
    nul[0]=0;
    //pop_up=initwindow(300, 150, nul, 400, 300);
    setcurrentwindow(pop_up);
    //setbkcolor(COLOR(102, 0, 51));
    //cleardevice();
    //line(0, 75, 300, 75);
    setcolor(WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(mesaj, "Introduceti valoarea variabilei ");
    strcat(mesaj, numevar);
    outtextxy((375-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+newline, mesaj);
    newline+=20;
    //strcpy(mesaj, "apoi apasati tasta Enter");
    //outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);
    tasta_apasata=getch();
    s[0]=0;
    cnt=-1;
    while(tasta_apasata!=13)
    {
        caracter=(char) tasta_apasata;
        while(caracter==8)
        {
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            bar((375-textwidth(s))/2, 75+(75-2*textheight(s))/2+newline-20, (375-textwidth(s))/2+textwidth(s), 75+(75-2*textheight(s))/2+textheight(s)+newline-20);
            setcolor(WHITE);
            s[cnt]=0;
            outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
            cnt--;
            tasta_apasata=getch();
            caracter=(char) tasta_apasata;
        }
        s[++cnt]=caracter;
        s[++cnt]=0;
        setcolor(WHITE);
        outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2+newline, s);
        newline+=20;
        cnt--;
        tasta_apasata=getch();
    }
    s[++cnt]=0;
    //cout<<s<<endl;
    //closegraph(pop_up);
    //setcurrentwindow(fereastra);

}

void FereastraCalcul(int fereastra, char s[350], int &lun, int theme)
{
    int pop_up;
    int tasta_apasata, cnt;
    char nul[5], mesaj[350], text[305], caracter;
    nul[0]=0;
    pop_up=initwindow(300, 150, nul, 400, 300, 0, 0);
    setcurrentwindow(pop_up);
    if(theme==0)
    setbkcolor(COLOR(102, 0, 51));
    else
    setbkcolor(COLOR(204, 255, 255));
    cleardevice();
    line(0, 75, 300, 75);
    if(theme==0)
    setcolor(WHITE);
    else setcolor(BLACK);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(mesaj, "Introduceti expresia,");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2, mesaj);
    strcpy(mesaj, "apoi apasati tasta Enter");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);
    tasta_apasata=getch();
    s[0]=0;
    cnt=-1;
    while(tasta_apasata!=13)
    {
        caracter=(char) tasta_apasata;
        while(caracter==8)
        {if(theme==0)
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            else
                 setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
            bar((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, (300-textwidth(s))/2+textwidth(s), 75+(75-2*textheight(s))/2+textheight(s));
            if(theme==0) setcolor(WHITE);
            else setcolor(BLACK);
            s[cnt]=0;
            outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
            cnt--;
            tasta_apasata=getch();
            caracter=(char) tasta_apasata;
        }
        s[++cnt]=caracter;
        s[++cnt]=0;
        if(theme==0)
        setcolor(WHITE);
        else setcolor(BLACK);
        outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
        cnt--;
        tasta_apasata=getch();
    }
    s[++cnt]=0;
    if(textwidth(s)-20>lun) lun=textwidth(s)+20;
    else if(textwidth(s)+20<75) lun=75;
    //cout<<s<<endl;
    closegraph(pop_up);
    setcurrentwindow(fereastra);
}



void FereastraDecizie(int fereastra, char s[350], int &lun, int &inal, int theme)
{
    int pop_up;
    int tasta_apasata, cnt;
    char nul[5], mesaj[350], text[305], caracter;
    nul[0]=0;
    pop_up=initwindow(300, 150, nul, 400, 300, 0, 0);
    setcurrentwindow(pop_up);
    if(theme==0)
    setbkcolor(COLOR(102, 0, 51));
    else
        setbkcolor(COLOR(204, 255, 255));
    cleardevice();
    line(0, 75, 300, 75);
    if(theme==0)
    setcolor(WHITE);
    else setcolor(BLACK);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(mesaj, "Introduceti expresia,");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2, mesaj);
    strcpy(mesaj, "apoi apasati tasta Enter");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);
    tasta_apasata=getch();
    s[0]=0;
    cnt=-1;
    while(tasta_apasata!=13)
    {
        caracter=(char) tasta_apasata;
        while(caracter==8)
        {if(theme==0)
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            else
                setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
            bar((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, (300-textwidth(s))/2+textwidth(s), 75+(75-2*textheight(s))/2+textheight(s));
            if(theme==0) setcolor(WHITE);
            else setcolor(BLACK);
            s[cnt]=0;
            outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
            cnt--;
            tasta_apasata=getch();
            caracter=(char) tasta_apasata;
        }
        s[++cnt]=caracter;
        s[++cnt]=0;
        if(theme==0)
        setcolor(WHITE);
        else setcolor(BLACK);
        outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
        cnt--;
        tasta_apasata=getch();
    }
    s[++cnt]=0;
    if(textwidth(s)-20>lun/4) {lun=textwidth(s)+4*lun/3; inal=2*lun/6;}
    else if(textwidth(s)+20<125/2) {lun=125; inal=50;}
    //cout<<s<<endl;
    closegraph(pop_up);
    setcurrentwindow(fereastra);

}


void FereastraAfisare(int fereastra, char s[350], int &lun, int &lun2, int &inal, int theme)
{
    int pop_up;
    int tasta_apasata, cnt;
    char nul[5], mesaj[350], text[305], caracter;
    nul[0]=0;
    pop_up=initwindow(300, 150, nul, 400, 300, 0, 0);
    setcurrentwindow(pop_up);
    if(theme==0)
    setbkcolor(COLOR(102, 0, 51));
    else  setbkcolor(COLOR(204, 255, 255));
    cleardevice();
    line(0, 75, 300, 75);
    if(theme==0)
    setcolor(WHITE);
    else setcolor(BLACK);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(mesaj, "Introduceti expresia,");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2, mesaj);
    strcpy(mesaj, "apoi apasati tasta Enter");
    outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);
    tasta_apasata=getch();
    s[0]=0;
    cnt=-1;
    while(tasta_apasata!=13)
    {
        caracter=(char) tasta_apasata;
        while(caracter==8)
        {if(theme==0)
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            else setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
            bar((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, (300-textwidth(s))/2+textwidth(s), 75+(75-2*textheight(s))/2+textheight(s));
            if(theme==0) setcolor(WHITE);
            else setcolor(BLACK);
            s[cnt]=0;
            outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
            cnt--;
            tasta_apasata=getch();
            caracter=(char) tasta_apasata;
        }
        s[++cnt]=caracter;
        s[++cnt]=0;
        if(theme==0)
        setcolor(WHITE);
        else setcolor(BLACK);
        outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
        cnt--;
        tasta_apasata=getch();
    }
    s[++cnt]=0;
    if(textwidth(s)-10>(lun+lun2)/2) {lun2=lun2+textwidth(s)+10;; lun=lun+textwidth(s)+10;}
    else if(textwidth(s)+20<(lun+lun2)/2) {lun2=45; lun=75;}
    //cout<<s<<endl;
    closegraph(pop_up);
    setcurrentwindow(fereastra);



}

void bloc_operatii(int x_op, int y_op, int lungime, int latime, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc)
{
    char s[350];
    int x_text, y_text;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    bar(x_op, y_op, x_op+lungime, y_op+latime);
    //setcolor(WHITE);
    rectangle(x_op, y_op, x_op+lungime, y_op+latime);
    //floodfill(x_op+1, y_op+1, WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    setbkcolor(COLOR(r, g, b));
    strcpy(s, "calcul");
    x_text=x_op+(lungime-textwidth(s))/2;
    y_text=y_op+(latime-textheight(s))/2;
    setcolor(COLOR(rt, gt, bt));
    outtextxy(x_text, y_text, s);
}

void bloc_start(int x_start, int y_start, int raza_x, int raza_y, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc)
{
    char s[350];
    int x_text, y_text;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    fillellipse(x_start, y_start, raza_x, raza_y);
    setcolor(COLOR(rc, bc, gc));
    ellipse(x_start, y_start, 0, 360, raza_x, raza_y);
    //floodfill(x_start+1, y_start+1, WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    setbkcolor(COLOR(r, g, b));
    strcpy(s, "start");
    x_text=x_start-raza_x+(2*raza_x-textwidth(s))/2;
    y_text=y_start-raza_y+(2*raza_y-textheight(s))/2;
    setcolor(COLOR(rt, gt, bt));
    outtextxy(x_text, y_text, s);
}

void bloc_stop(int x_stop, int y_stop, int raza_x, int raza_y, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc)
{
    char s[350];
    int x_text, y_text;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    fillellipse(x_stop, y_stop, raza_x, raza_y);
    //setcolor(WHITE);
    ellipse(x_stop, y_stop, 0, 360, raza_x, raza_y);
    settextstyle(3, HORIZ_DIR, 1);
    setbkcolor(COLOR(r, g, b));
    strcpy(s, "stop");
    x_text=x_stop-raza_x+(2*raza_x-textwidth(s))/2;
    y_text=y_stop-raza_y+(2*raza_y-textheight(s))/2;
    setcolor(COLOR(rt, gt, bt));
    outtextxy(x_text, y_text, s);
}

void bloc_cin(int x_cin, int y_cin, int baza_mare, int baza_mica, int inaltime, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc)
{
    char s[350];
    int v[10], i;
    int x_text, y_text;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    v[0]=x_cin;
    v[1]=y_cin;
    v[2]=x_cin+baza_mare;
    v[3]=y_cin;
    v[4]=x_cin+(baza_mare-baza_mica)/2+baza_mica;
    v[5]=y_cin+inaltime;
    v[6]=x_cin+(baza_mare-baza_mica)/2;
    v[7]=y_cin+inaltime;
    fillpoly(4, v);
    //setcolor(WHITE);
    line(x_cin, y_cin, x_cin+baza_mare, y_cin);
    line(x_cin+baza_mare, y_cin, x_cin+(baza_mare-baza_mica)/2+baza_mica, y_cin+inaltime);
    line(x_cin+(baza_mare-baza_mica)/2, y_cin+inaltime, x_cin+(baza_mare-baza_mica)/2+baza_mica, y_cin+inaltime);
    line(x_cin, y_cin, x_cin+(baza_mare-baza_mica)/2, y_cin+inaltime);
    strcpy(s, "input");
    //floodfill(x_cin+1, y_cin+1, WHITE);
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setbkcolor(COLOR(r, g, b));
    settextstyle(3, HORIZ_DIR, 1);
    x_text=x_cin+(baza_mare-baza_mica)/2+(baza_mica-textwidth(s))/2;
    y_text=y_cin+(inaltime-textheight(s))/2;
    outtextxy(x_text, y_text, s);

}

void bloc_cout(int x_cout, int y_cout, int baza_mare, int baza_mica, int inaltime, int r, int g, int b, int rt, int gt, int bt,  int rc, int gc, int bc)
{
    int x_text, y_text, v[10];
    char s[305];
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    v[0]=x_cout;
    v[1]=y_cout;
    v[2]=x_cout+baza_mica;
    v[3]=y_cout;
    v[4]=x_cout+(baza_mare-baza_mica)/2+baza_mica;
    v[5]=y_cout+inaltime;
    v[6]=x_cout-(baza_mare-baza_mica)/2;
    v[7]=y_cout+inaltime;
    fillpoly(4, v);
    //setcolor(WHITE);
    line(x_cout, y_cout, x_cout+baza_mica, y_cout);
    line(x_cout+baza_mica, y_cout, x_cout+(baza_mare-baza_mica)/2+baza_mica, y_cout+inaltime);
    line(x_cout-(baza_mare-baza_mica)/2, y_cout+inaltime, x_cout+(baza_mare-baza_mica)/2+baza_mica, y_cout+inaltime);
    line(x_cout, y_cout, x_cout-(baza_mare-baza_mica)/2, y_cout+inaltime);
    //floodfill(x_cout+1, y_cout+1, WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(s, "output");
    x_text=x_cout+(baza_mica-textwidth(s))/2;
    y_text=y_cout+(inaltime-textheight(s))/2;
    outtextxy(x_text, y_text, s);

}

void bloc_if(int x_varf, int y_varf, int lungime, int inaltime, int r, int g, int b, int rt, int gt, int bt,  int rc, int gc, int bc, char text[350])
{
    int x_text, y_text, v[10];
//char s[305];
//int inaltime;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
//inaltime=int(lungime*sqrt(3)/2)/2;
    setcolor(COLOR(rc, gc, bc));
    v[0]=x_varf;
    v[1]=y_varf;
    v[2]=x_varf+lungime/2;
    v[3]=y_varf+inaltime;
    v[4]=x_varf-lungime/2;
    v[5]=y_varf+inaltime;
    fillpoly(3, v);
    /*line(x_varf, y_varf, x_varf+lungime/2, y_varf+inaltime);
    line(x_varf-lungime/2, y_varf+inaltime, x_varf+lungime/2, y_varf+inaltime);
    line(x_varf, y_varf,x_varf-lungime/2, y_varf+inaltime);*/
    //floodfill(x_varf+1, y_varf+10, WHITE);
    settextstyle(3, HORIZ_DIR, 1);
//strcpy(s, "decizie");

    x_text=((x_varf+x_varf-lungime/2)/2);
    x_text=x_text+(lungime/2-textwidth(text))/2;
//cout<<x_text<<' ';
    y_text=y_varf+(inaltime-textheight(text))*3/4;
    outtextxy(x_text, y_text, text);
}

void buton(int x, int y, int lungime, int latime, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc, char s[350])
{
    int x_text, y_text;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    if(lungime<textwidth(s)) lungime=textwidth(s)+lungime/2;
    //if(strcmp(s, "Help")==0)
        //cout<<lungime<<endl;}
    bar(x, y, x+lungime, y+latime);
    //setcolor(WHITE);
    rectangle(x, y, x+lungime, y+latime);
    //floodfill(x+1, y+1, WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    setbkcolor(COLOR(r, g, b));
//strcpy(s, "Help");
    x_text=x+(lungime-textwidth(s))/2;
    y_text=y+(latime-textheight(s))/2;
    setcolor(COLOR(rt, gt, bt));
    outtextxy(x_text, y_text, s);
}

void deseneaza_sageata(int x, int y, int r, int g, int b)
{y-=6;
setcolor(COLOR(r, g, b));
line(x, y, x+5, y-10);
line(x, y, x-5, y-10);
//line(x, y, x, y-20);

}


void Adaug_Bloc_Start(int x_start, int y_start, int raza_x, int raza_y, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc)
{//cout<<"start";
    int i;
    char s[350];
    int x_text, y_text, x_cerc, y_cerc;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
      fillellipse(x_start, y_start, raza_x, raza_y);
    setcolor(COLOR(rc, gc, bc));
    ellipse(x_start, y_start, 0, 360, raza_x, raza_y);
    settextstyle(3, HORIZ_DIR, 1);
    //setbkcolor(COLOR(r, g, b));
    strcpy(s, "start");
    //line(x_start, y_start, 0, 0);
    x_text=x_start-raza_x+(2*raza_x-textwidth(s))/2;
    y_text=y_start-raza_y+(2*raza_y-textheight(s))/2;
    setcolor(COLOR(rt, gt, bt));
    outtextxy(x_text, y_text, s);
    x_cerc=x_start;
    y_cerc=y_start+raza_y;
    //setcolor(0);
    //circle(x_cerc, y_cerc, 6);
    setfillstyle(SOLID_FILL, COLOR(255, 255, 153));
     fillellipse(x_cerc, y_cerc, 6, 6);
    //floodfill(x_cerc+1, y_cerc+1, WHITE);
    //floodfill(x_cerc, y_cerc-5, WHITE);

}

void Adaug_Bloc_Stop(int x_stop, int y_stop, int raza_x, int raza_y, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc)
{
    char s[350];
    int x_text, y_text, x_cerc, y_cerc;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
      fillellipse(x_stop, y_stop, raza_x, raza_y);
    //setcolor(WHITE);
    ellipse(x_stop, y_stop, 0, 360, raza_x, raza_y);
    settextstyle(3, HORIZ_DIR, 1);
    //setbkcolor(COLOR(r, g, b));
    strcpy(s, "stop");
    x_text=x_stop-raza_x+(2*raza_x-textwidth(s))/2;
    y_text=y_stop-raza_y+(2*raza_y-textheight(s))/2;
    setcolor(COLOR(rt, gt, bt));
    outtextxy(x_text, y_text, s);
    x_cerc=x_stop;
    y_cerc=y_stop-raza_y;
   setfillstyle(SOLID_FILL, COLOR(255, 255, 153));
     fillellipse(x_cerc, y_cerc, 6, 6);

}

void Adaug_Bloc_Cin(int x_cin, int y_cin, int baza_mare, int baza_mica, int inaltime, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc, char var[350])
{
    char s[350];
    int v[10];
    int x_text, y_text, x1_cerc, x2_cerc, y1_cerc, y2_cerc;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
     v[0]=x_cin;
    v[1]=y_cin;
    v[2]=x_cin+baza_mare;
    v[3]=y_cin;
    v[4]=x_cin+(baza_mare-baza_mica)/2+baza_mica;
    v[5]=y_cin+inaltime;
    v[6]=x_cin+(baza_mare-baza_mica)/2;
    v[7]=y_cin+inaltime;
    fillpoly(4, v);
    //setcolor(WHITE);
    setcolor(COLOR(rc, gc, bc));
    line(x_cin, y_cin, x_cin+baza_mare, y_cin);
    line(x_cin+baza_mare, y_cin, x_cin+(baza_mare-baza_mica)/2+baza_mica, y_cin+inaltime);
    line(x_cin+(baza_mare-baza_mica)/2, y_cin+inaltime, x_cin+(baza_mare-baza_mica)/2+baza_mica, y_cin+inaltime);
    line(x_cin, y_cin, x_cin+(baza_mare-baza_mica)/2, y_cin+inaltime);
    //if(strcmp(var, "")==0) strcpy(s, "input");
    strcpy(s, var);
    //cout<<s<<endl;
    //floodfill(x_cin+1, y_cin+1, WHITE);
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    //setbkcolor(COLOR(r, g, b));
    settextstyle(3, HORIZ_DIR, 1);
    x_text=x_cin+(baza_mare-baza_mica)/2+(baza_mica-textwidth(s))/2;
    y_text=y_cin+(inaltime-textheight(s))/2;
    //floodfill(x_cin+1, y_cin+1, WHITE);
    outtextxy(x_text, y_text, s);
    setcolor(COLOR(rc, gc, bc));
    //floodfill(x_cin+1, y_cin+1, WHITE);
    x1_cerc=x_cin+baza_mare/2;
    y1_cerc=y_cin;
      x2_cerc=x1_cerc;
    y2_cerc=y1_cerc+inaltime;
      setfillstyle(SOLID_FILL, COLOR(255, 255, 153));
     fillellipse(x1_cerc, y1_cerc, 6, 6);
     fillellipse(x2_cerc, y2_cerc, 6, 6);
}

void Adaug_Bloc_Cout(int x_cout, int y_cout, int baza_mare, int baza_mica, int inaltime, int r, int g, int b, int rt, int gt, int bt,  int rc, int gc, int bc, char text[350])
{
    int x_text, y_text, x1_cerc, x2_cerc, y1_cerc, y2_cerc, v[10];
    char s[305];
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
     v[0]=x_cout;
    v[1]=y_cout;
    v[2]=x_cout+baza_mica;
    v[3]=y_cout;
    v[4]=x_cout+(baza_mare-baza_mica)/2+baza_mica;
    v[5]=y_cout+inaltime;
    v[6]=x_cout-(baza_mare-baza_mica)/2;
    v[7]=y_cout+inaltime;
    fillpoly(4, v);
    //setcolor(WHITE);
    line(x_cout, y_cout, x_cout+baza_mica, y_cout);
    line(x_cout+baza_mica, y_cout, x_cout+(baza_mare-baza_mica)/2+baza_mica, y_cout+inaltime);
    line(x_cout-(baza_mare-baza_mica)/2, y_cout+inaltime, x_cout+(baza_mare-baza_mica)/2+baza_mica, y_cout+inaltime);
    line(x_cout, y_cout, x_cout-(baza_mare-baza_mica)/2, y_cout+inaltime);
    //floodfill(x_cout+1, y_cout+1, WHITE);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(s, text);

    //outtextxy(x_text, y_text, s);


   x_text=x_cout+(baza_mica-textwidth(s))/2;
    y_text=y_cout+(inaltime-textheight(s))/2;
     outtextxy(x_text, y_text, s);


    x1_cerc=x_cout+baza_mica/2;
    y1_cerc=y_cout;
      x2_cerc=x1_cerc;
    y2_cerc=y1_cerc+inaltime;
     setfillstyle(SOLID_FILL, COLOR(255, 255, 153));
     fillellipse(x1_cerc, y1_cerc, 6, 6);
     fillellipse(x2_cerc, y2_cerc, 6, 6);

}

void Adaug_Bloc_If(int x_varf, int y_varf, int lungime, int inaltime, int r, int g, int b, int rt, int gt, int bt,  int rc, int gc, int bc, char text[350])
{
    int x_text, y_text, v[10];
    char s[350];
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    setcolor(COLOR(rc, gc, bc));
    v[0]=x_varf;
    v[1]=y_varf;
    v[2]=x_varf+lungime/2;
    v[3]=y_varf+inaltime;
    v[4]=x_varf-lungime/2;
    v[5]=y_varf+inaltime;
    fillpoly(3, v);
    settextstyle(3, HORIZ_DIR, 1);
    strcpy(s, text);
    x_text=((x_varf+x_varf-lungime/2)/2);
    x_text=x_text+(lungime/2-textwidth(s))/2;
    y_text=y_varf+(inaltime-textheight(s))*3/4;
     outtextxy(x_text, y_text, s);

    setfillstyle(SOLID_FILL, COLOR(255, 255, 153));
    fillellipse(x_varf, y_varf, 6, 6);
     setfillstyle(SOLID_FILL, COLOR(255, 153, 204));
    fillellipse(x_varf+lungime/2, y_varf+inaltime, 6, 6);
     setfillstyle(SOLID_FILL, COLOR(51, 153, 255));
    fillellipse(x_varf-lungime/2, y_varf+inaltime, 6, 6);



}

void Adaug_Bloc_Operatii(int x_op, int y_op, int lungime, int latime, int r, int g, int b, int rt, int gt, int bt, int rc, int gc, int bc, char text[350])
{int multx, multy, divx, divy, ltext;
    char s[350];
    int x_text, y_text;
    setfillstyle(SOLID_FILL, COLOR(r, g, b));
    setcolor(COLOR(rc, gc, bc));
    bar(x_op, y_op, x_op+lungime, y_op+latime);
    //setcolor(WHITE);
    rectangle(x_op, y_op, x_op+lungime, y_op+latime);

    //line(x_op, y_op, 0, 0);
    //setbkcolor(COLOR(r, g, b));
    //if(strcmp(text, "")==0) strcpy(s, "calcul");
    strcpy(s, text);
   // if(textwidth(s)<lungime) settextstyle(3, HORIZ_DIR, 1);

settextstyle(3, HORIZ_DIR, 1);

//setusercharsize(1, 10000000, 20, 32);
//cout<<ltext<<' '<<lungime<<' '<<divx<<' ';



    setcolor(COLOR(rt, gt, bt));

    {
    x_text=x_op+(lungime-textwidth(s))/2;
    y_text=y_op+(latime-textheight(s))/2;
    outtextxy(x_text, y_text, s);
    }
    /*
    else{
    s[4]='.';
    s[5]='.';
    s[6]='.';
    s[7]=0;
     x_text=x_op+(lungime-textwidth(s))/2;
    y_text=y_op+(latime-textheight(s))/2;
    outtextxy(x_text, y_text, s);
    }*/
    setfillstyle(SOLID_FILL, COLOR(255, 255, 153));

    fillellipse(x_op+lungime/2, y_op, 6,6);
    y_op+=latime;
    //setfillstyle(SOLID_FILL, COLOR(255, 255, 153));
    fillellipse(x_op+lungime/2, y_op, 6, 6);



}




int Buton_legatura_start(int x, int y, int x_centru, int y_centru, int r)
{
    if(x >= x_centru-r && x <= x_centru + r && y >= y_centru - r && y <= y_centru + r) return 1;
    return 0;
}

int Buton1_legatura_input(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton2_legatura_input(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton1_legatura_calcul(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton2_legatura_calcul(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton1_legatura_output(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton2_legatura_output(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton1_legatura_if(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton2_legatura_if(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton3_legatura_if(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

int Buton_legatura_stop(int x, int y, int x_centru, int y_centru, int r)
{
    if(x>=x_centru-r && x<=x_centru+r && y>=y_centru-r && y<=y_centru+r) return 1;
    return 0;
}

///start raza_x-50  raza_y-25

int Buton_Apasat_Start(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{
    //setcolor(15);
//delay(30);
//line(x_start+50, y_start+50, 1000, 500);
    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin && !Buton_legatura_start(x, y, x_start+50, y_start+50, 6)) return 1;
    return 0;
}

int Buton_Apasat_Input(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{

    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin && !Buton1_legatura_input(x, y, x_start+75/2, y_start, 6) && !Buton2_legatura_input(x, y, x_start+75/2, y_start+45, 6)) return 1;
    return 0;
}

int Buton_Apasat_Calcul(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{
    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin && !Buton1_legatura_calcul(x, y, x_start+75/2, y_start, 6) && !Buton2_legatura_calcul(x, y, x_start+75/2, y_start+45, 6)) return 1;
    return 0;
}

int Buton_Apasat_Decizie(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{

    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin && !Buton1_legatura_if(x, y, x_start+125/2, y_start, 6) && !Buton2_legatura_if(x, y, x_start, y_start+50, 6) && !Buton3_legatura_if(x, y, x_start+125, y_start+50, 6)) return 1;
    return 0;
}

int Buton_Apasat_Output(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{

    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin && !Buton1_legatura_output(x, y, x_start+75/2, y_start, 6) && !Buton2_legatura_output(x, y, x_start+75/2, y_start+45, 6)) return 1;
    return 0;
}

int Buton_Apasat_Stop(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{
    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin && !Buton_legatura_start(x, y, x_start+50, y_start, 6)) return 1;
    return 0;
}

int Buton_Apasat_Run(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{
    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin) return 1;
    return 0;
}

int Buton_Apasat_GenerareCod(int x, int y, int x_start, int y_start, int x_fin, int y_fin)
{
    if (x >= x_start && x <= x_fin && y >= y_start && y <= y_fin) return 1;
    return 0;
}

int GetZone(int x, int y)
{
    if (Buton_Apasat_Start(x, y, 1075, 75, 1175, 125)) return 1;//Adaug_Bloc_Start(600, 375, 50, 25, 102, 0, 51, 255, 255, 255, 255, 255, 255);
    if (Buton_Apasat_Input(x, y, 1085, 175, 1160, 220)) return 2;//Adaug_Bloc_Cin(600, 375, 75, 45, 45, 102, 0, 51, 0, 0, 0, 255, 255, 255);
    if (Buton_Apasat_Calcul(x, y, 1085, 275, 1360, 320)) return 3;//Adaug_Bloc_Operatii(600, 375, 75, 45, 102, 0, 51, 255, 255, 255, 255, 255, 255);
    if (Buton_Apasat_Decizie(x, y, 1063, 370, 1187, 420)) return 4;//Adaug_Bloc_If(600, 375, 125, 50, 102, 0, 51, 0, 0, 0, 255, 255, 255, "decizie");
    if (Buton_Apasat_Output(x, y, 1085, 490, 1160, 535)) return 5;//Adaug_Bloc_Cout(600, 375, 75, 45, 45, 102, 0, 51, 0, 0, 0, 255, 255, 255);
    if (Buton_Apasat_Stop(x, y, 1075, 600, 1175, 650)) return 6;//Adaug_Bloc_Stop(600, 375, 50, 25, 102, 0, 51, 255, 255, 255, 255, 255, 255);
    if (Buton_Apasat_Run(x, y, 550, 20, 600, 60)) return 7;
    if (Buton_Apasat_GenerareCod(x, y, 700, 20, 831, 60))return 8;
    if(buton_back(x, y)) return 9;
    if(buton_options(x, y, 275, 20, 358, 60)) return 10;
    if(Buton_Help(x, y, 425, 20, 475, 60)) return 11;
}

void deseneaza_linie(int x1, int y1, int x2, int y2, int r, int g, int b)
{
    setcolor(COLOR(r, g, b));
    line(x1,y1,x1,(y1+y2)/2);
    line(x1,(y1+y2)/2,x2,(y1+y2)/2);
    line(x2,(y1+y2)/2,x2,y2);
}

void Deseneaza_Meniu(int theme)
{
    int inaltime = 750, latime = 1200;
    int r1, g1, b1, r2, b2, g2;
    int x1_zona_piese, y1_zona_piese, x2_zona_piese, y2_zona_piese;
    int x1_zona_butoane, y1_zona_butoane, x2_zona_butoane, y2_zona_butoane;
    if(theme==1)
        {setbkcolor(COLOR(255, 229, 204));
        cleardevice();
        }

    x1_zona_piese=1050;
    y1_zona_piese=5;
    x2_zona_piese=1195;
    y2_zona_piese=745;
    r1=32;
    g1=32;
    b1=32;

    line(x1_zona_piese, y1_zona_piese, x2_zona_piese, y2_zona_piese);
    setfillstyle(SOLID_FILL, COLOR(r1, g1, b1));
    bar(x1_zona_piese, y1_zona_piese, x2_zona_piese, y2_zona_piese);


     if(theme==1)
        {setbkcolor(COLOR(255, 229, 204));
        cleardevice();
        }
    if(theme==0)
    {r1=153;
    g1=0;
    b1=176;
    }
    else{
        r1=255;
    g1=229;
    b1=204;
    }


    setfillstyle(SOLID_FILL, COLOR(255, 255, 255));
    bar(x1_zona_piese, 0, latime, y1_zona_piese);
    bar(x2_zona_piese, 0, latime, inaltime);
    bar(x1_zona_piese, y2_zona_piese, latime, inaltime);
    bar(x1_zona_piese-5, 0, x1_zona_piese, inaltime);
   if(theme==0)
    {r1=32;
    g1=32;
    b1=32;
    }
    else{
        r1=255;
    g1=229;
    b1=204;
    }

    setfillstyle(SOLID_FILL, COLOR(r1, g1, b1));
    x1_zona_butoane=0;
    y1_zona_butoane=0;
    x2_zona_butoane=1050;
    y2_zona_butoane=75;
    bar(x1_zona_butoane, y1_zona_butoane, x2_zona_butoane-5, y2_zona_butoane);

    setfillstyle(SOLID_FILL, COLOR(255, 255, 255));
    bar(x1_zona_butoane, y1_zona_butoane, latime, y1_zona_butoane+5);
    bar(x1_zona_butoane, y1_zona_butoane, x1_zona_butoane+5, y2_zona_butoane);
    bar(x1_zona_butoane, y2_zona_butoane-5, x2_zona_butoane, y2_zona_butoane);
//bar(x1_zona_butoane-5, 0, x1_zona_butoane, inaltime);


if(theme==0)
    {r1=102;
    g1=0;
    b1=51;
    }
    else
    {r1=204;
    g1=255;
    b1=255;
    }

    char nume[256];
    strcpy(nume, "decizie");
    int rt, gt, bt, rc, gc, bc;
    if(theme==0)
    {rt=255;
    gt=255;
    bt=255;
    rc=255;
    gc=255;
    bc=255;
    }
    else
    {
rt=0;
    gt=0;
    bt=0;
    rc=0;
    gc=0;
    bc=0;
    }

    bloc_start(1125, 100, 50, 25, r1, g1, b1, rt, gt, bt, rc, gc, bc);
    bloc_cin(1085, 175, 75, 45, 45, r1, g1, b1, rt, gt, bt, rc, gc, bc);
    bloc_operatii(1085, 275, 75, 45, r1, g1, b1, rt, gt, bt, rc, gc, bc);
    bloc_if(1125, 370, 125, 50, r1, g1, b1, rt, gt, bt, rc, gc, bc, nume);
    bloc_cout(1100, 490, 75, 45, 45, r1, g1, b1, rt, gt, bt, rc, gc, bc);
    bloc_stop(1125, 625, 50, 25, r1, g1, b1, rt, gt, bt, rc, gc, bc);

    strcpy(nume, "Back to main page");
    buton(25, 20, 50, 40, r1, g1, b1, rt, gt, bt, rc, gc, bc, nume);
    strcpy(nume, "Options");

    buton(275, 20, 50, 40, r1, g1, b1, rt, gt, bt, rc, gc, bc, nume);
    strcpy(nume, "Help");
    buton(425, 20, 50, 40, r1, g1, b1, rt, gt, bt, rc, gc, bc, nume);

    strcpy(nume, "Run");
    buton(550, 20, 50, 40, r1, g1, b1, rt, gt, bt, rc, gc, bc, nume);

    strcpy(nume, "Generate code");
    buton(700, 20, 50, 40, r1, g1, b1, rt, gt, bt, rc, gc, bc, nume);
}
#endif // GRAFICA_H_INCLUDED
