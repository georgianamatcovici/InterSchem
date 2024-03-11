#include <iostream>
#include "grafica.h"
#include <graphics.h>
#include <unordered_map>
#include <string>
#include "evaluare.h"
#include <string.h>
#include <algorithm>
using namespace std;

int nr_start, nr_stop;
int meniu;
int repr1, repr2;

unordered_map <string, int> M;
string str, str2;
int theme;
struct pozitii
{
    int x, y;
};
//int a[700][1200];
//int raza_x_start=50, raza_y_start=25;


struct bloc
{
    pozitii poz;
    int type; /// 1 = start; 2 = citire; 3 = expresii; 4 = if; 5 = afisare; 6 = stop
    int cod;
    int lungimeb, lungime2b, inaltimeb;
    char instr[203]="";
    char afis[203]="";
    pozitii cerc1, cerc2, cerc3;
    bloc *urm;
    bloc *fals;
    bloc *adev;
};

bloc *start[150];
int numar_arb;
bloc *p;
int ok, pag, fereastra;
int frecv[500], cod_unic;

void Init()
{
    for (int i = 1; i <= numar_arb; i++)
        start[i] = NULL;
}

bloc *stergere[150];
int numar_stergere;
char fisiere[50][50], fisier_curent[50];
int nr_fisiere;
bool declaratie1;

void Predp(bloc *curent, bloc *p)
{
    if (curent != NULL) frecv[curent->cod]++;
    if (frecv[curent->cod] >= 2 || curent == NULL) return;

    if (curent->type != 4 && curent->urm == p)
    {
        stergere[++numar_stergere] = curent;
    }

    if (curent->type == 4 && (curent->adev == p || curent->fals == p))
        stergere[++numar_stergere] = curent;

    if (curent->type != 4 && curent->urm != NULL) Predp(curent->urm, p);
    if (curent->type == 4)
    {
        if (curent->fals != NULL) Predp(curent->fals, p);
        if (curent->adev != NULL) Predp(curent->adev, p);
    }
}

int parcurg_mid[350], numar_parc;

void Parcurgere_Arbore_Delete_FR(bloc *st)
{
    if (st != NULL) frecv[st->cod]++;
    if (st != NULL && frecv[st->cod] == 1) parcurg_mid[st->cod] = ++numar_parc;
    if (st == NULL || frecv[st->cod] == 2) return;
    if (st->type != 4) Parcurgere_Arbore_Delete_FR(st->urm);
    else
    {
        Parcurgere_Arbore_Delete_FR(st->adev);
        Parcurgere_Arbore_Delete_FR(st->fals);
    }
}

void StergeBloc(bloc *p, int ind)
{
    for (int i = 0; i <= cod_unic; i++)
        frecv[i] = 0;
    bloc *c = start[ind];
    Predp(c, p);
    for (int i = 0; i <= cod_unic; i++)
        frecv[i] = 0;

    if(p == start[ind])
    {
        if (p->type != 4)
        {
            if (p->urm == NULL && numar_stergere == 0)
            {
                for (int i = ind; i <= numar_arb; i++)
                    start[i] = start[i + 1];
                numar_arb--;
                delete p;
            }
            else if (p->urm != NULL && numar_stergere == 0)
            {
                start[ind] = p->urm;
                delete p;
            }

            else if (numar_stergere > 0)
            {
                for (int i = 1; i <= numar_stergere; i++)
                {
                    if (stergere[i]->type != 4) stergere[i]->urm = NULL;
                    else if (stergere[i]->type == 4)
                    {
                        if (stergere[i]->adev == p) stergere[i]->adev = NULL;
                        else stergere[i]->fals = NULL;
                    }
                }

                if (p->urm == NULL)
                {
                    for (int i = ind; i <= numar_arb; i++)
                        start[i] = start[i + 1];
                    numar_arb--;
                    delete p;
                }
                else
                {
                    start[ind] = p->urm;
                    delete p;
                }

            }

        }
        else if (p->type == 4)
        {
            if(numar_arb > 0)
            {
                for (int i = 1; i <= numar_stergere; i++)
                {
                    if (stergere[i]->type != 4) stergere[i]->urm = NULL;
                    else if (stergere[i]->type == 4)
                    {
                        if (stergere[i]->adev == p) stergere[i]->adev = NULL;
                        else stergere[i]->fals = NULL;
                    }
                }
            }

            if (p->adev == NULL && p->fals == NULL)
            {
                delete p;
                for (int i = ind; i <= numar_arb; i++)
                    start[i] = start[i + 1];
                numar_arb--;
            }
            else if (p->adev != NULL && p->fals == NULL)
            {
                start[ind] = p->adev;
                delete p;
            }
            else if (p->adev == NULL && p->fals != NULL)
            {
                start[ind] = p->fals;
                delete p;
            }
            else
            {
                start[++numar_arb] = p->adev;
                start[++numar_arb] = p->fals;
                delete p;
                for (int i = ind; i < numar_arb; i++)
                    start[i] = start[i + 1];
                numar_arb--;
            }
        }
        return;
    }

    Parcurgere_Arbore_Delete_FR(start[ind]);

    for (int i = 0; i <= cod_unic; i++)
        frecv[i] = 0;

    for (int i = 1; i <= numar_stergere; i++)
    {
        if (stergere[i]->type != 4) stergere[i]->urm = NULL;
        else if (stergere[i]->type == 4)
        {
            if (stergere[i]->adev == p) stergere[i]->adev = NULL;
            else stergere[i]->fals = NULL;
        }
    }

    numar_stergere = 0;

    if (p->type != 4 && p->urm != NULL && (parcurg_mid[p->cod] < parcurg_mid[p->urm->cod])) start[++numar_arb] = p->urm;
    else if (p->type == 4)
    {
        if (p->adev != NULL && (parcurg_mid[p->cod] < parcurg_mid[p->adev->cod])) start[++numar_arb] = p->adev;
        if (p->fals != NULL && (parcurg_mid[p->cod] < parcurg_mid[p->fals->cod])) start[++numar_arb] = p->fals;
    }

    for (int i = 0; i <= numar_parc; i++)
        parcurg_mid[i] = 0;

    numar_parc = 0;

    delete p;
}
void deseneaza_linie(int x1, int y1, int x2, int y2, int r, int g, int b, bloc *p, bloc *q);

void StergeLegaturi(bloc *st)
{
    if (st == NULL) return;

    if (st->type == 1)
    {
        if(st->urm!=NULL) deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
    }
    if (st->type == 2)
    {
        if(st->urm!=NULL)deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
    }
    if (st->type == 3)
    {
        if(st->urm!=NULL)deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
    }
    if (st->type == 4)
    {
        if(st->adev!=NULL) deseneaza_linie(st->cerc2.x, st->cerc2.y, st->adev->cerc1.x, st->adev->cerc1.y, 0, 0, 0, st, st->adev);
        if(st->fals!=NULL) deseneaza_linie(st->cerc3.x, st->cerc3.y, st->fals->cerc1.x, st->fals->cerc1.y, 0, 0, 0, st, st->fals);
    }
    if(st->type == 5)
    {

        if(st->urm!=NULL) deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
    }
    if(st->type == 6);
}

void AdaugareBloc(int tip)
{
    int i;
    for(i=1; i<=numar_arb; i++)
    {
        StergeLegaturi(start[i]);
        //cout<<"sters"<<endl;
    }
    bloc *p;
    p = new bloc;
    p->type = tip;
    p->poz.x = 600;
    p->poz.y = 375;
    p->cod = cod_unic++;
    if (p->type != 4)
    {
        p->urm = NULL;
        if(p->type==2 || p->type==5)
        {
            p->lungimeb=75;
            p->lungime2b=45;
        }
        else if(p->type==3) p->lungimeb=75;

    }
    else
    {
        p->lungimeb=125;
        p->inaltimeb=50;
        p->fals = NULL;
        p->adev = NULL;
    }
    start[++numar_arb] = p;

}

void CreeazaLegatura(bloc *&p, bloc *&q)
{
    p->urm = q;
}

void CreeazaLegaturaIf(bloc *&p, bloc *&q, int flag)
{
    if (flag == 1) p->adev = q;
    else p->fals = q;
}

int pozitie_bloc(bloc *p)
{
    int i;
    for(i=1; i<=numar_arb; i++)
        if(start[i]==p) return i;
}

bloc *GasireButonLegatura(bloc *p, int x, int y, int &x_centru, int &y_centru, int &tip) /// 1-start, 2-input1, 3-input2, 4-calcul1, 5-calcul2, 6-if1, 7-if2, 8-if3, 9-outpu1
///10-output2, 11-stop
{
    if (p == NULL) return NULL;
    int px, py;
    px = p->poz.x;
    py = p->poz.y;
    //setcolor(15);
    //line(px, py, 500, 500);
    if (p->type == 1 &&  Buton_legatura_start(x, y, px, py+25, 6))
    {
        x_centru=px;
        y_centru=py+25;
        tip=1;
        return p;
    }

    if (p->type == 2 && Buton1_legatura_input(x, y, px+(p->lungimeb)/2, py, 6))
    {
        x_centru=px+(p->lungimeb)/2;
        y_centru=py;
        tip=2;
        return p;
    }


    if (p->type == 2 && Buton2_legatura_input(x, y, px+(p->lungimeb)/2, py+45, 6))
    {
        x_centru=px+(p->lungimeb)/2;
        y_centru=py+45;
        tip=3;
        return p;
    }


    if (p->type == 3 && Buton1_legatura_calcul(x, y, px+(p->lungimeb)/2, py, 6))
    {
        x_centru=px+(p->lungimeb)/2;
        y_centru=py;
        tip=4;
        return p;
    }


    if (p->type == 3 && Buton2_legatura_calcul(x, y, px+(p->lungimeb)/2, py+45, 6))
    {
        x_centru=px+(p->lungimeb)/2;
        y_centru=py+45;
        tip=5;
        return p;
    }

    if (p->type == 4 && Buton1_legatura_if(x, y, px, py, 6))
    {
        x_centru=px;
        y_centru=py;
        tip=6;
        return p;
    }

    if (p->type == 4 && Buton2_legatura_if(x, y, px-(p->lungimeb)/2, py+(p->inaltimeb), 6))
    {
        x_centru=px-(p->lungimeb)/2;
        y_centru=py+p->inaltimeb;
        tip=7;
        return p;
    }

    if (p->type == 4 && Buton3_legatura_if(x, y, px+(p->lungimeb)/2, py+(p->inaltimeb), 6))
    {
        x_centru=px+(p->lungimeb)/2;
        y_centru=py+p->inaltimeb;
        tip=8;
        return p;
    }

    if (p->type == 5 && Buton1_legatura_output(x, y, px + (p->lungime2b)/2, py, 6))
    {
        x_centru=px+(p->lungime2b)/2;
        y_centru=py;
        tip=9;
        return p;
    }

    if (p->type == 5 && Buton2_legatura_output(x, y, px + (p->lungime2b)/2, py+45, 6))
    {
        x_centru=px+(p->lungime2b)/2;
        y_centru=py+45;
        tip=10;
        return p;
    }
    if (p->type == 6 && Buton_legatura_stop(x, y, px, py-25, 6))
    {
        x_centru=px;
        y_centru=py-25;
        tip=11;
        return p;
    }
    /*if (p->type != 4) GasireBlocP(p->urm, x, y);
    else
    {
        GasireBlocP(p->adev, x, y);
        GasireBlocP(p->fals, x, y);
    }*/
    return NULL;
}

int minimx, minimy, maximx, maximy;

int viz[300];

