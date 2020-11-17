#include <stdio.h>
#include <stdlib.h>



typedef struct
{

    char ime[20];
    char prezime[20];
    char brIndex[10];
    int ocjena;


} TStudent;



//prototipovi
void unosStudenta(TStudent* student, int *brEl);
void ispisStudenata(TStudent* student, int brEl);
void izmjenaStudenta(TStudent* student, int *brEl);
void pretragaStudenta(TStudent* student, int *brEl);
void brisanjeStudenta(TStudent* student, int *brEl);
void sortinranjePoImenuPrezimenu(TStudent* student, int brEl);
void sortinranjePoOcjeni(TStudent* student, int brEl);


int main()

{
    int opcija; //bira opciju iz menija
    TStudent student[50];
    int brEl=0; //broji koliko ima studenata u nizu
    int uspio=0; //osigurava unos opcije od 0-5
    int odg; //bira u case 2 jednu od 2 opcije
    FILE *file ;


    do
    {
        //MENI
        printf("\n\---------------------------------------------------------------------------------------------------\n\n");
        printf("\n\t\tEvidencija studenata na izbornom predmetu\n");
        printf("\n\n\---------------------------------------------------------------------------------------------------\n\n");
        printf("\t\t1. Unos novog studenta");
        printf("\n\t\t2. Ispis svih studenata");
        printf("\n\t\t3. Izmjena postojeceg studenta");
        printf("\n\t\t4. Pretrazivanje studenta po broju indeksa");
        printf("\n\t\t5. Brisanje studenta");
        printf("\n\t\t6. Sortiranje studenata po imenu i prezimenu.");
        printf("\n\t\t7. Sortiranje studenata po ocjeni.");
        printf("\n\t\t0. Izlaz\n\n");
        //KRAJ MENIJA

        //POCETAK BLOKA: OSIGURAVA UNOS OPCIJE OD 0 DO 7

        do
        {
            printf("---------------------------------------------------------------------------------------------------\n");
            printf("\nUnesite zeljenu opciju: ");
            //scanf("%d", &opcija);

            if(scanf("%d", &opcija) != 1)
            {
                printf("\nOpcja koju ste izabrali nije validna. Molimo Vas, izaberite jednu od postojecih opcija.\n");
                fflush(stdin);
            }
            else if(opcija <0 || opcija>7)
            {
                printf("\nOpcja koju ste izabrali nije validna. Molimo Vas, izaberite jednu od postojecih opcija.\n");

            }
            else
            {
                uspio=1;
            }
        }
        while(uspio==0);
        //KRAJ BLOKA: OSIGURAVA UNOS OPCIJE OD 0 DO 7
        system("cls");
        switch(opcija)
        {

        case 1:
        {
            unosStudenta(student, &brEl);
            break;
        }
        case 2:
        {
            char line[30]; //u promjenljivu line se smjesta student iz tekstualnog fajla, odnosno prva linija
            int prosao=0; //osigurava unos jedne od 2 opcije


            printf("\n1. Ispis novododatih studenata.\n");
            printf("\n2. Ispis postojecih studenata iz datoteke.\n");
            //ZASTITA UNOSA JEDNE OD 2 OPCIJE
            do
            {
                printf("\nUnesite zeljenu opciju.\n");
                if( scanf("%d", &odg)!=1)
                {
                    printf("\nMolimo Vas, unesite odgovarajucu opciju.\n");
                    fflush(stdin);
                }
                else if(odg<1 || odg>2)
                {
                    printf("\nMolimo Vas, unesite odgovarajucu opciju.\n");

                }


                else
                {
                    prosao=1;
                    system("cls");
                }

            }
            while(prosao==0);
            //KRAJ BLOKA: ZASTITA UNOSA JEDNE OD 2 OPCIJE


            switch(odg)
            {
            case 1: //ISPIS STUDENATA KOJI SU TEK DODATI
            {
                ispisStudenata(student, brEl);
                break;
            }
            case 2: //ISPIS STUDENATA KOJI SU SACUVANI U DATOTECI
            {
                //CITANJE PODATAKA IZ DATOTEKE
                if ((file = fopen("spisak.txt","r+")) != NULL)	// Otvaranje datoteke sa provjerom prava na citanje(r)
                {

                    while (fgets(line, 50, file) != NULL) // Citanje stringova maksimalne duzine 50 iz ulazne datoteke
                    {
                        printf("%s", line);

                    }
                    fclose(file);	// Zatvaranje datoteke
                }
                //CITANJE PODATAKA IZ DATOTEKE
                break;

            }
            }
            //KRAJ SWITCH PETLJE

            break;
        }

        case 3:
        {
            izmjenaStudenta(student, &brEl);
            break;
        }
        case 4:
        {
            pretragaStudenta(student, &brEl);
            break;
        }
        case 5:
        {
            brisanjeStudenta(student, &brEl);
            break;
        }
        case 6:
        {
            sortinranjePoImenuPrezimenu(student,brEl);
            break;
        }
        case 7:
        {
            sortinranjePoOcjeni(student, brEl);
            break;
        }

        }

    }
    while(opcija!=0);
    //KRAJ BLOKA: OSIGURAVA UNOS OPCIJE OD 0 DO 7


    //POCETAK BLOKA: CUVANJE UNIJETIH STUDENATA U DATOTEKU
    if ((file = fopen("spisak.txt", "a+")) != NULL)	// Otvaranje datoteke sa provjerom prava na pisanje (w)
    {
        for(int i=0; i<brEl; i++)
        {
            fprintf(file,"\n%s %s %s %d", student[i].ime, student[i].prezime, student[i].brIndex, student[i].ocjena);	// Upis imena i prezimena u izlaznu tekstualnu datoteku
        }
        fclose(file);	// Zatvaranje datoteke
    }
    else
    {
        printf("\nGreska prilikom otvaranja datoteke za pisanje.\n");
    }
    //KRAJ BLOKA: CUVANJE UNIJETIH STUDENATA U DATOTEKU

    return 0;
}
//KRAJ main() FUNKCIJE


