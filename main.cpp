#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <iomanip>
#include <time.h>
#include <cstring>
using namespace std;
int f[52];

struct carte
{
    int val;
    int tip;
    carte *leg;
} *pachet, *pjuc1, *pjuc2;

char sir[100];
char cval[13][10] = {"as", "doi", "trei", "patru", "cinci", "sase", "sapte", "opt", "noua", "zece", "valet", "dama", "popa"};
char ctip[4][15] = {"inima rosie", "inima neagra", "trefla", "romb"};

carte *creare()
{
    int tip, val;
    carte *p, *q;
    p = NULL;
    for (int i = 0; i < 52; i++)
    {
        int x = rand() % 52;
        while (x < 52 && f[x] == 1)
        {
            x++;
        }
        if (x == 52)
        {
            x = 0;
            while (f[x])
                x++;
        }
        f[x] = 1;

        tip = x / 13;
        val = x % 13 + 1;

        q = new carte;
        q->val = val;
        q->tip = tip;
        q->leg = p;
        p = q;
    }
    return p;
}

void imparte_pachet(carte *pachet, carte *&pjuc1, carte *&pjuc2)
{
    pjuc1 = NULL;
    pjuc2 = NULL;
    int nr = 0;
    carte *q;
    while (pachet)
    {
        nr++;
        q = pachet;
        pachet = pachet->leg;
        if (nr % 2 == 1)
        {
            q->leg = pjuc1;
            pjuc1 = q;
        }
        else
        {
            q->leg = pjuc2;
            pjuc2 = q;
        }
    }
}

void push(int val, int tip, carte *&p)
{
    carte *q;
    carte *u;
    q = new carte;
    q->val = val;
    q->tip = tip;
    q->leg = NULL;
    if (!p)
        p = q;
    else
    {
        u = p;
        while (u->leg)
            u = u->leg;
        u->leg = q;
    }
}

void pop(carte *&p)
{
    carte *q;
    if (p)
    {
        q = p;
        p = p->leg;
        delete q;
    }
}

int front(carte *p)
{

    return p->val - 1;
}

void afis(char sir[], int lat, char x)
{
    if (x == 'l')
    {
        cout << sir;
        for (int i = 1; i <= lat - strlen(sir); i++)
            cout << " ";
    }
}

void parcurgere(carte *prim1, carte *prim2)
{
    while (prim1 || prim2)
    {
        if (prim1)
        {
            strcpy(sir, cval[prim1->val - 1]);
            strcat(sir, " ");
            strcat(sir, ctip[prim1->tip]);
            afis(sir, 30, 'l');
            prim1 = prim1->leg;
        }
        else
            afis(" ", 30, 'l');

        if (prim2)
        {
            strcpy(sir, cval[prim2->val - 1]);
            strcat(sir, " ");
            strcat(sir, ctip[prim2->tip]);
            afis(sir, 30, 'l');
            prim2 = prim2->leg;
        }
        else
            afis(" ", 30, 'l');
        cout << "\n";
    }
}

int v[60], k;

int main()
{

    int nr = 0;
    srand(time(NULL));

    pachet = creare();
    imparte_pachet(pachet, pjuc1, pjuc2);

    do
    {

        afis("jucator 1:", 30, 'l');
        afis("jucator 2:", 30, 'l');
        cout << endl;
        if (nr == 0)
            parcurgere(pjuc1, pjuc2);
        else
        {
            strcpy(sir, cval[pjuc1->val - 1]);
            strcat(sir, " ");
            strcat(sir, ctip[pjuc1->tip]);
            afis(sir, 30, 'l');

            strcpy(sir, cval[pjuc2->val - 1]);
            strcat(sir, " ");
            strcat(sir, ctip[pjuc2->tip]);
            afis(sir, 30, 'l');
        }
        nr++;
        cout << "\n";
        cout << "carte jos: " << cval[v[k]];
        cout << "\n";
        bool ok = false;
        // cand jucatorii pun cartile jos
        if (pjuc1->val - 1 == v[k])
        {
            v[++k] = pjuc1->val;
            pop(pjuc1);
            ok = true;
        }
        else if (pjuc2->val - 1 == v[k])
        {
            v[++k] = pjuc2->val;
            pop(pjuc2);
            ok = true;
        }
        /* datul cartilor intre juc
        if(front(pjuc1) == v[k] + 1){
            v[++k] = front(pjuc1);
            pop(pjuc1);
            ok = true;
    }else if(front(pjuc2) == v[k] + 1){
            v[++k] = front(pjuc2);
            pop(pjuc2);
            ok = true;
        }*/
        if (v[k] == 14)
            v[++k] = 0;

        if (!ok)
        {
            push(pjuc1->val, pjuc1->tip, pjuc1);

            push(pjuc2->val, pjuc2->tip, pjuc2);

            pop(pjuc1);
            pop(pjuc2);
        }
        // system("cls");
        getch();
    } while (pjuc1 && pjuc2);

    return 0;
}