void ParcurgereMinim(bloc *rad, bloc *p, bloc *q, int y1, int y2, int x1, int x2, int flag)
{
//cout<<y1<<' '<<y2<<endl;
    int px, py;
    if(rad!=NULL && !viz[rad->cod])
    {
        viz[rad->cod]=1;
        px=rad->poz.x;
        py=rad->poz.y;
        if((flag && (rad!=p && rad!=q)))
        {
            if(rad->type==1 || rad->type==6)
            {
                if(px-50<minimx && (py+25>=y1 && py-25<=y2 && px+50>=x1 && px-50<=x2)) minimx=px-50;
                if(px+50>maximx && (py+25>=y1 && py-25<=y2 && px+50>=x1 && px-50<=x2)) maximx=px+50;
                if(py-25<minimy && (py+25>=y1 && py-25<=y2 && px+50>=x1 && px-50<=x2)) minimy=py-25;
                if(py+25>maximy && (py+25>=y1 && py-25<=y2 && px+50>=x1 && px-50<=x2)) maximy=py+25;
            }
            else if(rad->type==2 || rad->type==3)
            {
                if(px<minimx && (py+45>=y1 && py<=y2 && px+rad->lungimeb>=x1 && px<=x2)) minimx=px;
                if(px+rad->lungimeb>maximx && (py+45>=y1 && py<=y2 && px+rad->lungimeb>=x1 && px<=x2)) maximx=px+rad->lungimeb;
                if(py<minimy && (py+45>=y1 && py<=y2 && px+rad->lungimeb>=x1 && px<=x2)) minimy=py;
                if(py+45>maximy && (py+45>=y1 && py<=y2 && px+rad->lungimeb>=x1 && px<=x2)) maximy=py+45;

            }
            else if(rad->type==4)
            {
                if(px-rad->lungimeb/2<minimx && (py+rad->inaltimeb>=y1 && py<=y2 && px+rad->lungimeb/2>=x1 && px-rad->lungimeb/2<=x2))
                {
                    minimx=px-rad->lungimeb/2;
                }
                if(px+rad->lungimeb/2>maximx && (py+rad->inaltimeb>=y1 && py<=y2 && px+rad->lungimeb/2>=x1 && px-rad->lungimeb/2<=x2)) maximx=px+rad->lungimeb/2;
                if(py<minimy && (py+rad->inaltimeb>=y1 && py<=y2 && px+rad->lungimeb/2>=x1 && px-rad->lungimeb/2<=x2)) minimy=py;
                if(py+rad->inaltimeb>maximy && (py+rad->inaltimeb>=y1 && py<=y2 && px+rad->lungimeb/2>=x1 && py-rad->lungimeb/2<=x2)) maximy=py+rad->inaltimeb;
            }

            else if(rad->type==5)
            {
                if(px-(rad->lungimeb-rad->lungime2b)/2<minimx && (py+45>=y1 && py<=y2 && px+45>=x1 && px-(rad->lungimeb-rad->lungime2b)/2<=x2 )) minimx=px-(rad->lungimeb-rad->lungime2b)/2;
                if(px+rad->lungimeb-(rad->lungimeb-rad->lungime2b)/2>maximx && (py+45>=y1 && py<=y2 && px+45>=x1 && px-(rad->lungimeb-rad->lungime2b)/2<=x2)) maximx=px+rad->lungimeb-(rad->lungimeb-rad->lungime2b)/2;
                if(py<minimy && (py+45>=y1 && py<=y2 && px+rad->lungime2b>=x1 && px-(rad->lungimeb-rad->lungime2b)/2<=x2 )) minimy=py;
                if(py+45>maximy && (py+45>=y1 && py<=y2 && px+rad->lungime2b>=x1 && px-(rad->lungimeb-rad->lungime2b)/2<=x2 )) maximy=py+45;

            }
        }
        else if(!flag)
        {

            if(rad->type==1 || rad->type==6)
            {
                if(px-50<minimx && (py+25>=y1 && py-25<=y2)) minimx=px-50;
                if(px+50>maximx && (py+25>=y1 && py-25<=y2)) maximx=px+50;
                if(py-25<minimy && (py+25>=y1 && py-25<=y2)) minimy=py-25;
                if(py+25>maximy && (py+25>=y1 && py-25<=y2)) maximy=py+25;
            }
            else if(rad->type==2 || rad->type==3)
            {
                if(px<minimx && (py+45>=y1 && py<=y2)) minimx=px;
                if(px+rad->lungimeb>maximx && (py+45>=y1 && py<=y2)) maximx=px+rad->lungimeb;
                if(py<minimy && (py+45>=y1 && py<=y2)) minimy=py;
                if(py+45>maximy && (py+45>=y1 && py<=y2)) maximy=py+45;

            }
            else if(rad->type==4)
            {
                if(px-rad->lungimeb/2<minimx && (py+rad->inaltimeb>=y1 && py<=y2))
                {
                    minimx=px-rad->lungimeb/2;
                }
                if(px+rad->lungimeb/2>maximx && (py+rad->inaltimeb>=y1 && py<=y2 )) maximx=px+rad->lungimeb/2;
                if(py<minimy && (py+rad->inaltimeb>=y1 && py<=y2)) minimy=py;
                if(py+rad->inaltimeb>maximy && (py+rad->inaltimeb>=y1 && py<=y2)) maximy=py+rad->inaltimeb;
            }

            else if(rad->type==5)
            {
                //rad->lungimeb-(rad->lungimeb-rad->lungime2b)/2
                if(px-(rad->lungimeb-rad->lungime2b)/2<minimx && (py+45>=y1 && py<=y2 )) minimx=px-(rad->lungimeb-rad->lungime2b)/2;
                if(px+rad->lungimeb-(rad->lungimeb-rad->lungime2b)/2>maximx && (py+45>=y1 && py<=y2 )) maximx=px+rad->lungimeb-(rad->lungimeb-rad->lungime2b)/2;
                if(py<minimy && (py+45>=y1 && py<=y2 )) minimy=py;
                if(py+45>maximy && (py+45>=y1 && py<=y2 )) maximy=py+45;

            }
        }

        if(rad->type!=4) ParcurgereMinim(rad->urm, p, q, y1, y2, x1, x2, flag);
        else
        {
            ParcurgereMinim(rad->adev, p, q, y1, y2, x1, x2, flag);
            ParcurgereMinim(rad->fals, p, q, y1, y2, x1, x2, flag);
        }
    }

}

int extreme(int &xmin, int y1, int &xmax, int y2, bloc *p, bloc *q, int &ymin, int &ymax, int x1, int x2, int flag)
{
    int i;
    minimx=1050;
    minimy=700;
    maximx=0;
    maximy=80;
    for(i=0; i<=cod_unic; i++)
        viz[i]=0;
    for(i=1; i<=numar_arb; i++)
    {
        ParcurgereMinim(start[i], p, q, y1, y2, x1, x2, flag);
    }
    for(i=0; i<=cod_unic; i++)
        viz[i]=0;
    xmin=minimx;
    xmax=maximx;
    ymin=minimy;
    ymax=maximy;
//cout<<"da";

}

void deseneaza_linie(int x1, int y1, int x2, int y2, int r, int g, int b, bloc *p, bloc *q)
{
    int xmin=0, ymin=0, xmax=0, ymax=0;
    int vx[350], vy[350], cnt=0;
    int dist1, dist2;
    setcolor(COLOR(r, g, b));
    cnt++;

    if(y1<y2)
    {
        if(x1<x2)extreme(xmin, y1,  xmax, y2, p, q, ymin, ymax, x1, x2, 1);
        else extreme(xmin, y2, xmax, y1, p, q, ymin, ymax, x2, x1, 1);
    }
    else
    {
        if(x1<x2) extreme(xmin, y2,  xmax, y1, p, q, ymin, ymax, x1, x2, 0);
        else extreme(xmin, y2, xmax, y1, p, q, ymin, ymax, x2, x1, 0);
    }
    /*line(x1,y1,x1,(y1+y2)/2);
    line(x1,(y1+y2)/2,x2,(y1+y2)/2);
    line(x2,(y1+y2)/2,x2,y2);*/
    // cout<<xmin<<' '<<xmax;
    if(xmin==1050 && xmax==0 && ymin==700 && ymax==80)
    {
        line(x1,y1,x1,(y1+y2)/2);
        line(x1,(y1+y2)/2,x2,(y1+y2)/2);
        line(x2,(y1+y2)/2,x2,y2);
    }
    else
    {
        if(y1<y2)
        {
            //cout<<"da";
            if(p->type==4)
            {
                if(p->adev!=NULL && p->adev==q)
                {
                    line(x1, y1, x1, y1+10);
                    line(x1, y1+10, xmin-6, y1+10);
                    line(xmin-6, y1+10, xmin-6, y2-10);
                    line(xmin-6, y2-10, x2, y2-10);
                    line(x2, y2-10, x2, y2);

                }
                if(p->fals!=NULL && p->fals==q)
                {
                    line(x1, y1, x1, y1+10);
                    line(xmax+6, y1, xmax+6, ymax+6);
                    line(xmax+6, ymax+6, xmin-6, ymax+6);
                    line(xmin-6, ymax+6, xmin-6, ymin-6);
                    line(xmin-6, ymin-6, x2, y2);
                }
            }
            else
            {
                if(x1<x2)
                {

                    /*dist1=x1-xmin;
                    dist2=xmax-x2;
                    if(dist1<dist2)
                    {line(x1, y1, x1, y1+10);
                    line(x1, y1+10, xmin-6, y1+10);
                    line(xmin-6, y1+10, xmin-6, y2-10);
                    line(xmin-6, y2-10, x2, y2-10);
                    line(x2, y2-10, x2, y2);}*/
                    //else{
                    line(x1, y1, x1, y1+10);
                    line(x1, y1+10, xmin-6, y1+10);
                    line(xmin-6, y1+10, xmin-6, y2-10);
                    line(xmin-6, y2-10, x2, y2-10);
                    line(x2, y2-10, x2, y2);
                    //}


                }
                else
                {

                    dist1=xmax-x1;
                    dist2=x2-xmin;
                    /*if(dist1<dist2)
                    {line(x1, y1, x1, y1+10);
                    line(x1, y1+10, xmax+6, y1+10);
                    line(xmax+6, y1+10, xmax+6, y2-10);
                    line(xmax+6, y2-10, x2, y2-10);
                    line(x2, y2-10, x2, y2);
                    }*/
                    // else{
                    line(x1, y1, x1, y1+10);
                    line(xmax+6, y1, xmax+6, ymax+6);
                    line(xmax+6, ymax+6, xmin-6, ymax+6);
                    line(xmin-6, ymax+6, xmin-6, ymin-6);
                    line(xmin-6, ymin-6, x2, y2);
                    // }
                }
            }
        }
        else
        {

            if(p->type==4)
            {
                if(p->adev!=NULL && p->adev==q)
                {
                    line(x1, y1, x1, ymax+6);
                    line(x1, ymax+6, xmin-6, ymax+6);
                    line(xmin-6, ymax+6, xmin-6, ymin-6);
                    line(xmin-6, ymin-6, x2, ymin-6);
                    line(x2, ymin-6, x2, y2);

                }
                if(p->fals!=NULL && p->fals==q)
                {
                    line(x1, y1, x1, ymax+6);
                    line(x1, ymax+6, xmax+6, ymax+6);
                    line(xmax+6, ymax+6, xmax+6, ymin-6);
                    line(xmax+6, ymin-6, x2, ymin-6);
                    line(x2, ymin-6, x2, y2);
                }

            }
            else
            {
                if(x1<x2)
                {
                    dist1=xmax-x2;
                    dist2=x1-xmin;
                    // if(dist2<dist1)
                    //{
                    // cout<<"da";
                    //cout<<ymin<<' '<<ymax<<endl;
                    line(x1, y1, x1, ymax+6);
                    line(x1, ymax+6, xmax+6, ymax+6);
                    line(xmax+6, ymax+6, xmax+6, ymin-6);
                    line(xmax+6, ymin-6, x2, ymin-6);
                    line(x2, ymin-6, x2, y2);
                    //}
                    //else{

                    /* line(x1, y1, x1, y1+10);
                     line(x1, y1+10, xmin-6, y1+10);
                     line(xmin-6, y1+10, xmin-6, ymin-6);
                     line(xmin-6, ymin-6, x2, ymin-6);
                     line(x2, ymin-6, x2, y2);*/
                    //}
                }
                else
                {
                    dist1=xmax-x1;
                    dist2=x2-xmin;
                    /*if(dist1<dist2)
                    {line(x1, y1, x1, y1+10);
                    line(x1, y1+10, xmax+6, y1+10);
                    line(xmax+6, y1+10, xmax+6, ymin-6);
                    line(xmax+6, ymin-6, x2, ymin-6);
                    line(x2, ymin-6, x2, y2);
                    }*/
                    //else{
                    line(x1, y1, x1, ymax+6);
                    line(x1, ymax+6, xmin-6, ymax+6);
                    line(xmin-6, ymax+6, xmin-6, ymin-6);
                    line(xmin-6, ymin-6, x2, ymin-6);
                    line(x2, ymin-6, x2, y2);
                    //}
                }

            }
        }
    }
    deseneaza_sageata(x2, y2, r, g, b);
}


