#include <iostream>
#include <string>

using namespace std;
class PKO;
class Konto
{
    friend class PKO;

    private:
        string nazwa;
        string kto;
        float kwota;
        float wp_wyp;

    void Wypisz()
    {
      cout<< nazwa<<":  "<<kwota<<" zl   "<<kto<<":  "<<wp_wyp<<" zl"<<endl;
    }

    bool Wplac(float wplata)
    {
     if(wplata>=0)
     {
         kwota+=wplata;
         wp_wyp=wplata;
         return true;
     }
     else
     {
         return false;
     }
    }

    bool Wyplac(float wyplata)
    {
     if (wyplata<kwota)
     {
      kwota-=wyplata;
      wp_wyp=(wyplata*(-1));
      return true;
     }
     else
     {
         return false;
     }
    }

    public:
    Konto (string nazwa="", string kto="", float kwota=0.0, float wp_wyp=0.0):nazwa(nazwa),kto(kto),kwota(kwota),wp_wyp(wp_wyp) //skrocona forma konstruktora
    {
    }
};

class PKO
{
    private:
    int ilekont;
    Konto *tabKonta; //zainicjowanie czegos co bedzie nam zbierac konta pozniej
    string wlasciciel;
    string pelnomocnik;
    string logon;

    public:
    PKO (int ilekont_=0,string wlasciciel_="", string pelnomocnik_="")
    {
        ilekont=ilekont_;
        tabKonta=new Konto[ilekont];
        wlasciciel=wlasciciel_;
        pelnomocnik=pelnomocnik_;
        logon=wlasciciel;
    }

    ~PKO()
    {
     int ilekont=0; string wlasciciel="";  string pelnomocnik=""; string logon="";
     delete[] tabKonta;
    }

    void Ustaw(string nazwa_, float kwota_, int id)
    {
     tabKonta[id-1].nazwa=nazwa_;
     tabKonta[id-1].Wplac(kwota_);
     tabKonta[id-1].kto=logon;
    }

    void Przelew(float kwota_,string nakonto="",string zkonto="")
    {

        for (int i=0; i<ilekont; i++)
        {
            if (zkonto==tabKonta[i].nazwa)
            {
                tabKonta[i].Wyplac(kwota_);
                tabKonta[i].kto=logon;
            }
        }
        for (int i=0; i<ilekont; i++)
        {
            if (nakonto==tabKonta[i].nazwa)
            {
                tabKonta[i].Wplac(kwota_);
                tabKonta[i].kto=logon;

            }
        }

    }

    bool LogIN( string logujacy)
    {

        if (logujacy == wlasciciel || logujacy==pelnomocnik )
        {
            cout<< "Login poprawny"<<endl;
            logon=logujacy;
            return true;
        }
        else
        {
           cout<< "Login niepoprawny"<<endl;
            return false;
        }
    }

     void Show()
 {
     cout<<"-------------------------------------------------------------"<<endl;
     for(int i=0; i<ilekont; i++)
     {
         cout<<i+1<<". "<<tabKonta[i].nazwa<<":   "<<tabKonta[i].kwota<<" zl    "<<tabKonta[i].kto<<": "<<tabKonta[i].wp_wyp<<" zl"<<endl;
     }
    cout<<"--------------------------------------------------------------"<<endl;
 }
};
int main()
{
   PKO pko_moje(3,"Cezary","Joanna");
   pko_moje.Ustaw("Glowne",3599.9, 1);
   pko_moje.Ustaw("Oszcz",2340.5, 2);
   pko_moje.Ustaw("Lokata",5321.3, 3);
   pko_moje.Show();

  cout<< "Witamy w PKO. Prosze podac login: "<<endl;
  string help_login;
  cin>>help_login;
  pko_moje.LogIN(help_login);

  int operacja;
  string konto;
  string nakonto;
  string zkonto;
  float kwota;

  do
  {

  cout<< "Wplata - 1"<<endl<<"Wyplata - 2"<<endl<< "Przelew - 3"<<endl<< "WYJSCIE - 0"<<endl;
  cin>>operacja;


  switch (operacja)
  {
/*string konto;
  float kwota; */ //nie rub tak ok?
   case 0:
        break;

   case 1:

   cout<< "Konto:"<<endl;
    cin>>konto;
    cout<<"Kwota: "<<endl;
    cin>> kwota;
    pko_moje.Przelew(kwota,konto);

    break;


   case 2:
   cout<< "Konto:"<<endl;
    cin>>konto;
    cout<<"Kwota: "<<endl;
    cin>> kwota;
    pko_moje.Przelew(kwota,"",konto);
   break;

   case 3:
   cout<< "Konto z:"<<endl;
    cin>>zkonto;
    cout<< "Konto na:"<<endl;
    cin>>nakonto;
    cout<<"Kwota: "<<endl;
    cin>> kwota;
    pko_moje.Przelew(kwota,nakonto,zkonto);
   break;

   default :
       cout<< "Blad!"<<endl;
  }

  pko_moje.Show();

  }while(operacja!=0);

    return 0;
}
