#include <Windows.h>
#include <iostream>
#include <fstream>
#include <map>
#include <list>
#include <vector>
using namespace std;

class Usel 
{
public: 
    int kolvo = 0;
    char simv = 0;
    Usel* left,*right;

    Usel() { left = right = NULL; }   //Основной конструктор

    Usel (Usel* L, Usel* R)     //Конструктор, чтобы соединать рядом стоящие узлы в один
    {
        left = L;
        right = R;
        kolvo = L->kolvo + R->kolvo;
    }
};

vector<bool> code;
map<char, vector<bool> > Spisok;

struct DlaSort                //Структура для сортировки листа по возврастания
{     
    bool operator() (Usel* lev, Usel* prav) const
    {
        return lev->kolvo < prav->kolvo;
    }
};


void PrisvaivSimvCod(Usel* Vershina)
{
    if (Vershina == NULL)
        return;
    if (Vershina->left != NULL)
    {
        code.push_back(0);
        PrisvaivSimvCod(Vershina->left);
    }
    if (Vershina->right != NULL) 
    {
        code.push_back(1);
        PrisvaivSimvCod(Vershina->right);
    }
    if (Vershina->left == NULL && Vershina->right == NULL)
        Spisok[Vershina->simv] = code;

    if (!code.empty())
        code.pop_back();
}

void PodchSimvol(map<char, int> &KolvoSimv, string filename)              //Подсчет символов в файле
{
    ifstream file(filename, ios::binary);
    char isfila;

    if (!file.is_open())
        printf("Error, file isn\'t open T_T\n");
    else
        if (file.eof())
            printf("File is empty =(\n");
        else
        {
            while (file.get(isfila)) 
            {
                KolvoSimv[isfila]++;
            }
        }

    
    file.close();
}

void ZamenSimvol(string Filename, string Filenamebin)              //Подсчет символов в файле
{
    ifstream file(Filename, ios::binary);
    ofstream itog(Filenamebin, ios::binary);
    char isfila;

    file.clear();
    file.seekg(0, ios_base::beg);

    int count = 0; 
    char buff = 0;
    while (file.get(isfila))
    {
        vector<bool> code = Spisok[isfila];

        for (bool bit : code) 
        {
            buff = buff << 1 | bit;
            count++;
            if (count == 8) 
            {
                itog.put(buff);
                count = 0;
                buff = 0;
            }
        }
    }

    file.close();

    if (count > 0) {
        buff = buff << (8 - count);
        itog.put(buff);
    }

    itog.close();
}


void ObratRash(Usel* Vershina, string Falename) 
{
    ifstream F(Falename, ios::in | ios::binary);

    Usel* p = Vershina;
    int count = 0; 
    char byte;
    byte = F.get();
    while (F.eof())
    {
        bool b = byte & (1 << (7 - count));
        if (b) 
            p = p->right; 
        else 
            p = p->left;
        if (p->left == NULL && p->right == NULL) 
        { 
            cout << p->simv; 
            p = Vershina; 
        }
        count++;
        if (count == 8) 
        { 
            count = 0; 
            byte = F.get(); 
        }
    }

    F.close();
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Error, not coef");
        return 1;
    }
    
    string choose = argv[1];
    string Filename = argv[2];
    string FilenameBin = argv[3];

    map<char, int> KolvoSimv;
    PodchSimvol(KolvoSimv, Filename);

    list<Usel*> VseSimv;

    map<char, int>::iterator i;
    for (i = KolvoSimv.begin(); i != KolvoSimv.end(); ++i)
    {
        Usel* nUsel = new Usel();
        nUsel->simv = i->first;
        nUsel->kolvo = i->second;
        VseSimv.push_back(nUsel);
    }

    while (VseSimv.size() > 1)
    {
        VseSimv.sort(DlaSort());
        Usel* Perv = VseSimv.front();
        VseSimv.pop_front();
        Usel* Vtor = VseSimv.front();
        VseSimv.pop_front();

        Usel* glavn = new Usel(Perv, Vtor);
        VseSimv.push_back(glavn);
    }

    Usel* Vershina = VseSimv.front();
    PrisvaivSimvCod(Vershina);

    if (choose == "e")
    {
        ZamenSimvol(Filename,FilenameBin);
    }
    else
        if (choose == "d")
        {
            ObratRash(Vershina, FilenameBin);
        }
        else
            printf("Error");

    return 0;
}