//FUNKCIJE


void unosStudenta(TStudent* student, int *brEl)
{
    int  uspeo = 0;  // OSIGURAVA UNOS OCJENE OD 5-10
    int ime, prezime; //BROJI DUZINU STRINGA

    system("cls");
    printf("\n------------------------------------------- UNOS STUDENTA -------------------------------------------");
    printf("\n\n*NAPOMENA: Tek nakon izlaska iz programa, podaci koje ste unijeli bice sacuvani u datoteci.\n");
    printf("\n\nUnesite ime studenta: ");
    scanf("%s", student[*brEl].ime);

    ime=strlen(student[*brEl].ime); //U PROMJENLJIVU IME SE SMJESTA DUZINA STRINGA

    //STAVLJA VELIKO POCETNO SLOVO
    if(student[*brEl].ime[0]>=97 && student[*brEl].ime[0]<=122)
    {
        student[*brEl].ime[0]=student[*brEl].ime[0]-32;
    }
    //SVA SLOVA OSIM POCETNOG PRETVARA U MALA
    for(int i=1; i<=ime; i++)
    {
        if(student[*brEl].ime[i]>=65 && student[*brEl].ime[i]<=90)
        {
            student[*brEl].ime[i]=student[*brEl].ime[i]+32;
        }

    }


    printf("\nUnesite prezime studenta: ");
    scanf("%s", student[*brEl].prezime);

    prezime=strlen(student[*brEl].prezime); //U PROMJENLJIVU PREZIME VRACA DUZINU STRINGA

    //STAVLJA VELIKO POCETNO SLOVO
    if(student[*brEl].prezime[0]>=97 && student[*brEl].prezime[0]<=122)
    {
        student[*brEl].prezime[0]=student[*brEl].prezime[0]-32;
    }
    //SVA SLOVA OSIM POCETNOG PRETVARA U MALA
    for(int i=1; i<=prezime; i++)
    {
        if(student[*brEl].prezime[i]>=65 && student[*brEl].prezime[i]<=90)
        {
            student[*brEl].prezime[i]=student[*brEl].prezime[i]+32;
        }

    }

    //POCETAK BLOKA: OSIGURAVA UNOS INDEKSA U ODGOVARAJUCEM FORMATU
    do
    {
        printf("\nUnesite indeks studenta[MHXX/YYYY]: ");

        scanf("%s", student[*brEl].brIndex);
        // MH XX / YYYY
        // 01 23 4 5678
        //OSIGURAJ DA JE 0='M', 1= 'H', 4='/' i ostali karakteri u stringu da su brojevi
        if(student[*brEl].brIndex[0]!='M' || student[*brEl].brIndex[1]!='H' || student[*brEl].brIndex[4]!='/'
                || (student[*brEl].brIndex[2]<48 || student[*brEl].brIndex[2]>57)
                || (student[*brEl].brIndex[3]<48 || student[*brEl].brIndex[3]>57)
                || (student[*brEl].brIndex[5]<48 || student[*brEl].brIndex[5]>57)
                || (student[*brEl].brIndex[6]<48 || student[*brEl].brIndex[6]>57)
                || (student[*brEl].brIndex[7]<48 || student[*brEl].brIndex[7]>57)
                || (student[*brEl].brIndex[8]<48 || student[*brEl].brIndex[8]>57) )
        {
            printf("\nMolimo Vas, unesite broj indeksa u odgovarajucem formatu.\n");
        }

    }
    while(student[*brEl].brIndex[0]!='M' || student[*brEl].brIndex[1]!='H' || student[*brEl].brIndex[4]!='/'
            || (student[*brEl].brIndex[2]<48 || student[*brEl].brIndex[2]>57)
            || (student[*brEl].brIndex[3]<48 || student[*brEl].brIndex[3]>57)
            || (student[*brEl].brIndex[5]<48 || student[*brEl].brIndex[5]>57)
            || (student[*brEl].brIndex[6]<48 || student[*brEl].brIndex[6]>57)
            || (student[*brEl].brIndex[7]<48 || student[*brEl].brIndex[7]>57)
            || (student[*brEl].brIndex[8]<48 || student[*brEl].brIndex[8]>57) );

    //KRAJ BLOKA: OSIGURAVA UNOS INDEKSA U ODGOVARAJUCEM FORMATU


    //POCETAK BLOKA: OSIGURAVA UNOS OCJENE OD 5-10
    do
    {

        printf("\nUnesite ocjenu studenta: ");
        fflush(stdin);
        if (scanf("%d", &student[*brEl].ocjena) != 1) //UKOLIKO SE UNESE NENUMERICKI KARAKTER
        {
            printf("GRESKA: Uneta vrednost nije broj!\n");
            fflush(stdin);  // ukloni neispravnu vrednost
        }
        else if(student[*brEl].ocjena<5 || student[*brEl].ocjena>10)
        {
            printf("\nMolimo Vas, unesite ocjenu od 5 do 10.\n");
        }
        else
        {
            uspeo = 1; //ukoliko je unos ispravan, uspio=1 i izlazi se iz do-while petlje
        }

    }
    while (uspeo == 0);

    //KRAJ BLOKA: OSIGURAVA UNOS OCJENE OD 5-10

    (*brEl)++; //NAKON SVAKOG UNOSA, BROJAC STUDENATA U NIZU SE POVECAVA
    system("cls");

}

