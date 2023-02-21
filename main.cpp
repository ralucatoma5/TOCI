#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <time.h>
using namespace std;
int f[52];

struct carte
{
    int val;
    int tip;
    carte *leg;
} *pachet, *pjuc1, *pjuc2;
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

void parcurgere(carte *prim)
{
    while (prim)
    {
        cout << cval[prim->val - 1] << " " << ctip[prim->tip] << endl;
        prim = prim->leg;
    }
}

int v[60], k;

int main()
{

    srand(time(NULL));

    pachet = creare();
    imparte_pachet(pachet, pjuc1, pjuc2);

    do
    {
        cout << "jucator 1: \n";
        parcurgere(pjuc1);
        cout << "\n";
        cout << "jucator 2: \n";
        parcurgere(pjuc2);
        cout << "\n";
        cout << "parte jos: " << cval[v[k]];
        cout << "\n";
        bool ok = false;
        // cand jucatorii pun cartile jos
        if (pjuc1->val - 1 == v[k])
        {
            pop(pjuc1);
            ok = true;
        }
        else if (pjuc2->val - 1 == v[k])
        {
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
        getch();
    } while (pjuc1 && pjuc2);

    return 0;
}