void Deseneaza_Schema(bloc *st)
{
    if (st == NULL || frecv[st->cod] == 1) return;
    if (st->type == 1)
    {
        frecv[st->cod] = 1;
        if(theme==0)
            Adaug_Bloc_Start(st->poz.x, st->poz.y, 50, 25, 102, 0, 51, 255, 255, 255, 255, 255, 255);
        else Adaug_Bloc_Start(st->poz.x, st->poz.y, 50, 25, 204, 255, 255, 0, 0, 0, 0, 0, 0);
        if(st->urm != NULL && frecv[st->urm->cod] == 0) Deseneaza_Schema(st->urm);
        if(st->urm!=NULL)
        {
            if(theme==0)
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 255, 255, 255, st, st->urm);
            else
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
        }
    }
    if (st->type == 2)
    {
        frecv[st->cod] = 1;
        if(theme==0)
            Adaug_Bloc_Cin(st->poz.x, st->poz.y, st->lungimeb, st->lungime2b, 45, 102, 0, 51, 0, 0, 0, 255, 255, 255, st->afis);
        else
            Adaug_Bloc_Cin(st->poz.x, st->poz.y, st->lungimeb, st->lungime2b, 45, 204, 255, 255, 0, 0, 0, 0, 0, 0, st->afis);

        if(st->urm != NULL && frecv[st->urm->cod] == 0) Deseneaza_Schema(st->urm);
        if(st->urm!=NULL)
        {
            if(theme==0)
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 255, 255, 255, st, st->urm);
            else deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
        }
    }
    if (st->type == 3)
    {
        frecv[st->cod] = 1;
        if(theme==0)
            Adaug_Bloc_Operatii(st->poz.x, st->poz.y, st->lungimeb, 45, 102, 0, 51, 255, 255, 255, 255, 255, 255, st->afis);
        else Adaug_Bloc_Operatii(st->poz.x, st->poz.y, st->lungimeb, 45, 204, 255, 255, 0, 0, 0, 0, 0, 0, st->afis);
        if(st->urm != NULL && frecv[st->urm->cod] == 0) Deseneaza_Schema(st->urm);
        if(st->urm!=NULL)
        {
            if(theme==0)
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 255, 255, 255, st, st->urm);
            else
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
        }
    }
    if (st->type == 4)
    {
        frecv[st->cod] = 1;
        if(theme==0)
            Adaug_Bloc_If(st->poz.x, st->poz.y, st->lungimeb, st->inaltimeb, 102, 0, 51, 0, 0, 0, 255, 255, 255, st->instr);
        else  Adaug_Bloc_If(st->poz.x, st->poz.y, st->lungimeb, st->inaltimeb, 204, 255, 255, 0, 0, 0, 0, 0, 0, st->instr);
        if(st->adev != NULL && frecv[st->adev->cod] == 0)Deseneaza_Schema(st->adev);
        if(st->adev!=NULL)
        {
            if(theme==0)
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->adev->cerc1.x, st->adev->cerc1.y, 255, 255, 255, st, st->adev);
            else
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->adev->cerc1.x, st->adev->cerc1.y, 0, 0, 0, st, st->adev);
        }
        if(st->fals != NULL && frecv[st->fals->cod] == 0)Deseneaza_Schema(st->fals);
        if(st->fals!=NULL)
        {
            if(theme==0)
                deseneaza_linie(st->cerc3.x, st->cerc3.y, st->fals->cerc1.x, st->fals->cerc1.y, 255, 255, 255, st, st->fals);
            else
                deseneaza_linie(st->cerc3.x, st->cerc3.y, st->fals->cerc1.x, st->fals->cerc1.y, 0, 0, 0, st, st->fals);
        }
    }
    if(st->type == 5)
    {
        frecv[st->cod] = 1;
        if(theme==0) Adaug_Bloc_Cout(st->poz.x, st->poz.y, st->lungimeb, st->lungime2b, 45, 102, 0, 51, 0, 0, 0, 255, 255, 255, st->afis);
        else Adaug_Bloc_Cout(st->poz.x, st->poz.y, st->lungimeb, st->lungime2b, 45, 204, 255, 255, 0, 0, 0, 0, 0, 0, st->afis);
        if(st->urm != NULL && frecv[st->urm->cod] == 0) Deseneaza_Schema(st->urm);
        if(st->urm!=NULL)
        {
            if(theme==0)
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 255, 255, 255, st, st->urm);
            else
                deseneaza_linie(st->cerc2.x, st->cerc2.y, st->urm->cerc1.x, st->urm->cerc1.y, 0, 0, 0, st, st->urm);
        }
    }
    if(st->type == 6)
    {
        if(theme==0)
            Adaug_Bloc_Stop(st->poz.x, st->poz.y, 50, 25, 102, 0, 51, 255, 255, 255, 255, 255, 255);
        else Adaug_Bloc_Stop(st->poz.x, st->poz.y, 50, 25, 204, 255, 255, 0, 0, 0, 0, 0, 0);
    }
}

bloc *GasireBlocP(bloc *p, int x, int y)
{
    if (p == NULL || frecv[p->cod] == 1) return NULL;
    int px, py;
    px = p->poz.x;
    py = p->poz.y;

    if (p->type == 1 && Buton_Apasat_Start(x, y, px - 50, py - 25, px + 50, py + 25))
    {
        return p;
    }
    if (p->type == 2 && Buton_Apasat_Input(x, y, px, py, px + p->lungimeb, py + 45))
    {
        return p;
    }
    if (p->type == 3 && Buton_Apasat_Calcul(x, y, px, py, px + p->lungimeb, py + 45))
    {
        return p;
    }
    if (p->type == 4 && Buton_Apasat_Decizie(x, y, px - (p->lungimeb/2), py, px + (p->lungimeb/2), py + p->inaltimeb))
    {
        return p;
    }
    if (p->type == 5 && Buton_Apasat_Output(x, y, px - (p->lungimeb-p->lungime2b)/2, py, px + p->lungimeb, py + 45))
    {
        return p;
    }
    if (p->type == 6 && Buton_Apasat_Stop(x, y, px - 50, py - 25, px + 50, py + 25))
    {
        return p;
    }
    if (p->type != 4)
    {
        frecv[p->cod] = 1;
        return GasireBlocP(p->urm, x, y);
    }
    else if (p->type == 4)
    {
        bloc *tmp;
        bloc *tmp2;
        frecv[p->cod] = 1;
        tmp = GasireBlocP(p->adev, x, y);
        tmp2 = GasireBlocP(p->fals, x, y);
        if (tmp != NULL) return tmp;
        if (tmp2 != NULL) return tmp2;
    }
    return NULL;
}

void parcurgere(bloc *rad, int x, int y, int &x_centru, int &y_centru, int &tip)
{
    if(ok==1)
    {
        if(rad!=NULL && !frecv[rad->cod])
        {
            frecv[rad->cod]=1;
            //cout<<rad->type<<' ';
            p = GasireButonLegatura(rad, x, y, x_centru, y_centru, tip);
            if(p!=NULL)
            {
                ok=0;
            }
            {
                if(rad->type!=4) parcurgere(rad->urm, x, y, x_centru, y_centru, tip);
                else
                {
                    parcurgere(rad->adev, x, y, x_centru, y_centru, tip);
                    parcurgere(rad->fals, x, y, x_centru, y_centru, tip);
                }
            }
        }
    }
}

void CoordonateCercuri(bloc *&p, int xc, int yc, int tip)
{
    if(tip==2 || tip==4 || tip==6 || tip==9 || tip==11)
    {
        p->cerc1.x=xc;
        p->cerc1.y=yc;
    }
    else if(tip==1 || tip==3 || tip==5 || tip==7 || tip==10)
    {
        p->cerc2.x=xc;
        p->cerc2.y=yc;
    }
    else if(tip==8)
    {
        p->cerc3.x=xc;
        p->cerc3.y=yc;
    }
}

bloc *ButonDinSchemaApasat(int x, int y)
{
    bloc *p;
    for (int i = 1; i <= numar_arb; i++)
    {
        p = GasireBlocP(start[i], x, y);
        if (p != NULL)
        {
            return p;
        }
    }
    return NULL;
}


bloc *ButonDinSchemaApasatDubluClick(int x, int y)
{
    bloc *p;
    for (int i = 1; i <= numar_arb; i++)
    {
        p = GasireBlocP(start[i], x, y);
        if (p != NULL && p->type!=1 && p->type!=6)
        {
            return p;
        }
    }
    return NULL;
}



void Deseneaza_Ecran()
{
    nr_start=0;
    Deseneaza_Meniu(theme);
}

bloc *ButonLegatura(int x, int y, int &x_centru, int &y_centru, int &tip)
{
    int xc=0, yc=0;
    for (int i = 1; i <= numar_arb; i++)
    {
        p=NULL;
        ok=1;
        parcurgere(start[i], x, y, xc, yc, tip);
        //p=GasireButonLegatura(start[i], x, y, x_centru, y_centru, tip);
        if (p != NULL)
        {
            repr1=i;
            //cout<<p->type<<' ';
            x_centru=xc;
            y_centru=yc;
            return p;
        }
    }
    return NULL;
}

void Muta_Bloc(bloc *&p, int x, int y)
{
    int difx = x - p->poz.x;
    int dify = y - p->poz.y;

    int dif_cerc_x1 = p->poz.x - p->cerc1.x;
    int dif_cerc_y1 = p->poz.y - p->cerc1.y;

    int dif_cerc_x2 = p->poz.x - p->cerc2.x;
    int dif_cerc_y2 = p->poz.y - p->cerc2.y;

    int dif_cerc_x3 = p->poz.x - p->cerc3.x;
    int dif_cerc_y3 = p->poz.y - p->cerc3.y;

    while(1)
    {
        delay(30);
        int px = mousex();
        int py = mousey();

       int pozx, pozy;
       pozx=px-difx;
       pozy=py-dify;
       if(p->type==1 || p->type==6)
       {if(!(pozx-50>=0 && pozx+50<=1045 && pozy-25>=80 && pozy+25<=750))
       return;
       }
       else if(p->type==2 || p->type==3)
       {if(!(pozx+p->lungimeb<=1045 && pozx>=0 && pozy-45>=80 && pozy+45<=750))
       return;
       }
       else if(p->type==4)
       {if(!(pozx-p->lungimeb/2>=0 && pozx+p->lungimeb/2<=1045 && pozy>=80 && pozy+p->inaltimeb<=750))
       return ;
       }
       else if(p->type==5)
       {
        if(!(pozx-(p->lungimeb-p->lungime2b)/2>=0 && pozx+p->lungime2b+(p->lungimeb-p->lungime2b)/2<=1045 && pozy>=80 && pozy+45<=750))
            return ;
       }

        p->poz.x = pozx;
        p->poz.y = pozy;

        if (p->type != 1 && p->type != 4)
        {
            p->cerc1.x = p->poz.x - dif_cerc_x1;
            p->cerc1.y = p->poz.y - dif_cerc_y1;
        }

        if (p->type != 6 && p->type != 4)
        {
            p->cerc2.x = p->poz.x - dif_cerc_x2;
            p->cerc2.y = p->poz.y - dif_cerc_y2;
        }

        if (p->type == 4)
        {
            p->cerc1.x = p->poz.x; //600, 375, 125, 50, 102, 0, 51, 0, 0, 0, 255, 255, 255,
            p->cerc1.y = p->poz.y;

            p->cerc2.x = p->poz.x - (p->lungimeb/2);
            p->cerc2.y = p->poz.y + p->inaltimeb;

            p->cerc3.x = p->poz.x + (p->lungimeb/2);
            p->cerc3.y = p->poz.y + p->inaltimeb;
        }
        setactivepage(1 - pag);
        setcolor(0);
        setbkcolor(0);
        cleardevice();
        Deseneaza_Meniu(theme);
        for (int i = 1; i <= numar_arb; i++)
        {
            Deseneaza_Schema(start[i]);
        }
        for (int i = 0; i <= cod_unic; i++)
            frecv[i] = 0;
        setvisualpage(1 - pag);
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            //cout << px << " " << py << "\n";
            clearmouseclick(WM_LBUTTONDOWN);
            return;
        }
        pag = 1 - pag;
    }
}


int tip;

void StergeArbore(int poz)
{
    int i;
    if(repr1!=repr2)
    {
        for(i=poz; i<numar_arb; i++)
            start[i]=start[i+1];
        numar_arb--;
    }
}

void afisare(bloc *p)
{
    if (p != NULL)
    {
        // cout << p->type << " ";
        if(p->type != 4) afisare(p->urm);
        else afisare(p->fals);
    }
}

/*void parcurgere_test(bloc *p)
{
    if(p!=NULL)
    {
        cout<<p->type<<' ';
        if(p->type!=4)
        {
            cout<<p->afis<<endl;
            parcurgere_test(p->urm);
        }
        else
        {
            cout<<p->instr<<endl;
            parcurgere_test(p->adev);
            parcurgere_test(p->fals);
        }
    }
}*/

void CreeazaLegaturi(bloc *&p, int x, int y, int tip)
{
    int mouse_x, mouse_y, click=0, x_centru, y_centru, tip_leg;
    repr2=repr1;
    bloc *q;
    while(!click)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            mouse_x=mousex();
            mouse_y=mousey();
            clearmouseclick(WM_LBUTTONDOWN);
            for (int i = 0; i <= cod_unic; i++)
                frecv[i] = 0;
            q=ButonLegatura(mouse_x, mouse_y, x_centru, y_centru, tip_leg);
            for (int i = 0; i <= cod_unic; i++)
                frecv[i] = 0;
            if(q!=NULL)
            {
                CoordonateCercuri(q, x_centru, y_centru, tip_leg);
                if(tip_leg==2 || tip_leg==4 || tip_leg==6 || tip_leg==9 || tip_leg==11)
                {
                    Beep(2000,100);
                    if(tip==7)
                    {
                        CreeazaLegaturaIf(p, q, 1);
                        if(repr1!=repr2) StergeArbore(pozitie_bloc(q));

                    }
                    else if(tip==8)
                    {
                        CreeazaLegaturaIf(p, q, 0);
                        if(repr1!=repr2) StergeArbore(pozitie_bloc(q));
                    }
                    else
                    {
                        CreeazaLegatura(p, q);
                        if(repr1!=repr2) StergeArbore(pozitie_bloc(q));
                    }
                    if(theme==0) deseneaza_linie(x, y, x_centru, y_centru, 255, 255, 255, p, q);
                    else deseneaza_linie(x, y, x_centru, y_centru, 0, 0, 0, p, q);
                    click=1;
                }
            }
        }
    }
}

int Cauta_Arb(bloc *cautat, bloc *curent)
{
    if (curent != NULL) frecv[curent->cod]++;
    if (curent == NULL || frecv[curent->cod] == 2) return 0;
    if (cautat == curent) return 1;
    if(curent->type != 4) return Cauta_Arb(cautat, curent->urm);
    else if(curent->type == 4)
    {
        int stanga, dreapta;
        stanga  = Cauta_Arb(cautat, curent->adev);
        dreapta = Cauta_Arb(cautat, curent->fals);

        if (stanga != 0) return stanga;
        if (dreapta != 0) return dreapta;
    }
    return 0;
}

int Indice_Lista(bloc *p)
{
    bloc *tmp;
    for (int i = 1; i <= numar_arb; i++)
        if (Cauta_Arb(p, start[i]) == 1) return i;
    return 0;
}

int Parsare(char s[])
{
    int val = 0;
    for (int i = 0; s[i] != 0; i++)
        val = val * 10 + s[i] - '0';
    return val;
}