void ispisStudenata(TStudent* student,int brEl)
{
    system("cls");
    printf("\n\n\---------------------------------------------------------------------------------------------------");
    printf("\n\n\tSPISAK STUDENATA");
    printf("\n\n\---------------------------------------------------------------------------------------------------\n\n");

    for(int i=0; i<brEl; i++)
    {
        printf("\t%d. %10s %20s %20s %10d\n\n", i+1, student[i].ime, student[i].prezime, student[i].brIndex, student[i].ocjena);
    }

}


void izmjenaStudenta(TStudent* student, int *brEl)
{
    int izmjena; //redni broj studenta ciji se podaci mijenjaju
    char odg_izmjena; // da li zeli korisnik da izmijeni podatke
    int izbor_izmjena; //bira se koji podatak se mijenja
    int uspio=0, uspio1=0,uspio2=0, uspio3=0; //osiguravaju korektan unos trazenih opcija
    int ime, prezime; //broji duzinu stringa

    system("cls");
    printf("\n------------------------------------------- IZMJENA STUDENTA -------------------------------------------\n");
    printf("\n\n*NAPOMENA: Podatke o studentima koji su sacuvani u datoteci nije moguce mijenjati.\n");

    //ukoliko je spisak prazan
    if(*brEl==0)
    {
        printf("\n\nNovi spisak sadrzi %d studenata. Nema podataka koje je moguce izmijeniti.\n ", *brEl);
    }

    //ukoliko spisak nije prazan
    else
    {
        //POCETAK BLOKA: OSIGURAVA UNOS REDNOG BROJA STUDENTA KOG ZELIMO DA IZMIJENIMO
        do
        {
            printf("\n\nNovi spisak sadrzi %d studenata. Spisak krece od rednog broja 0., redom.\n ", *brEl);
            printf("\n\nUnesite redni broj studenta kog zelite da izmijenite: ");

            if( scanf("%d", &izmjena)!=1) //UKOLIKO SE UNESE NENUMERICKI KARATKER
            {
                printf("\nOpcja koju ste izabrali nije validna. Molimo Vas, izaberite jednu od postojecih opcija.\n");
                fflush(stdin);
            }
            else if(izmjena>(*brEl-1)) //UKOLIKO SE UNESE VECI BROJ OD BROJA STUDENATA SA SPISKA
            {
                printf("\nNa spisku ne postoji student pod navedenim rednim brojem.\n");
            }

            else
            {
                uspio=1; //ukoliko je unos ispravan, uspio-1 i izlazi se iz do-while petlje
            }
        }
        while(uspio==0);
        //KRAJ BLOKA: OSIGURAVA UNOS REDNOG BROJA STUDENTA KOG ZELIMO DA IZMIJENIMO


        //POCETAK BLOKA: OSIGURAVA UNOS ODGOVORA NA 'D', 'd', 'N' ili 'n'
        do
        {
            printf("\nDati student je %s %s %s %d . Da li zelite da izmijenite njegove podatke? [D/N] ",  student[izmjena].ime, student[izmjena].prezime, student[izmjena].brIndex, student[izmjena].ocjena);
            scanf(" %c", &odg_izmjena);

            //ukoliko je odgovor potvrdan
            if(odg_izmjena=='d' || odg_izmjena=='D')
            {
                //POCETAK BLOKA: VRTI SVE DOK SE NE IZABERE 0 ZA KRAJ
                do
                {
                    printf("\nIzmjena podataka");
                    printf("\n1. Ime studenta.");
                    printf("\n2. Prezime studenta.");
                    printf("\n3. Indeks studenta.");
                    printf("\n4. Ocjenu studenta.");
                    printf("\n0. Izlaz");

                    //POCETAK BLOKA: OSIGURAVA UNOS PROMJENE PODATAKA  0-4
                    do
                    {
                        printf("\nKoji podatak zelite da izmijenite? ");


                        if(scanf("%d", &izbor_izmjena)!=1) //UKOLIKO JE UNOS NENUMERICKI
                        {
                            printf("\nOdabir opcije koji ste unijeli nije ponudjen u meniju. Molimo Vas, izaberite validnu opciju.\n\n");
                            fflush(stdin);


                        }

                        else if(izbor_izmjena<0 || izbor_izmjena>4) //UKOLIKO ODGOVOR NIJE U TRAZENOM OPSEGU
                        {
                            printf("\nOdabir opcije koji ste unijeli nije ponudjen u meniju. Molimo Vas, izaberite validnu opciju.\n\n");
                        }
                        else //UKOLIKO JE ODGOVOR KOREKTAN
                        {
                            switch(izbor_izmjena)
                            {
                            case 1:
                            {
                                printf("\nUnesite novo ime studenta: ");
                                scanf("%s", student[izmjena].ime);

                                ime=strlen(student[izmjena].ime); //U PROMJENLJIVU IME SE SMJESTA DUZINA STRINGA
                                //STAVLJA VELIKO POCETNO SLOVO
                                if(student[izmjena].ime[0]>=97 && student[izmjena].ime[0]<=122)
                                {
                                    student[izmjena].ime[0]=student[izmjena].ime[0]-32;
                                }
                                //SVA SLOVA OSIM POCETNOG PRETVARA U MALA
                                for(int i=1; i<=ime; i++)
                                {
                                    if(student[izmjena].ime[i]>=65 && student[izmjena].ime[i]<=90)
                                    {
                                        student[izmjena].ime[i]=student[izmjena].ime[i]+32;
                                    }

                                }

                                system("cls");
                                printf("\nPodaci o studentu uspjesno izmijenjeni.\n");
                                break;
                            }
                            case 2:
                            {
                                printf("\nUnesite novo prezime studenta: ");
                                scanf("%s", student[izmjena].prezime);
                                prezime=strlen(student[izmjena].prezime); //U PROMJENLJIVU PREZIME SE SMJESTA DUZINA STRINGA
                                //STAVLJA VELIKO POCETNO SLOVO
                                if(student[izmjena].prezime[0]>=97 && student[izmjena].prezime[0]<=122)
                                {
                                    student[izmjena].prezime[0]=student[izmjena].prezime[0]-32;
                                }
                                //SVA SLOVA OSIM POCETNOG PRETVARA U MALA
                                for(int i=1; i<=prezime; i++)
                                {
                                    if(student[izmjena].prezime[i]>=65 && student[izmjena].prezime[i]<=90)
                                    {
                                        student[izmjena].prezime[i]=student[izmjena].prezime[i]+32;
                                    }

                                }
                                system("cls");
                                printf("\nPodaci o studentu uspjesno izmijenjeni.\n");
                                break;
                            }
                            case 3:
                            {
                                //POCETAK BLOKA: OSIGURAVA UNOS INDEKSA U ODGOVARAJUCEM FORMATU
                                do
                                {
                                    printf("\nUnesite novi indeks studenta[MHXX/YYYY]: ");

                                    scanf("%s", student[izmjena].brIndex);

                                    if(student[izmjena].brIndex[0]!='M' || student[izmjena].brIndex[1]!='H' || student[izmjena].brIndex[4]!='/'
                                            || (student[izmjena].brIndex[2]<48 || student[izmjena].brIndex[2]>57)
                                            || (student[izmjena].brIndex[3]<48 || student[izmjena].brIndex[3]>57)
                                            || (student[izmjena].brIndex[5]<48 || student[izmjena].brIndex[5]>57)
                                            || (student[izmjena].brIndex[6]<48 || student[izmjena].brIndex[6]>57)
                                            || (student[izmjena].brIndex[7]<48 || student[izmjena].brIndex[7]>57)
                                            || (student[izmjena].brIndex[8]<48 || student[izmjena].brIndex[8]>57) )
                                    {
                                        printf("\nMolimo Vas, unesite broj indeksa u odgovarajucem formatu.\n");
                                    }

                                }
                                while(student[izmjena].brIndex[0]!='M' || student[izmjena].brIndex[1]!='H' || student[izmjena].brIndex[4]!='/'
                                        || (student[izmjena].brIndex[2]<48 || student[izmjena].brIndex[2]>57)
                                        || (student[izmjena].brIndex[3]<48 || student[izmjena].brIndex[3]>57)
                                        || (student[izmjena].brIndex[5]<48 || student[izmjena].brIndex[5]>57)
                                        || (student[izmjena].brIndex[6]<48 || student[izmjena].brIndex[6]>57)
                                        || (student[izmjena].brIndex[7]<48 || student[izmjena].brIndex[7]>57)
                                        || (student[izmjena].brIndex[8]<48 || student[izmjena].brIndex[8]>57) );

                                //KRAJ BLOKA: OSIGURAVA UNOS INDEKSA U ODGOVARAJUCEM FORMATU
                                system("cls");
                                printf("\nPodaci o studentu uspjesno izmijenjeni.\n");
                                break;
                            }
                            case 4:
                            {
                                //   POCETAK BLOKA: OSIGURAVA UNOS OCJENE 5-10
                                do
                                {

                                    printf("\nUnesite novu ocjenu studenta: ");
                                    fflush(stdin);
                                    if (scanf("%d", &student[izmjena].ocjena) != 1) //UKOLIKO SE UNESE NENUMERICKI KARAKTER
                                    {
                                        printf("GRESKA: Uneta vrednost nije broj!\n");
                                        fflush(stdin);  // ukloni neispravnu vrednost
                                    }
                                    else if(student[izmjena].ocjena<5 || student[izmjena].ocjena>10)
                                    {
                                        printf("\nMolimo Vas, unesite ocjenu od 5 do 10.\n");
                                    }
                                    else
                                    {
                                        uspio2 = 1; //AKO JE UNOS KOREKTAN, uspio2=1 I IZLAZI SE IZ do-while PETLJE
                                    }

                                }
                                while (uspio2 == 0);

                                //KRAJ BLOKA: OSIGURAVA UNOS OCJENE OD 5-10

                                system("cls");
                                printf("\nPodaci o studentu uspjesno izmijenjeni.\n");
                                break;
                            }
                            }
                            uspio3=1; //ukoliko je odgovor koji podatak zelimo da mijenjamo tacan, uspio3=1 i izlazi se iz do-while petlje
                        }

                    }
                    while(uspio3==0);   //KRAJ BLOKA: OSIGURAVA UNOS PROMJENE PODATAKA  0-4

                }
                while(izbor_izmjena!=0);  //KRAJ BLOKA: VRTI SVE DOK SE NE IZABERE 0 ZA KRAJ


                uspio1=1; //unijet je pravilan odgovor('d' lil 'D'), te se izlazi iz do-while petlje
            }
            //kraj slucaja kada je unos potvrdan

            //slucaj kada je unos odrican
            else if(odg_izmjena=='n' || odg_izmjena=='N')
            {
                printf("\nPodaci o studentu nece biti izmijenjeni.\n\n");
                uspio1=1; //unijet je pravilan odgovor('n' lil 'N'), te se izlazi iz do-while petlje

            }

            //ukoliko nije uneseno ni 'd' ni 'n'
            else
            {
                printf("\nMolimo Vas, unesite validan odgovor.\n");
            }

        }
        while(uspio1==0);
        //KRAJ BLOKA: OSIGURAVA UNOS ODGOVORA NA 'D', 'd', 'N' ili 'n'
    }
    //kraj if-else, slucaj else, odnosno  slucaj ukoliko spisak nije prazan


}

void pretragaStudenta(TStudent* student, int *brEl)
{
    char index[20]; //indeks po kome se trazi student
    int nije_pronadjen=0;
    system("cls");
    printf("\n\n\------------------------------------------- PRETRAGA STUDENTA -------------------------------------------");

    printf("\n\n*NAPOMENA: Podatke o studentima koji su vec sacuvani u datoteci nije moguce pretrazivati.\n");

    //POCETAK BLOKA: OSIGURAVA UNOS INDEKSA U ODGOVARAJUCEM FORMATU
    do
    {
        printf("\nUnesite indeks kako biste pronasli odgovarajuceg studenta [MHXX/YYYY]: ");
        scanf("%s", index);

        if(index[0]!='M' || index[1]!='H' || index[4]!='/'
                || (index[2]<48 || index[2]>57)
                || (index[3]<48 ||index[3]>57)
                || (index[5]<48 || index[5]>57)
                || (index[6]<48 || index[6]>57)
                || (index[7]<48 || index[7]>57)
                || (index[8]<48 || index[8]>57) )
        {
            printf("\nMolimo Vas, unesite broj indeksa u odgovarajucem formatu.\n");
        }

    }
    while(index[0]!='M' || index[1]!='H' || index[4]!='/'
            || (index[2]<48 || index[2]>57)
            || (index[3]<48 ||index[3]>57)
            || (index[5]<48 || index[5]>57)
            || (index[6]<48 || index[6]>57)
            || (index[7]<48 || index[7]>57)
            || (index[8]<48 || index[8]>57) );

    //KRAJ BLOKA: OSIGURAVA UNOS INDEKSA U ODGOVARAJUCEM FORMATU
    for(int i=0; i<*brEl; i++)
    {
        if(strcmp(index, student[i].brIndex)==0)
        {
            printf("\nTrazeni student je: %s %s %s %d\n", student[i].ime, student[i].prezime, student[i].brIndex, student[i].ocjena);
            nije_pronadjen=1; //kada je student pronadjen, mijenja vrijednost nije_pronadjen=1 , kako ne bi usao u naredni if slucaj
        }
    }
    if(nije_pronadjen==0) //vrijednost dodijeljena pri inicijalizaciji, ALI ukoliko se student pronadje, vr se mijenja, pa se ovaj blok nece izvrsiti
    {
        printf("\nStudent sa trazenim indeksom ne postoji na spisku.\n");
    }

}