void Strtok_De_Mana(char s[], char cuv[350][350], int &numar_cuvinte)
{

    for (int i = 0; i < 350; i++)
        strcpy(cuv[i], "");

    int i, dist;
    i = 0;
    int limita = strlen(s);
    for (int k = 0; k < limita; )
    {
        if (s[k] == '=')
        {
            dist = 0;
            for (int l = i; l < k; l++)
            {
                if (s[l] != ' ')
                {
                    cuv[numar_cuvinte][dist] = s[l];
                    dist++;
                }
            }
            cuv[numar_cuvinte][dist] = NULL;
            numar_cuvinte++;
            i = k + 1;
            while(s[i] == ' ') i++;
            k = i;
        }
        else k++;
    }
    dist = 0;
    for (int l = i; s[l] != 0; l++)
        if (s[l] != ' ') cuv[numar_cuvinte][dist++] = s[l];
    cuv[numar_cuvinte][dist] = NULL;
}

bool Nu_Este_Operator(char s)/// &&, ||, <=, >=, <, >, !=, ==
{
    if (s == '&' || s == '|' || s == '<' || s == '>' || s == '!' || s == '=') return 0;
    return 1;
}

bool Operator_Cond(char s)
{
    if (s == '&' || s == '|') return 1;
    return 0;
}

void ConvertChar(int val, char s[])
{
    int n = val, nr_cif = 0;
    int flag=0;
    if (val == 0) s[0] = 0;

    if(n < 0)
    {
        n=-n;
        val=-val;
        flag=1;
    }
    if (n == 0)
    {
        nr_cif = 1;
        s[0] = '0';
    }
    while (n > 0)
    {
        nr_cif++;
        n /= 10;
    }
    if(flag==1) nr_cif++;
    s[nr_cif] = 0;
    while (val > 0)
    {
        s[nr_cif - 1] = (val % 10) + '0';
        val /= 10;
        nr_cif--;
    }
    if(flag==1) s[0]='-';

}

int Evaluare_If(char s[])
{
    bool inca = false;
    int i, dist;
    char cond[350] = "", cond_fin[350] = "", cond_fin_nr, proces = -1;
    char val_char[305];

    int m = strlen(s);
    if (s[0] != '(')
    {
        for (int i = m; i > 0; i--)
            s[i] = s[i - 1];
        s[0] = '(';
        s[m + 1] = ')';
        s[m + 2] = 0;
    }

    stack<int> st;
    for (int j = 0; s[j] != 0; )
    {
        if (s[j] == '(')
        {
            cond_fin[cond_fin_nr++] = '(';
            st.push(j);
            j++;
        }
        else if (s[j] == ')')/// ((a+32<b+12)||(a+21<213))    (a +32 < 14)
        {
            i = st.top();
            st.pop();
            if (i > proces)
            {
                //cout << i << "\n";
                dist = 0;
                strcpy(cond, "");
                int k;
                //cout << i << "\n";
                for (k = i + 1; Nu_Este_Operator(s[k]) && s[k] != ')'; k++)
                {
                    if (s[k] != ' ' && Nu_Este_Operator(s[k]) && s[k] != '(' && s[k] != ')')
                    {
                        cond[dist] = s[k];
                        dist++;
                    }
                }
                cond[dist] = 0;
                int er;
                int valoarea = Eval_Expr(cond, M, 0, er);
                //cout<<endl<<valoarea<<endl;

                ConvertChar(valoarea, val_char);
                strcat(cond_fin, val_char);



                cond_fin_nr = strlen(cond_fin);
                cond_fin[cond_fin_nr++] = s[k++];
                if (s[k] == '&' || s[k] == '|' || s[k] == '=') cond_fin[cond_fin_nr++] = s[k++];

                strcpy(cond, "");
                dist = 0;
                for (; s[k] != ')'; k++)
                {
                    if (s[k] != ' ')
                    {
                        cond[dist] = s[k];
                        dist++;
                    }
                }
                cond[dist] = 0;
                //cout << cond << "\n";
                //cout << "\n";

                valoarea = Eval_Expr(cond, M, 0, er);

                ConvertChar(valoarea, val_char);
                strcat(cond_fin, val_char);

                cond_fin_nr = strlen(cond_fin);
                cond_fin[cond_fin_nr] = ')';
                cond_fin_nr++;
                cond_fin[cond_fin_nr] = 0;
            }
            j++;
        }
        else if (Operator_Cond(s[j]))
        {
            inca = true;
            //cout << "intra?\n";
            cond_fin[cond_fin_nr++] = s[j];
            proces = j;
            j++;
        }
        else j++;
    }
    int kys = strlen(cond_fin);
    if(inca == true) cond_fin[kys] = ')';
    cond_fin[kys + 1] = 0;
    ConversiePostfixBool(cond_fin);
    return Valoare_Adevar_Expresie(cond_fin);

}
int cnt_endl;
int pop_up_rulare;
int error;

int ajuns_stop, er;
void ParcurgereErori(bloc *st)
{
    char s[250];
    if(st!=NULL && st->type==6)
        ajuns_stop=1;
    else if(st==NULL && ajuns_stop==0)
    {
        error=1;
        Eroare_Compilare(fereastra, "Bloc stop neintrodus!", theme);
    }
    else if(st!=NULL && !error && !viz[st->cod])
    {
        viz[st->cod]=1;
        if(st->type==1)
        {
            /*cout<<"da";*/ ParcurgereErori(st->urm);
        }
        else if(st->type==2)

        {
            if(strcmp(st->afis, "")==0)
            {
                error=1;
                Eroare_Compilare(fereastra, "Nu ati introdus numele unei variabile!", theme);
            }
            else
            {
                if(strcmp(st->afis, "sin")==0 || strcmp(st->afis, "cos")==0 || strcmp(st->afis, "abs")==0 || strcmp(st->afis, "tan")==0 || strcmp(st->afis, "log")==0 || strcmp(st->afis, "sqrt")==0)
                {
                    strcpy(s, "Variabila ");
                    strcat(s, st->afis);
                    strcat(s, " denumeste o functie predefinita!");
                    error=1;
                    Eroare_Compilare(fereastra, s, theme);
                }
            }
            ParcurgereErori(st->urm);
        }
        else if(st->type==3)
        {
            if(strcmp(st->afis, "")==0)
            {
                error=1;
                Eroare_Compilare(fereastra, "Nu ati introdus expresia intr-un bloc de calcul!", theme);
            }
            else if(!ParantezareCorecta(st->afis))
            {
                error=1;
                strcpy(s, "Expresia ");
                strcat(s, st->afis);
                strcat(s, " este incorecta!");
                Eroare_Compilare(fereastra, s, theme);
            }
            else
            {
                er=0;
                strcpy(s, st->afis);
                Eval_Expr(s, M, 1, er);
                if(er==1)
                {
                    error=1;
                    strcpy(s, "Expresia ");
                    strcat(s, st->afis);
                    strcat(s, " este incorecta!");
                    Eroare_Compilare(fereastra, s, theme);
                }

            }
            ParcurgereErori(st->urm);
        }
        else if(st->type==4)
        {
            if(strcmp(st->instr, "")==0)
            {
                error=1;
                Eroare_Compilare(fereastra, "Nu ati introdus expresia intr-un bloc de decizie!", theme);
            }
            else if(!ParantezareCorecta(st->instr))
            {
                error=1;
                strcpy(s, "Expresia ");
                strcat(s, st->instr);
                strcat(s, " este incorecta!");
                Eroare_Compilare(fereastra, s, theme);
            }
            /* if(st->adev!=NULL && !error)*/ ParcurgereErori(st->adev);
            ajuns_stop=0;
            /*if(st->fals!=NULL && !error)*/ ParcurgereErori(st->fals);
            ajuns_stop=0;
        }
        else if(st->type==5)
        {
            if(strcmp(st->afis, "")==0)
            {
                error=1;
                Eroare_Compilare(fereastra, "Nu ati introdus expresia intr-un bloc de afisare!", theme);
            }
            else if(!ParantezareCorecta(st->afis))
            {
                error=1;
                strcpy(s, "Expresia ");
                strcat(s, st->afis);
                strcat(s, " este incorecta!");
                Eroare_Compilare(fereastra, s, theme);
            }
            else
            {
                er=0;
                strcpy(s, st->afis);
                Eval_Expr(s, M, 1, er);
                //cout<<"aici "<<er;
                if(er==1)
                {
                    error=1;
                    strcpy(s, "Expresia ");
                    strcat(s, st->afis);
                    strcat(s, " este incorecta!");
                    Eroare_Compilare(fereastra, s, theme);
                }
            }
            ParcurgereErori(st->urm);
        }


    }

}

void DetecteazaErori()
{
    if (numar_arb > 1 || start[1]->type != 1 || numar_arb==0 || (nr_start==1 && cod_unic==1)/*||(nr_stop==0)*/)
    {
        error=1;
        //cout << start[numar_arb]->type << "\n";
        Eroare_Compilare(fereastra, "Schema nefinalizata!", theme);
        return;
    }
    int i;
    for(i=0; i<=cod_unic; i++)
        viz[i]=0;
    ajuns_stop=0;
    error=0;
    ParcurgereErori(start[1]);
    for(i=0; i<=cod_unic; i++)
        viz[i]=0;
}

void Ruleaza_Cod_Cu_Arbore()/// 1 = start; 2 = citire; 3 = expresii; 4 = if; 5 = afisare; 6 = stop
{
    char mesaj[350], s[350];
    int tasta_apasata;
    char caracter;


    int tasta;
    error=0;
    DetecteazaErori();
    if(!error)
    {
        pop_up_rulare=0;
        cnt_endl=0;
        pop_up_rulare=initwindow(375, 275, "", 350, 150, 0, 0);
        setcurrentwindow(pop_up_rulare);
        if(theme==0)
            setbkcolor(COLOR(102, 0, 51));
        else
            setbkcolor(COLOR(204, 255, 255));
        cleardevice();
        bloc *p = start[1];
        while(p->type != 6)
        {
            if(p->type==1)
            {
                cnt_endl=0;
                if(theme==0)
                    setcolor(WHITE);
                else
                    setcolor(BLACK);
                settextstyle(3, HORIZ_DIR, 1);
                strcpy(mesaj, "Inceput program");
                outtextxy(10, (15-textheight(mesaj)/2)+cnt_endl, mesaj);
                cnt_endl+=20;
            }
            if (p->type == 2)
            {
                int flag=0;
                s[0] = 0;
                //Citire_Val_Variabila(fereastra, s, p->afis, pop_up_rulare, cnt_endl);
                //setcolor(WHITE);
                settextstyle(3, HORIZ_DIR, 1);
                strcpy(mesaj, "Introduceti valoarea variabilei ");
                strcat(mesaj, p->afis);
                strcat(mesaj, ",");
                outtextxy(10, (15-textheight(mesaj)/2)+cnt_endl, mesaj);
                strcpy(mesaj, "apoi apasati Enter");
                strcat(mesaj, ":");
                outtextxy(10, (15-textheight(mesaj)/2)+cnt_endl+20, mesaj);
                //cnt_endl+=40;
                tasta_apasata=getch();
                s[0]=0;
                cnt=-1;
                while(tasta_apasata!=13)
                {
                    caracter=(char) tasta_apasata;
                    while(caracter==8)
                    {
                        if(theme==0)
                            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
                        else  setfillstyle(SOLID_FILL, COLOR(204, 255, 255));
                        bar(textwidth(mesaj)+20, (15-textheight(s)/2)+cnt_endl+20, textwidth(mesaj)+20+textwidth(s), (15-textheight(s)/2)+cnt_endl+20+textheight(s));

                        if(theme==0)
                            setcolor(WHITE);
                        else setcolor(BLACK);
                        s[cnt]=0;
                        outtextxy(textwidth(mesaj)+20, (15-textheight(s)/2)+cnt_endl+20, s);
                        cnt--;
                        tasta_apasata=getch();
                        caracter=(char) tasta_apasata;
                    }
                    if(caracter=='-' && flag==0)
                    {
                        flag=1;
                        s[++cnt]=caracter;
                        s[++cnt]=0;
                        if(theme==0)
                            setcolor(WHITE);
                        else
                            setcolor(BLACK);
                        outtextxy(textwidth(mesaj)+20, (15-textheight(s)/2)+cnt_endl+20, s);
                        cnt-=2;
                    }
                    else //if(caracter!='-')
                    {
                        s[++cnt]=caracter;
                        s[++cnt]=0;
                        if(theme==0)
                            setcolor(WHITE);
                        else
                            setcolor(BLACK);

                        outtextxy(textwidth(mesaj)+20, (15-textheight(s)/2)+cnt_endl+20, s);
                        cnt--;
                        tasta_apasata=getch();
                    }

                }
                s[++cnt]=0;
                //closegraph(pop_up_rulare);
                if(flag) strcpy(s, s+1);
                cnt_endl+=40;
                int valoarea = Parsare(s);
                if(flag) valoarea = -valoarea;
                //cout<<s<<endl;
                string numele;
                numele = p->afis;
                M[numele] = valoarea;
                p = p->urm;

            }
            else if (p->type == 3)
            {
                char cuvinte[350][350];
                char cond[350];
                int cnt = 0;
                strcpy(cond, p->afis);
                Strtok_De_Mana(cond, cuvinte, cnt);
                int er;
                int val = Eval_Expr(cuvinte[cnt], M, 0, er);
                ///cout << val << "\n";
                for (int i = 0; i < cnt; i++)
                {
                    string numele;
                    numele = cuvinte[i];
                    M[numele] = val;
                }
                p = p->urm;
            }
            else if (p->type == 4)
            { cout<<"da";
                /// ((a > b) && (c <= d))
                int flag = Evaluare_If(p->instr);
                //cout << flag << " <-flag\n";
                if (flag == 1) p = p->adev;
                else p = p->fals;
            }
            else if (p->type == 5)
            {
                //cout<<"da"<<endl;
                if (p->afis[0] == '"')
                {
                    char s[350];
                    int k=-1;
                    int n = strlen(p->afis);
                    for (int it = 0; it < n; it++)
                        if (it != 0 && it != (n - 1)) s[++k]=p->afis[it];
                    s[++k]='\0';
                    settextstyle(3, HORIZ_DIR, 1);
                    if(theme==0)
                        setcolor(WHITE);
                    else    setcolor(BLACK);
                    outtextxy(15, (15-textheight(s)/2)+cnt_endl, s);
                    cnt_endl+=20;
                }
                else
                {
                    bool flag = 0;
                    int rez, k;
                    char s[350];

                    char temp[350];
                    strcpy(temp, p->afis);
                    //cout << Eval_Expr(temp, M) << "\n";
                    int er;
                    rez = Eval_Expr(temp, M, 0, er);
                    int n = numar_cifre(rez);
                    k=n-1;
                    if (rez < 0)
                    {
                        rez = -rez;
                        k++;
                        flag = 1;
                    }
                    if (rez == 0)
                    {
                        s[k]=char(rez%10+'0');
                        rez/=10;
                        k--;
                    }
                    while(rez)
                    {
                        s[k]=char(rez%10+'0');
                        rez/=10;
                        k--;
                    }
                    if (flag == 1)
                    {
                        n++;
                        s[0] = '-';
                    }
                    s[n]=0;
                    settextstyle(3, HORIZ_DIR, 1);
                    if(theme==0)
                        setcolor(WHITE);
                    else
                        setcolor(BLACK);
                    outtextxy(15, (15-textheight(s)/2)+cnt_endl, s);
                    cnt_endl+=20;
                }
                p = p->urm;
            }
            else p = p->urm;
        }
        strcpy(s, "Sfarsit program");
        settextstyle(3, HORIZ_DIR, 1);
        if(theme==0)
            setcolor(WHITE);
        else
            setcolor(BLACK);
        outtextxy(10, (15-textheight(s)/2)+cnt_endl, s);
        strcpy(s, "Apasati orice tasta");
        outtextxy(10, (15-textheight(s)/2)+cnt_endl+20, s);
        tasta=getch();
        closegraph(pop_up_rulare);
        setcurrentwindow(fereastra);
        M.clear();
    }
}
/// ((a + 32 < b + 12) || a + 21)

void Parcurge_Arb_Pt_ConvCod(bloc *p)
{
    if (p != NULL) frecv[p->cod]++;
    if (p == NULL || frecv[p->cod] == 2) return;
    if (p->type == 2)
    {
        char cond[350];
        strcpy(cond, p->afis);
        string c;
        c = cond;
        M[c] = -1e9;
        Parcurge_Arb_Pt_ConvCod(p->urm);
    }
    if (p->type == 3)
    {
        char cuv[350][350];
        char cond[350];
        int nr_cuv = 0;
        strcpy(cond, p->afis);
        Strtok_De_Mana(cond, cuv, nr_cuv);
        for (int i = 0; i < nr_cuv; i++)
        {
            string c;
            c = cuv[i];
            M[c] = -1e9;
        }
        Parcurge_Arb_Pt_ConvCod(p->urm);
    }
    else if (p->type == 4)
    {
        Parcurge_Arb_Pt_ConvCod(p->fals);
        Parcurge_Arb_Pt_ConvCod(p->adev);
    }
    else Parcurge_Arb_Pt_ConvCod(p->urm);
}

int pop_up_cod, cnt_endl_cod, x_al;

int seteaza[350];

void Set_Loops(bloc *p)
{
    if (p != NULL) frecv[p->cod]++;
    if (p == NULL || frecv[p->cod] >= 3) return;
    if (frecv[p->cod] == 2)
    {
        seteaza[p->cod] = 1;
        return;
    }
    if (p->type != 4) Set_Loops(p->urm);
    else if (p->type == 4)
    {
        Set_Loops(p->adev);
        Set_Loops(p->fals);
    }
}
void ConvertRec(bloc *p, int nr_al)
{
    char s[350];
    if (p != NULL) frecv[p->cod]++;
    if (p == NULL || p->type == 6 || frecv[p->cod] >= 2) return;
    for (int i = 1; i < nr_al; i++)
        x_al+=5;
    if (p->type == 1) ConvertRec(p->urm, 1);
    if (p->type == 2)
    {
        if (seteaza[p->cod] == 1)
        {
            settextstyle(3, HORIZ_DIR, 1);
            setcolor(WHITE);
            outtextxy(10, cnt_endl_cod, "do");
            cnt_endl_cod+=20;
            outtextxy(10, cnt_endl_cod, "{");
            cnt_endl_cod+=20;
            //cout << "cin << " << p->afis << ";\n";
            cnt_endl_cod+=20;
        }
        settextstyle(3, HORIZ_DIR, 1);
        setcolor(WHITE);
        strcpy(s, "cin>> ");
        strcat(s, p->afis);
        strcat(s, ";");
        //cout << "cin << " << p->afis << ";\n";
        outtextxy(x_al, cnt_endl_cod, s);
        cnt_endl_cod+=20;
        ConvertRec(p->urm, nr_al);
    }
    else if (p->type == 3)
    {
        if (seteaza[p->cod] == 1)
        {
            settextstyle(3, HORIZ_DIR, 1);
            setcolor(WHITE);
            outtextxy(10, cnt_endl_cod, "do");
            cnt_endl_cod+=20;
            outtextxy(10, cnt_endl_cod, "{");
            cnt_endl_cod+=20;
            //cout << "cin << " << p->afis << ";\n";
            cnt_endl_cod+=20;
        }
        strcpy(s, p->afis);
        strcat(s, ";");
        outtextxy(x_al, cnt_endl_cod, s);
        cnt_endl_cod+=20;
        ConvertRec(p->urm, nr_al);
    }
    else if (p->type == 4)
    {
        char s[350];
        strcpy(s, p->instr);
        int m = strlen(s);
        if (s[0] != '(')
        {
            for (int i = m; i > 0; i--)
                s[i] = s[i - 1];
            s[0] = '(';
            s[m + 1] = ')';
            s[m + 2] = 0;
            strcpy(p->instr, s);
        }

        if (seteaza[p->cod] == 1)
        {
            //cout << "if" << p->instr << "\n";
            strcpy(s, "while");
            strcat(s, p->instr);
            outtextxy(x_al-4, cnt_endl_cod, s);
            cnt_endl_cod+=20;
            //for (int i = 1; i <= nr_al; i++)
            //  cout << "    ";
            strcpy(s, "{");
            outtextxy(x_al, cnt_endl_cod, s);
            cnt_endl_cod+=20;
            int x1=x_al;
            //cout << "{\n";
            x_al+=10;
            ConvertRec(p->adev, nr_al);
            x_al-=10;
            //for (int i = 1; i <= nr_al; i++)
            // cout << "    ";
            strcpy(s, "}");
            outtextxy(x1, cnt_endl_cod, s);
            cnt_endl_cod+=20;
            //cout << "}\n";
            ConvertRec(p->fals, nr_al);
        }
        else
        {
            /**if (frecv[p->adev->cod] == 1)
            {
                //cout << "if" << p->instr << "\n";
                outtextxy(x_al-4, cnt_endl_cod, "}");
                cnt_endl_cod += 20;
                strcpy(s, "while");
                strcat(s, p->instr);
                outtextxy(x_al-4, cnt_endl_cod, s);
                cnt_endl_cod+=20;
                //for (int i = 1; i <= nr_al; i++)
                //  cout << "    ";
                int x1=x_al;
                //cout << "{\n";
                x_al+=10;
                ConvertRec(p->fals, nr_al);
                x_al-=10;
                //for (int i = 1; i <= nr_al; i++)
                // cout << "    ";
                //cout << "}\n";
            }

            else if (frecv[p->fals->cod] == 1)
            {
                //cout << "if" << p->instr << "\n";
                outtextxy(x_al-4, cnt_endl_cod, "}");
                cnt_endl_cod += 20;
                strcpy(s, "while");
                strcat(s, p->instr);
                outtextxy(x_al-4, cnt_endl_cod, s);
                cnt_endl_cod+=20;
                //for (int i = 1; i <= nr_al; i++)
                //  cout << "    ";
                int x1=x_al;
                //cout << "{\n";
                x_al+=10;
                ConvertRec(p->adev, nr_al);
                x_al-=10;
                //for (int i = 1; i <= nr_al; i++)
                // cout << "    ";
                //cout << "}\n";
            }
            else
            {*/
            //cout << "if" << p->instr << "\n";
            strcpy(s, "if");
            strcat(s, p->instr);
            outtextxy(x_al, cnt_endl_cod, s);
            cnt_endl_cod+=20;
            //for (int i = 1; i <= nr_al; i++)
            //  cout << "    ";
            strcpy(s, "{");
            outtextxy(x_al, cnt_endl_cod, s);
            cnt_endl_cod+=20;
            int x1=x_al;
            //cout << "{\n";
            x_al+=10;
            ConvertRec(p->adev, nr_al);
            x_al-=10;
            //for (int i = 1; i <= nr_al; i++)
            // cout << "    ";
            strcpy(s, "}");
            outtextxy(x1, cnt_endl_cod, s);
            cnt_endl_cod+=20;
            //cout << "}\n";
            if (p->fals != NULL)
            {
                //for (int i = 1; i <= nr_al; i++)
                // cout << "    ";
                strcpy(s, "else");
                outtextxy(x1, cnt_endl_cod, s);
                cnt_endl_cod+=20;
                //cout << "else\n";
                //for (int i = 1; i <= nr_al; i++)
                //cout << "    ";
                strcpy(s, "{");
                int x1=x_al;
                outtextxy(x_al, cnt_endl_cod, s);
                cnt_endl_cod+=20;
                //cout << "{\n";
                x_al+=10;
                ConvertRec(p->fals, nr_al);
                x_al-=10;
                // for (int i = 1; i <= nr_al; i++)
                // cout << "    ";
                // cout << "}\n";
                strcpy(s, "}");
                outtextxy(x1, cnt_endl_cod, s);
                cnt_endl_cod+=20;
            }
            //}
        }
    }
    else if (p->type == 5)
    {
        if (seteaza[p->cod] == 1)
        {
            settextstyle(3, HORIZ_DIR, 1);
            setcolor(WHITE);
            outtextxy(10, cnt_endl_cod, "do");
            cnt_endl_cod+=20;
            outtextxy(10, cnt_endl_cod, "{");
            cnt_endl_cod+=20;
            //cout << "cin << " << p->afis << ";\n";
            cnt_endl_cod+=20;
        }
        strcpy(s, "cout<< ");
        strcat(s, p->afis);
        strcat(s, ";");
        //cout << "cin << " << p->afis << ";\n";
        outtextxy(x_al, cnt_endl_cod, s);
        cnt_endl_cod+=20;
        ConvertRec(p->urm, nr_al);
    }
}
void Converteste_Cod()
{
    int x_var;
    char s[350];
    pop_up_cod=initwindow(400, 600, "", 375, 105, 0, 0);
    setcurrentwindow(pop_up_cod);
    setbkcolor(BLACK);
    cleardevice();
    strcpy(s, "#include <bits/stdc++.h>");
    settextstyle(3, HORIZ_DIR, 1);
    setcolor(WHITE);
    outtextxy(5, 5, s);
    strcpy(s, "using namespace std;");
    outtextxy(5, 25, s);
    strcpy(s, "int main()");
    outtextxy(5, 45, s);
    strcpy(s, "{\n");
    outtextxy(5, 65, s);
//getch();
//closegraph(pop_up_cod);
//setcurrentwindow(fereastra);
    cnt_endl_cod=85;
    x_var=textwidth(s)+40;

    for (int i = 0; i <= cod_unic; i++)
        frecv[i] = 0;

    Set_Loops(start[1]);

    for (int i = 0; i <= cod_unic; i++)
        frecv[i] = 0;

    int sf;
    //"#include <bits/stdc++.h>\n\nusing namespace std;\n\nint main()\n{\n    int ";
    int nr_al = 1;
    Parcurge_Arb_Pt_ConvCod(start[1]);
    if (!M.empty())
    {
        strcpy(s, "int ");
        setcolor(WHITE);
        outtextxy(20, 85, s);
        cnt_endl_cod += 20;
    }

    for (auto it = M.begin(); it != M.end(); it++)
    {
        strcpy(s, it->first.c_str());
        sf=x_var+textwidth(s);

        strcat(s, ",");
        setcolor(WHITE);
        settextstyle(3, HORIZ_DIR, 1);
        outtextxy(x_var, 85, s);
        x_var=x_var+textwidth(s)+10;
    }

    strcpy(s, ";");
    outtextxy(sf, 85, s);
    x_al=20;
    for (int i = 0; i <= cod_unic; i++)
        frecv[i] = 0;
    ConvertRec(start[1], 1);
    strcpy(s, "return 0;");
    outtextxy(20, cnt_endl_cod, s);
    cnt_endl+=20;
    strcpy(s, "}");
    outtextxy(5, cnt_endl_cod+20, s);
    getch();
    closegraph(pop_up_cod);
    setcurrentwindow(fereastra);
    M.clear();
}

void MeniuPrincipal();


int pop_up_options, pop_up_help;
bloc *incarca[500];