void brisanjeStudenta(TStudent* student, int *brEl)
{
    int brisanje; //rednu broj studenta kog korisnik zeli da obrise
    char odg_brisanje; //potvrda brisanja
    int uspio=0,uspio1=0; //osiguravaju korektan unos korisnika
    system("cls");
    //UKOLIKO JE SPISAK PRAZAN
    if(*brEl==0)
    {
        printf("\n\nSpisak sadrzi %d studenata. Nema podataka koje je moguce izbrisati.\n ", *brEl);
    }
    //UKOLIKO POSTOJI BAR 1 STUDENT NA SPISKU
    else
    {
        //POCETAK BLOKA: ZASTITA UNOSA REDNOG BROJA STUDENTA SA SPISKA
        do
        {
            printf("\n------------------------------------------- BRISANJE STUDENTA -------------------------------------------");
            printf("\n\n*NAPOMENA: Podatke o studentima koji su vec sacuvani u datoteci nije moguce izbrisati.\n");
            printf("\n\nNovi spisak sadrzi %d studenata.\n ", *brEl);
            printf("\n\nUnesite redni broj studenta kog zelite da izbrisete: ");

            if(scanf("%d", &brisanje)!=1) //UKOLIKO JE UNESEN NENUMERICKI KARAKTER
            {
                printf("\nOpcija koju ste unijeli nije validna.\n");
                fflush(stdin);
            }

            else if(brisanje>(*brEl-1)) //UKOLIKO SE UNESE VECI BROJ OD BROJA STUDENATA SA SPISKA
            {
                printf("\nNa spisku ne postoji student pod navedenim rednim brojem.\n");
            }
            else
            {
                uspio1=1; //UKOLIKO JE UNOS KOREKTAN, IZLAZI IZ DO-WHILE PETLJE
            }
        }
        while(uspio1==0);
        //KRAJ BLOKA: ZASTITA UNOSA REDNOG BROJA STUDENTA SA SPISKA

        printf("\nTrazeni student je: %s %s %s %d\n", student[brisanje].ime, student[brisanje].prezime, student[brisanje].brIndex, student[brisanje].ocjena);
        //POCETAK BLOKA: ZASTITA UNOSA POTVRDNOG ILI ODRICNOG ODGOVORA
        do
        {
            printf("\nDa li zelite da izbrisete datog studenta sa liste? [D/N] ");
            scanf(" %c", &odg_brisanje);
            if(odg_brisanje=='d' || odg_brisanje=='D')
            {
                for(int i=brisanje; i<(*brEl)-1; i++)
                {
                    student[i]=student[i+1];

                }
                printf("\nPodaci o studentu su uspjesno obrisani.\n");
                (*brEl)--;
                uspio=1;

            }
            else if(odg_brisanje=='n' || odg_brisanje=='N')
            {
                printf("\nPodaci o studentu nece biti izbrisani.\n");
                uspio=1;
            }

            else
            {

                printf("\nOdgovor koji ste unijeli nije validan .\n");

            }
        }
        while(uspio==0);
        //KRAJ BLOKA: ZASTITA UNOSA POTVRDNOG ILI ODRICNOG ODGOVORA

    }
    //KRAJ SLUCAJA: UKOLIKO POSTOJI BAR 1 STUDENT NA SPISKU

}