void Decripteaza_Rec(bloc *anterior, int indice, char s[], int flag)
{
    if(s[indice] == '2' || s[indice] == '3' || s[indice] == '5')
    {
        int tip = s[indice] - '0';
        char car[350];
        int dim = 0;
        bloc *p;
        p = new bloc;
        p->cod = cod_unic++;
        p->type = tip;

        p->urm = p->adev = p->fals = NULL;
        indice++;
        indice++;
        int x, y;
        x = y = 0;
        while (s[indice] != ']')
        {
            x = x * 10 + (s[indice] - '0');
            indice++;
        }
        indice++;
        indice++;
        while (s[indice] != ']')
        {
            y = y * 10 + (s[indice] - '0');
            indice++;
        }
        indice++;
        indice++;;
        p->poz.x = x;
        p->poz.y = y;

        int inal1, inal2, inal3;

            inal1 = inal2 = inal3 = 0;

            while (s[indice] != ']')
            {
                inal1 = inal1 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal2 = inal2 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal3 = inal3 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            p->inaltimeb = inal1;
            p->lungimeb = inal2;
            p->lungime2b = inal3;

        if (tip == 2 || tip == 3)
        {
            p->cerc1.x = p->poz.x + 75/2;
            p->cerc2.x = p->poz.x + 75/2;
            p->cerc1.y = p->poz.y;
            p->cerc2.y = p->poz.y + 45;
        }
        else if (tip == 5)
        {
            p->cerc1.x = p->poz.x + 45/2;
            p->cerc2.x = p->poz.x + 45/2;
            p->cerc1.y = p->poz.y;
            p->cerc2.y = p->poz.y + 45;
        }
        strcpy(car, "");
        while (s[indice] != '}')
            car[dim++] = s[indice++];
        car[dim] = 0;
        strcpy(p->afis, car);
        indice++;

        if (flag == 0) anterior->urm = p;
        else if (flag == 1) anterior->fals = p;
        else anterior->adev = p;

        incarca[cod_unic - 1] = p;

        if (s[indice] == '-' && s[indice + 1] == '>') Decripteaza_Rec(p, indice + 2, s, 0);
        else if (s[indice] == 'j' && s[indice + 1] == '.')
        {
            x = 0;
            indice++;
            indice++;
            while ('0' <= s[indice] && s[indice] <= '9')
            {
                x = x * 10 + (s[indice] - '0');
                indice++;
            }
            p->urm = incarca[x - 1];
        }
    }
    else if (s[indice] == '4')
    {
        int tip = s[indice] - '0';
        char car[350];
        int dim = 0;
        bloc *p;
        p = new bloc;
        p->cod = cod_unic++;
        p->type = tip;
        p->urm = p->adev = p->fals = NULL;
        indice++;
        indice++;
        int x, y;
        x = y = 0;
        while (s[indice] != ']')
        {
            x = x * 10 + (s[indice] - '0');
            indice++;
        }
        indice++;
        indice++;
        while (s[indice] != ']')
        {
            y = y * 10 + (s[indice] - '0');
            indice++;
        }

        p->poz.x = x;
        p->poz.y = y;

        p->cerc1.x = p->poz.x;
        p->cerc1.y = p->poz.y;

        p->cerc2.x = p->poz.x - 125/2;
        p->cerc2.y = p->poz.y + 50;

        p->cerc3.x = p->poz.x + 125/2;
        p->cerc3.y = p->poz.y + 50;

        indice++;
        indice++;

        int inal1, inal2, inal3;

        inal1 = inal2 = inal3 = 0;

        while (s[indice] != ']')
        {
            inal1 = inal1 * 10 + (s[indice] - '0');
            indice++;
        }

        indice++;
        indice++;

        while (s[indice] != ']')
        {
            inal2 = inal2 * 10 + (s[indice] - '0');
            indice++;
        }

        indice++;
        indice++;

        while (s[indice] != ']')
        {
            inal3 = inal3 * 10 + (s[indice] - '0');
            indice++;
        }

        indice++;
        indice++;

        p->inaltimeb = inal1;
        p->lungimeb = inal2;
        p->lungime2b = inal3;

        while (s[indice] != '}')
            car[dim++] = s[indice++];
        car[dim] = 0;
        strcpy(p->instr, car);
        indice++;
        if (flag == 0) anterior->urm = p;
        else if (flag == 1) anterior->fals = p;
        else anterior->adev = p;
        indice++;
        if (flag == 0) anterior->urm = p;
        else if (flag == 1) anterior->fals = p;
        else anterior->adev = p;
        indice++;

        incarca[cod_unic - 1] = p;

        if(s[indice - 1] == '{' && s[indice] != '}') Decripteaza_Rec(p, indice, s, 2);
        else if (s[indice - 1] == 'j' && s[indice] == '.')
        {
            x = 0;
            indice++;
            while ('0' <= s[indice] && s[indice] <= '9')
            {
                x = x * 10 + (s[indice] - '0');
                indice++;
            }
            p->adev = incarca[x - 1];
        }

        int counter = 1;

        while (counter > 0)
        {
            if (s[indice] == 'F' && s[indice + 1] == '{')
            {
                counter--;
                indice++;
            }
            else if (s[indice] == 4)
            {
                counter++;
                indice++;
            }
            else indice++;
        }
        indice++;
        if(s[indice - 1] == '{' && s[indice] != '}') Decripteaza_Rec(p, indice, s, 1);
        else if (s[indice - 1] == 'j' && s[indice] == '.')
        {
            x = 0;
            indice++;
            while ('0' <= s[indice] && s[indice] <= '9')
            {
                x = x * 10 + (s[indice] - '0');
                indice++;
            }
            p->adev = incarca[x - 1];
        }
    }
    else if (s[indice] == '6')
    {
        int tip = s[indice] - '0';
        char car[350];
        int dim = 0;
        bloc *p;
        p = new bloc;
        p->cod = cod_unic++;
        p->type = tip;
        p->urm = p->adev = p->fals = NULL;
        indice++;
        indice++;
        int x, y;
        x = y = 0;
        while (s[indice] != ']')
        {
            x = x * 10 + (s[indice] - '0');
            indice++;
        }
        indice++;
        indice++;
        while (s[indice] != ']')
        {
            y = y * 10 + (s[indice] - '0');
            indice++;
        }
        p->poz.x = x;
        p->poz.y = y;

        p->cerc1.x = p->poz.x;
        p->cerc1.y = p->poz.y - 25;

        int inal1, inal2, inal3;

        inal1 = inal2 = inal3 = 0;

        while (s[indice] != ']')
        {
            inal1 = inal1 * 10 + (s[indice] - '0');
            indice++;
        }

        indice++;
        indice++;

        while (s[indice] != ']')
        {
            inal2 = inal2 * 10 + (s[indice] - '0');
            indice++;
        }

        indice++;
        indice++;

        while (s[indice] != ']')
        {
            inal3 = inal3 * 10 + (s[indice] - '0');
            indice++;
        }

        indice++;
        indice++;

        p->inaltimeb = inal1;
        p->lungimeb = inal2;
        p->lungime2b = inal3;

        indice++;

        if (flag == 0) anterior->urm = p;
        else if (flag == 1) anterior->fals = p;
        else anterior->adev = p;
        incarca[cod_unic - 1] = p;
    }
}

void Decripteaza(ifstream& fin)
{
    int nr, n;
    char s[1500];
    fin >> nr;
    fin.get();
    numar_arb = 0;
    for (int i = 1; i <= nr; i++)
    {
        fin.getline(s, 1500);
        n = strlen(s);
        int indice = 0;
        if (s[indice] == '1')
        {
            nr_start++;
            int tip = s[indice] - '0';
            char car[350];
            int dim = 0;
            bloc *p;
            p = new bloc;
            p->cod = cod_unic++;
            p->type = tip;
            p->urm = p->adev = p->fals = NULL;
            indice++;
            indice++;
            int x, y;
            x = y = 0;
            while (s[indice] != ']')
            {
                x = x * 10 + (s[indice] - '0');
                indice++;
            }
            indice++;
            indice++;
            while (s[indice] != ']')
            {
                y = y * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            p->poz.x = x;
            p->poz.y = y;

            p->cerc2.x = p->poz.x;
            p->cerc2.y = p->poz.y + 25;

            int inal1, inal2, inal3;

            inal1 = inal2 = inal3 = 0;

            while (s[indice] != ']')
            {
                inal1 = inal1 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal2 = inal2 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal3 = inal3 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;

            p->inaltimeb = inal1;
            p->lungimeb = inal2;
            p->lungime2b = inal3;

            start[++numar_arb] = p;
            incarca[cod_unic - 1] = p;
            if (s[indice] == '-' && s[indice + 1] == '>')Decripteaza_Rec(p, indice + 2,s, 0);
        }
        else if (s[indice] == '4')
        {
            int tip = s[indice] - '0';
            char car[350];
            int dim = 0;
            bloc *p;
            p = new bloc;
            p->cod = cod_unic++;
            p->type = tip;
            p->urm = p->adev = p->fals = NULL;
            indice++;
            indice++;
            int x, y;
            x = y = 0;
            while (s[indice] != ']')
            {
                x = x * 10 + (s[indice] - '0');
                indice++;
            }
            indice++;
            indice++;
            while (s[indice] != ']')
            {
                y = y * 10 + (s[indice] - '0');
                indice++;
            }
            p->poz.x = x;
            p->poz.y = y;

            p->cerc1.x = p->poz.x - 125/2;
            p->cerc1.y = p->poz.y + 50;

            p->cerc2.x = p->poz.x + 125/2;
            p->cerc2.y = p->poz.y + 50;

            int inal1, inal2, inal3;

            inal1 = inal2 = inal3 = 0;

            while (s[indice] != ']')
            {
                inal1 = inal1 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal2 = inal2 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal3 = inal3 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            p->inaltimeb = inal1;
            p->lungimeb = inal2;
            p->lungime2b = inal3;

            indice++;
            indice++;


            while (s[indice] != '}')
                car[dim++] = s[indice++];
            strcpy(p->afis, car);
            indice++;
            indice++;
            p->cerc1.x = p->poz.x;
            p->cerc1.y = p->poz.y - 25;

            incarca[cod_unic - 1] = p;

            if(s[indice] != '}') Decripteaza_Rec(p, indice, s, 2);
            int counter = 1;

            while (counter > 0)
            {
                if (s[indice] == 'F' && s[indice + 1] == '{')
                {
                    counter--;
                    indice++;
                }
                else if (s[indice] == 4)
                {
                    counter++;
                    indice++;
                }
                else indice++;
            }
            indice++;
            if(s[indice] != '}') Decripteaza_Rec(p, indice, s, 1);
        }
        else if(s[indice] == '2' || s[indice] == '3' || s[indice] == '5')
        {
            int tip = s[indice] - '0';
            char car[350];
            int dim = 0;
            bloc *p;
            p = new bloc;
            p->cod = cod_unic++;
            p->type = tip;
            p->urm = p->adev = p->fals = NULL;
            indice++;
            indice++;
            int x, y;
            x = y = 0;
            while (s[indice] != ']')
            {
                x = x * 10 + (s[indice] - '0');
                indice++;
            }
            indice++;
            indice++;
            while (s[indice] != ']')
            {
                y = y * 10 + (s[indice] - '0');
                indice++;
            }
            indice++;
            indice++;;
            p->poz.x = x;
            p->poz.y = y;

            if (tip == 2 || tip == 3)
            {
                p->cerc1.x = p->poz.x + 75/2;
                p->cerc2.x = p->poz.x + 75/2;
                p->cerc1.y = p->poz.y;
                p->cerc2.y = p->poz.y + 45;
            }
            else if (tip == 5)
            {
                p->cerc1.x = p->poz.x + 45/2;
                p->cerc2.x = p->poz.x + 45/2;
                p->cerc1.y = p->poz.y;
                p->cerc2.y = p->poz.y + 45;
            }

            int inal1, inal2, inal3;

            inal1 = inal2 = inal3 = 0;

            while (s[indice] != ']')
            {
                inal1 = inal1 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal2 = inal2 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            while (s[indice] != ']')
            {
                inal3 = inal3 * 10 + (s[indice] - '0');
                indice++;
            }

            indice++;
            indice++;

            p->inaltimeb = inal1;
            p->lungimeb = inal2;
            p->lungime2b = inal3;

            indice++;
            indice++;

            while (s[indice] != '}')
                car[dim++] = s[indice++];
            strcpy(p->afis, car);
            indice++;
            start[++numar_arb] = p;

            incarca[cod_unic - 1] = p;

            if (s[indice] == '-' && s[indice + 1] == '>')
                Decripteaza_Rec(p, indice + 2, s, 0);
        }

        else if (s[indice] == '6')
        {
            int tip = s[indice] - '0';
            char car[350];
            int dim = 0;
            bloc *p;
            p = new bloc;
            p->cod = cod_unic++;
            p->type = tip;
            p->urm = p->adev = p->fals = NULL;
            indice++;
            indice++;
            int x, y;
            x = y = 0;
            while (s[indice] != ']')
            {
                x = x * 10 + (s[indice] - '0');
                indice++;
            }
            indice++;
            indice++;
            while (s[indice] != ']')
            {
                y = y * 10 + (s[indice] - '0');
                indice++;
            }

            p->poz.x = x;
            p->poz.y = y;

            p->cerc1.x = p->poz.x;
            p->cerc1.y = p->poz.y - 25;

            incarca[cod_unic - 1] = p;

            start[++numar_arb] = p;
        }
    }

    for (int i = 1; i <= numar_arb; i++)
        Deseneaza_Schema(start[i]);

}

void Cripteaza();

void Cripteaza_Rec(bloc *p, ofstream& fout)
{
    if (p != NULL) frecv[p->cod]++;
    if (p == NULL || frecv[p->cod] >= 2) return;
    if (p->type == 1)
    {
        fout << "1[" << p->poz.x << "][" << p->poz.y << "]" << "[" << p->inaltimeb << "][" << p->lungimeb << "][" << p->lungime2b << "]";
        if (p->urm != NULL)
        {
            fout << "->";
            Cripteaza_Rec(p->urm, fout);
        }
    }
    else if (p->type == 2)
    {
        fout << "2[" << p->poz.x << "][" << p->poz.y << "][" << p->inaltimeb << "][" << p->lungimeb << "][" << p->lungime2b << "]{" << p->afis << "}";
        if (p->urm != NULL && frecv[p->urm->cod] == 0)
        {
            fout << "->";
            if (p->urm != NULL) Cripteaza_Rec(p->urm, fout);
        }
        else if (p->urm != NULL) fout << "j." << parcurg_mid[p->urm->cod];
    }
    else if(p->type == 3)
    {
        fout << "3[" << p->poz.x << "][" << p->poz.y << "][" << p->inaltimeb << "][" << p->lungimeb << "][" << p->lungime2b << "]{" << p->afis << "}";
        if (p->urm != NULL && frecv[p->urm->cod] == 0)
        {
            fout << "->";
            if (p->urm != NULL) Cripteaza_Rec(p->urm, fout);
        }
        else if (p->urm != NULL) fout << "j." << parcurg_mid[p->urm->cod];
    }
    else if(p->type == 4)
    {
        fout << "4[" << p->poz.x << "][" << p->poz.y << "][" << p->inaltimeb << "][" << p->lungimeb << "][" << p->lungime2b << "]{" << p->instr << "}";
        if (p->adev != NULL && frecv[p->adev->cod] == 0)
        {
            fout <<"T{";
            if (p->adev != NULL) Cripteaza_Rec(p->adev, fout);
            fout << "}";
        }
        else if (p->adev != NULL) fout << "Tj." << parcurg_mid[p->adev->cod];
        else fout << "T{}";
        if (p->fals != NULL && frecv[p->fals->cod] == 0)
        {
            fout <<"F{";
            if (p->fals != NULL) Cripteaza_Rec(p->fals, fout);
            fout << "}";
        }
        else if (p->fals != NULL) fout << "Fj." << parcurg_mid[p->fals->cod];
        else fout << "F{}";
    }
    else if(p->type == 5)
    {
        fout << "5[" << p->poz.x << "][" << p->poz.y << "][" << p->inaltimeb << "][" << p->lungimeb << "][" << p->lungime2b << "]{" << p->afis << "}";
        if (p->urm != NULL && frecv[p->urm->cod] == 0)
        {
            fout << "->";
            if (p->urm != NULL) Cripteaza_Rec(p->urm, fout);
        }
        else if (p->urm != NULL) fout << "j." << parcurg_mid[p->urm->cod];
    }
    else if(p->type == 6)
    {
        fout << "6[" << p->poz.x << "][" << p->poz.y << "]" << "[" << p->inaltimeb << "][" << p->lungimeb << "][" << p->lungime2b << "]";
    }
}

void Cripteaza(ofstream& fout)
{
    fout << numar_arb << "\n";
    for(int i = 1; i <= numar_arb; i++)
        Parcurgere_Arbore_Delete_FR(start[i]);

    for(int i = 0; i <= cod_unic; i++)
        frecv[i] = 0;

    for (int i = 1; i <= numar_arb; i++)
    {
        Cripteaza_Rec(start[i], fout);
        fout << "\n";
    }

    for(int i = 0; i <= cod_unic; i++)
        frecv[i] = parcurg_mid[i] = 0;
}


int pop_up_salvare, pop_up_lista;
fstream afara("aparitii.txt");


void Delete_Arb(bloc *&p)
{
    if (p == NULL) return;
    if (p->type != 4) Delete_Arb(p->urm);
    else if (p->type == 4)
    {
        Delete_Arb(p->adev);
        Delete_Arb(p->fals);
    }
    delete p;
}

void App()
{
    char var[350];
    int x_centru, y_centru, tip, pop_up;
    int valoare_var, lun, lun2, inal;
    fereastra=initwindow(1200, 750, "Schema noua");
    Deseneaza_Ecran();
    Init();

    ifstream intra("aparitii.txt");

    intra >> nr_fisiere;
    for (int i = 1; i <= nr_fisiere; i++)
        intra >> fisiere[i];
    intra.close();

    while(1)
    {
        int x, y;
        bool flag = 0;
        if (ismouseclick(WM_LBUTTONDBLCLK))
        {
            x=mousex();
            y=mousey();
            delay(5);
            clearmouseclick(WM_LBUTTONDBLCLK);
            bloc *piesa = ButonDinSchemaApasatDubluClick(x, y);
            for (int i = 0; i <= cod_unic; i++)
                frecv[i] = 0;
            if (piesa!= NULL)
            {
                str=piesa->afis;
                {
                    clearmouseclick(WM_RBUTTONDOWN);
                    if(piesa->type==2)
                    {
                        strcpy(var, "");
                        FereastraCitire(fereastra, var, valoare_var, theme);
                        strcpy(piesa->afis, var);
                        str=piesa->afis;
                        M[str]=0;
                    }
                    else if(piesa->type==3)
                    {
                        lun=piesa->lungimeb;
                        strcpy(var, "");
                        FereastraCalcul(fereastra, var, lun, theme);
                        piesa->lungimeb=lun;
                        if(theme==0) setfillstyle(SOLID_FILL, BLACK);
                        else setfillstyle(SOLID_FILL, COLOR(255, 229, 204));
                        bar (0, 80, 1045, 750);
                        piesa->cerc1.x=piesa->poz.x+piesa->lungimeb/2;
                        piesa->cerc2.x=piesa->poz.x+piesa->lungimeb/2;
                        strcpy(piesa->afis, var);
                        int i;
                        for(i=0; i<=cod_unic; i++)
                            frecv[i]=0;
                        //Deseneaza_Ecran();
                        for (int i = 1; i <= numar_arb; i++)
                        {
                            Deseneaza_Schema(start[i]);
                        }
                        for(i=0; i<=cod_unic; i++)
                            frecv[i]=0;
                        //Deseneaza_Ecran();
                    }
                    else if(piesa->type==4)
                    {
                        lun=piesa->lungimeb;
                        inal=piesa->inaltimeb;
                        strcpy(var, "");
                        FereastraDecizie(fereastra, var, lun, inal, theme);
                        strcpy(piesa->instr, var);
                        piesa->lungimeb=lun;
                        piesa->inaltimeb=inal;
                        if(theme==0) setfillstyle(SOLID_FILL, BLACK);
                        else setfillstyle(SOLID_FILL, COLOR(255, 229, 204));
                        //bar (0, 80, 1045, 750);
                       //  setactivepage(1-pag);
                       // bar (0, 80, 1045, 750);
                       // setactivepage(pag);
                        piesa->cerc2.x=piesa->poz.x-piesa->lungimeb/2;
                        piesa->cerc2.y=piesa->poz.y+piesa->inaltimeb;
                        piesa->cerc3.x=piesa->poz.x+piesa->lungimeb/2;
                        piesa->cerc3.y=piesa->poz.y+piesa->inaltimeb;
                        int i;
                        for(i=0; i<=cod_unic; i++)
                            frecv[i]=0;
                        //Deseneaza_Ecran();
                        for (int i = 1; i <= numar_arb; i++)
                        {
                            Deseneaza_Schema(start[i]);
                        }
                        for(i=0; i<=cod_unic; i++)
                            frecv[i]=0;

                    }
                    else if(piesa->type==5)
                    {
                        lun=piesa->lungimeb;
                        lun2=piesa->lungime2b;
                        inal=piesa->inaltimeb;
                        strcpy(var, "");
                        FereastraAfisare(fereastra, var, lun, lun2, inal, theme);
                        strcpy(piesa->afis, var);
                        piesa->lungimeb=lun;
                        piesa->lungime2b=lun2;
                        piesa->inaltimeb=inal;
                        if(theme==0) setfillstyle(SOLID_FILL, BLACK);
                        else setfillstyle(SOLID_FILL, COLOR(255, 229, 204));
                        bar (0, 80, 1045, 750);
                        piesa->cerc1.x=piesa->poz.x+piesa->lungime2b/2;
                        piesa->cerc2.x=piesa->poz.x+piesa->lungime2b/2;
                        int i;
                        for(i=0; i<=cod_unic; i++)
                            frecv[i]=0;
                        //Deseneaza_Ecran();
                        for (int i = 1; i <= numar_arb; i++)
                        {
                            Deseneaza_Schema(start[i]);
                        }
                        for(i=0; i<=cod_unic; i++)
                            frecv[i]=0;


                    }

                    //cout<<piesa->afis;
                    //delay(30);


                    for (int i = 1; i <= numar_arb; i++)
                        Deseneaza_Schema(start[i]);
                    for (int i = 0; i <= cod_unic; i++)
                        frecv[i] = 0;

                    // getch();
                    //getch();
                }
            }
        }

        else if (ismouseclick(WM_LBUTTONDOWN))
        {
            x = mousex();
            y = mousey();
            delay(5);
            clearmouseclick(WM_LBUTTONDOWN);
            int zona = GetZone(x, y);
            if (zona == 1 && nr_start < 1)
            {
                nr_start++;
                // Adaug_Bloc_Start(600, 375, 50, 25, 102, 0, 51, 255, 255, 255, 255, 255, 255);
                // for(i=1; i<=numar_arb; i++)
                //{//StergeLegaturi(start[i]);
                //cout<<"sters"<<endl;
                // }
                //cout<<"da";
                AdaugareBloc(1);
                flag = 1;
            }
            else if (zona == 2)
            {
                //Adaug_Bloc_Cin(600, 375, 75, 45, 45, 102, 0, 51, 0, 0, 0, 255, 255, 255);

                AdaugareBloc(2);
                flag = 1;
            }
            else if (zona == 3)
            {
                //Adaug_Bloc_Operatii(600, 375, 75, 45, 102, 0, 51, 255, 255, 255, 255, 255, 255);
                AdaugareBloc(3);
                flag = 1;
            }
            else if (zona == 4)
            {
                //Adaug_Bloc_If(600, 375, 125, 50, 102, 0, 51, 0, 0, 0, 255, 255, 255, "decizie");
                AdaugareBloc(4);
                flag = 1;
            }
            else if (zona == 5)
            {
                //Adaug_Bloc_Cout(600, 375, 75, 45, 45, 102, 0, 51, 0, 0, 0, 255, 255, 255);
                AdaugareBloc(5);
                flag = 1;
            }
            else if (zona == 6)
            {
                nr_stop++;
                //Adaug_Bloc_Stop(600, 375, 50, 25, 102, 0, 51, 255, 255, 255, 255, 255, 255);
                AdaugareBloc(6);
                flag = 1;
            }
            else if (zona == 7)
            {

                // cout<<endl;

                Ruleaza_Cod_Cu_Arbore();
            }
            else if (zona == 8) Converteste_Cod();
            else if(zona==9)
            {
                closegraph(fereastra);
                setcurrentwindow(meniu);
                MeniuPrincipal();
            }
            else if(zona==10) ///zona salvare incarcare
            {
                // cout<<"da10"<<endl;
                pop_up_options=0;
                pop_up_options=initwindow(250, 220, "", 190, 100, 0, 0);
                setcurrentwindow(pop_up_options);
                if(theme==0)
                    setbkcolor(COLOR(102, 0, 51));
                else setbkcolor(COLOR(204, 255, 255));
                cleardevice();
                //setcolor(WHITE);
                if(theme==0)
                    setfillstyle(SOLID_FILL, WHITE);
                else
                    setfillstyle(SOLID_FILL, BLACK);
                bar(0, 55, 250, 57);
                bar(0, 110, 250, 112);
                bar(0, 165, 250, 167);
                char s[100];
                strcpy(s, "Salveaza Schema");
                settextstyle(3, HORIZ_DIR, 1);
                if(theme==0)
                    setcolor(WHITE);
                else
                    setcolor(BLACK);

                outtextxy((250-textwidth(s))/2, (55-textheight(s))/2, s);
                //setcurrentwindow(fereastra);
                strcpy(s, "Incarca schema");
                outtextxy((250-textwidth(s))/2, 55+(55-textheight(s))/2, s);
                strcpy(s, "Lista scheme");
                outtextxy((250-textwidth(s))/2, 110+(55-textheight(s))/2, s);
                strcpy(s, "X");
                outtextxy((250-textwidth(s))/2, 165+(55-textheight(s))/2, s);
                clearmouseclick(WM_LBUTTONDOWN);
                int ok=0;
                while(!ok)
                {
                    if(ismouseclick(WM_LBUTTONDOWN))
                    {
                        int xm=mousex();
                        int ym=mousey();
                        delay(5);
                        clearmouseclick(WM_LBUTTONDOWN);
                        int ok1=0;

                        if(buton_salveaza_schema(xm, ym))
                        {
                            ok1=1;
                        }
                        else if(buton_incarca_schema(xm, ym))
                        {
                            ok1=2;
                        }
                        if(ok1==1 || ok1==2)
                        {
                            closegraph(pop_up_options);
                            setcurrentwindow(fereastra);
                            ok=1;
                            pop_up_salvare=initwindow(300, 150, "", 400, 300, 0, 0);
                            setcurrentwindow(pop_up_salvare);
                            char mesaj[150], s[350];
                            int tasta_apasata, cnt;
                            int caracter;
                            if(theme==0)
                                setbkcolor(COLOR(102, 0, 51));
                            else setbkcolor(COLOR(204, 255, 255));
                            cleardevice();
                            line(0, 75, 300, 75);
                            if(theme==0)
                                setcolor(WHITE);
                            else setcolor(BLACK);
                            settextstyle(3, HORIZ_DIR, 1);
                            if(ok1==1)
                            {
                                strcpy(mesaj, "Introduceti numele fisierului,");
                                outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2, mesaj);
                                strcpy(mesaj, "apoi apasati tasta Enter");
                                outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);


                            }
                            else
                            {
                                strcpy(mesaj, "Introduceti numele fisierului pe care");
                                outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2, mesaj);
                                strcpy(mesaj, "doriti sa il deschideti, apoi apasati Enter");
                                outtextxy((300-textwidth(mesaj))/2, (75-2*textheight(mesaj))/2+textheight(mesaj), mesaj);
                            }
                            tasta_apasata=getch();
                            s[0]=0;
                            cnt=-1;
                            while(tasta_apasata!=13)
                            {
                                caracter=(char) tasta_apasata;
                                if(caracter==8)
                                {
                                    if(cnt<0)
                                    {
                                        if(theme==0)
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
                                else
                                {
                                    s[++cnt]=caracter;
                                    s[++cnt]=0;
                                    if(theme==0)
                                        setcolor(WHITE);
                                    else
                                        setcolor(BLACK);
                                    outtextxy((300-textwidth(s))/2, 75+(75-2*textheight(s))/2, s);
                                    cnt--;
                                    tasta_apasata=getch();
                                }

                            }
                            if(ok1==1)
                            {
                                nr_fisiere++;
                                strcpy(fisiere[nr_fisiere], s);
                                int lenfis = strlen(fisiere[nr_fisiere]);
                                lenfis--;
                                if (fisiere[nr_fisiere][lenfis] != 't' || fisiere[nr_fisiere][lenfis - 1] != 'x' || fisiere[nr_fisiere][lenfis - 2] != 't' || fisiere[nr_fisiere][lenfis - 3] != '.') strcat(fisiere[nr_fisiere], ".txt");

                                ofstream fout(fisiere[nr_fisiere]);

                                afara << nr_fisiere << "\n";
                                for (int i = 1; i <= nr_fisiere; i++)
                                    afara << fisiere[i] << "\n";

                                Cripteaza(fout);

                                for (int i = 0; i <= cod_unic; i++)
                                    frecv[i] = 0;
                                fout.close();
                                afara.close();
                                 closegraph(pop_up_salvare);
                            setcurrentwindow(fereastra);
                            }
                            else
                            {for (int ke = 1; ke <= numar_arb; ke++)
                                    Delete_Arb(start[ke]);
                                numar_arb = 0;


                                strcpy(fisier_curent, s);
                                int lenfis = strlen(fisier_curent);
                                lenfis--;
                                if (fisier_curent[lenfis] != 't' || fisier_curent[lenfis - 1] != 'x' || fisier_curent[lenfis - 2] != 't' || fisier_curent[lenfis - 3] != '.') strcat(fisier_curent, ".txt");
                                ifstream fin(fisier_curent);
                                 closegraph(pop_up_salvare);
                            setcurrentwindow(fereastra);

                        if(theme==0) setfillstyle(SOLID_FILL, BLACK);
                        else setfillstyle(SOLID_FILL, COLOR(255, 229, 204));
                       bar (0, 80, 1045, 750);
                     //setactivepage(1-pag);
                       //bar (0, 80, 1045, 750);
                       //setactivepage(pag);
                       //pag=1-pag;



                                Decripteaza(fin);

                                for (int i = 0; i <= cod_unic; i++)
                                    frecv[i] = 0;
                                fin.close();
                            }

                        }
                        else if(buton_lista(xm, ym))
                        {closegraph(pop_up_options);
                        setcurrentwindow(fereastra);
                        pop_up_lista=initwindow(400, 600, "", 375, 105, 0, 0);
                        if(theme==0)  setbkcolor(COLOR(102, 0, 51));
                            else setbkcolor(COLOR(204, 255, 255));
                            cleardevice();
                        if(theme==0) setcolor(WHITE);
                        else setcolor(BLACK);
                        char s1[150];
                        settextstyle(3, HORIZ_DIR, 3);
                        strcpy(s1, "LISTA SCHEMELOR SALVATE:");
                        outtextxy(70, 5, s1);
                        int cnt_sp=50;
                        int nr;
                       for(int i=1; i<=nr_fisiere; i++)

                        {strcpy(s1, fisiere[i]);
                         if(theme==0) setcolor(WHITE);
                        else setcolor(BLACK);
                        s1[strlen(s1)-4]=0;
                        //strcpy(s1+2, s1);
                        //s1[0]=(char)(i-'0');
                        //s1[1]='.';
                        settextstyle(3, HORIZ_DIR, 2);
                        outtextxy(20, cnt_sp, s1);
                        cnt_sp+=30;
                        }
                        strcpy(s1, "Apasati orice tasta pentru a inchide");
                        settextstyle(3, HORIZ_DIR, 1);
                        outtextxy((400-textwidth(s1))/2, 500, s1);
                        getch();
                        closegraph(pop_up_lista);
                        setcurrentwindow(fereastra);
                        ok=1;

                        }

                        else if(buton_x(xm, ym))

                        {
                            closegraph(pop_up_options);
                            setcurrentwindow(fereastra);
                            ok=1;
                        }
                    }
                }
            }

            //delay(1500);
            //closegraph(pop_up_options);
            //setcurrentwindow(fereastra);


            else if(zona==11)
            {
                MeniuHelp(pop_up_help, fereastra, theme);

            }

            if (flag == 1)
            {
                for (int i = 1; i <= numar_arb; i++)
                    Deseneaza_Schema(start[i]);
                for (int i = 0; i <= cod_unic; i++)
                    frecv[i] = 0;
            }

            else
            {
                bloc *p;
                repr1=0;
                p = ButonDinSchemaApasat(x, y);
                for (int i = 0; i <= cod_unic; i++)
                    frecv[i] = 0;
                if (p != NULL)
                {
                    setvisualpage(pag);
                    Muta_Bloc(p, x, y);
                    for (int i = 0; i <= cod_unic; i++)
                        frecv[i] = 0;
                }
                else
                {
                    tip=0;
                    for (int i = 0; i <= cod_unic; i++)
                        frecv[i] = 0;
                    p=ButonLegatura(x, y, x_centru, y_centru, tip);
                    for (int i = 0; i <= cod_unic; i++)
                        frecv[i] = 0;
                    if(p!=NULL)  //Beep(2000,100);
                    {

                        CoordonateCercuri(p, x_centru, y_centru, tip);
                        if(tip!=2&&tip!=4&&tip!=6&&tip!=9 /*&& numar_arb!=1*/)
                        {
                            Beep(2000,100);
                            CreeazaLegaturi(p, x_centru, y_centru, tip);
                        }
                        //afisare();
                    }

                }
            }
        }

        else if (ismouseclick(WM_RBUTTONDOWN))
        {
            x = mousex();
            y = mousey();
            clearmouseclick(WM_RBUTTONDOWN);
            if (ButonDinSchemaApasat(x, y) != NULL)
            {
                setvisualpage(pag);

                for (int i = 0; i <= cod_unic; i++)
                    frecv[i] = 0;

                bloc *tmp = ButonDinSchemaApasat(x, y);

                for (int i = 0; i <= cod_unic; i++)
                    frecv[i] = 0;

                if (tmp->type == 1) nr_start--;
                delay(5);
                clearmouseclick(WM_RBUTTONDOWN);
                setactivepage(1 - pag);
                setcolor(0);
                setbkcolor(0);
                cleardevice();
                Deseneaza_Meniu(theme);

                int ind = Indice_Lista(tmp);

                for (int i = 0; i <= cod_unic; i++)
                    frecv[i] = 0;
                StergeBloc(tmp, ind);


                for (int i = 1; i <= numar_arb; i++)
                    Deseneaza_Schema(start[i]);
                for (int i = 0; i <= cod_unic; i++)
                    frecv[i] = 0;
                setvisualpage(1 - pag);
                pag = 1 - pag;
            }
        }
    }
    getch();
}

void MeniuPrincipal()
{
    int r = 121, g = 15, b = 122;
    int r1 = 0, g1 = 0, b1 = 0;
    char s[500];
    int xm,ym;

    int inaltime = 750, latime = 1200;
    meniu=initwindow(latime, inaltime, "Interschem");

    int inaltimebuton = 83, latimebuton = 600;
    int xText, yText;
    if(theme==0)
        setbkcolor(BLACK);
    else  setbkcolor(COLOR(255, 229, 204));
    cleardevice();
    if(theme==0) setfillstyle(SOLID_FILL, COLOR(121, 15, 122));
    else setfillstyle(SOLID_FILL, COLOR(204, 255, 255));

    settextstyle(3, HORIZ_DIR, 3);
    bar(300, 83+20, 900, 166+20);
    strcpy(s, "SCHEMA NOUA");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 83 + 20 + (inaltimebuton - textheight(s)) / 2;
    if(theme==0) setbkcolor(COLOR(121, 15, 122));
    else setbkcolor(COLOR(204, 255, 255));
    setcolor(0);
    outtextxy(xText, yText, s);

    bar(300, 226+20, 900, 309+20);
    strcpy(s, "LISTA SCHEME SALVATE");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 226 + 20 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    bar(300, 369+20, 900, 452+20);
    strcpy(s, "OPTIUNI");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 369 + 20 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);

    bar(300, 512+20, 900, 595+20);
    strcpy(s, "EXIT");
    xText = 300 + (latimebuton - textwidth(s)) / 2;
    yText = 512 + 20 + (inaltimebuton - textheight(s)) / 2;
    outtextxy(xText, yText, s);
    while(1)
    {
        int x, y;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            x=mousex();
            y=mousey();
            delay(5);
            clearmouseclick(WM_LBUTTONDOWN);
        }
        if(buton_schema_noua(x, y))
        {
            App();
        }
        else if(buton_selecteaza_schema(x, y))
        {  int ok1=0;

            if(ok==0) {if(theme==0)setbkcolor(BLACK);
            else  setbkcolor(COLOR(255, 229, 204));
            cleardevice();
                if(theme==0) setcolor(WHITE);
            else setcolor(BLACK);
            setcolor(COLOR(102, 0, 51));
              setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
            bar(20, 20, 100, 70);
            setcolor(WHITE);
            rectangle(20, 20, 100, 70);
            char s2[150];
            settextstyle(3, HORIZ_DIR, 3);
            setbkcolor(COLOR(102, 0, 51));
            strcpy(s2, "BACK");
            outtextxy(20+(80-textwidth(s2))/2, (50-textheight(s2)/2), s2);
            setfillstyle(SOLID_FILL, COLOR(102, 0, 51));
             setbkcolor(COLOR(102, 0, 51));
            bar (150, 70, 1100, 600);
            setcolor(WHITE);
             rectangle (150, 70, 1100, 600);
              setbkcolor(COLOR(102, 0, 51));
            strcpy(s2, "LISTA SCHEMELOR SALVATE:");
                outtextxy(450, 100, s2);
                       int cnt_sp=150;
                        int nr;
                       afara>>nr;
                       while(afara.getline(s2, 150))

                        {//strcpy(s2, fisiere[i]);
                         if(theme==0) setcolor(WHITE);
                        else setcolor(BLACK);
                        s2[strlen(s2)-4]=0;
                        //strcpy(s1+2, s1);
                        //s1[0]=(char)(i-'0');
                        //s1[1]='.';
                        settextstyle(3, HORIZ_DIR, 2);
                        outtextxy(200, cnt_sp, s2);
                        cnt_sp+=30;
                        }
                        ok=1;
        while(ok1==0)
        {if(ismouseclick(WM_LBUTTONDOWN))
        {int xm=mousex();
        int ym=mousey();
        clearmouseclick(WM_LBUTTONDOWN);
        if(xm>=20 && xm<=100 && ym>=20&& ym<=70)
        {ok1=1;
        MeniuPrincipal();
        }
        }
        }
        }

        }
        else if(buton_optiuni(x, y))
        {
            Deseneaza_Ecran_Optiuni(theme);
            int ok;
            while(1)
            {
                if (ismouseclick(WM_LBUTTONDOWN))
                {
                    ok=0;
                    xm=mousex();
                    ym=mousey();
                    delay(5);
                    clearmouseclick(WM_LBUTTONDOWN);
                }
                if(buton_schema_noua(xm, ym))
                {
                    theme=1;
                    if(ok==0)
                    {
                        Deseneaza_Ecran_Optiuni(1);
                        ok=1;
                    }

                }
                else if(buton_selecteaza_schema(xm, ym))
                {
                    theme=0;
                    if(ok==0)
                    {
                        Deseneaza_Ecran_Optiuni(0);
                       // if(theme==0)setbkcolor(BLACK);
                       // else  setbkcolor(COLOR(255, 229, 204));
                        //cleardevice();
                        ok=1;
                    }

                }
                else if(buton_optiuni(xm, ym))
                {
                    if(ok==0)
                    {
                        MeniuPrincipal();
                        ok=1;
                    }
                }
            }

        }

        else if(buton_exit(x, y))
            exit(0);
    }

    // getch();
    // closegraph();
    //return 0;
}

int main()
{
    MeniuPrincipal();
    getch();
    closegraph();
//cout<<start[0]->fals->type;
//cout<<numar_arb<<endl;
    return 0;
}