void sortinranjePoImenuPrezimenu(TStudent* student, int brEl)
{
    int i,k;
    TStudent pom;
    printf("\n---------------------------------- SORTIRANJE STUDENATA PO PREZIMENU I IMENU -------------------------------------------");
    printf("\n\n*NAPOMENA: Podatke o studentima koji su vec sacuvani u datoteci nije moguce sortirati.\n");

    do
    {
        k = 0;
        for (i = 0; i < brEl-1; i++)
        {
            if (strcmp(student[i].prezime, student[i+1].prezime) > 0 || ((strcmp(student[i].prezime, student[i+1].prezime) == 0) && (strcmp(student[i].ime, student[i+1].ime) > 0)))
            {
                pom = student[i];
                student[i] = student[i+1];
                student[i+1] = pom;
                k = 1;
            }
        }
    }
    while(k != 0);

    printf("\nNiz studenata sortiran po prezimenu i imenu!\n");
}
void sortinranjePoOcjeni(TStudent* student, int brEl)
{
    int i,k;
    TStudent pom;
    printf("\n---------------------------------- SORTIRANJE STUDENATA PO OCJENI -------------------------------------------");
    printf("\n\n*NAPOMENA: Podatke o studentima koji su vec sacuvani u datoteci nije moguce sortirati.\n");

    do
    {
        k = 0;
        for (i = 0; i < brEl-1; i++)
        {
            if (student[i].ocjena<student[i+1].ocjena)
            {
                pom= student[i];
                student[i] = student[i+1];
                student[i+1] = pom;
                k = 1;
            }
        }
    }
    while(k != 0);

    printf("\nNiz studenata sortiran po ocjeni!\n");
}




