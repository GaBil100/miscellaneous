/*Gareth,Bilaney*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>





int inlineSubtraction(int a,int b);
int inlineAddition(int a, int b);

int cmpfunc (const void * a, const void * b){
return ( *(int*)a - *(int*)b );}



/*  +++++++++++++++++++MAIN++++++++++++++++++++++ */

int main(int argc,char** argv)
{
int k, p,z,l,t,nxtf,s,inc, n,fir,f, no, ac;
register int i, j;

/*  +++++++++++++++++++DEFINITIONEN++++++++++++++++++++++ */
inc=1;

j=i=n=p=k=nxtf=no=fir=0;
ac=48;


/*  +++++++++++++++++++FUNKTIONEN++++++++++++++++++++++ */

/* Inline-ASM Funktionen für Subtraction und Addition */

int inlineSubtraction(int a, int b) //Einlesen von Integer "a" und "b"
{
__asm__
(
"subl %%ebx, %%eax;"      // eax-ebx, sprich a-b
: "=a" (a)               // Output eax=a. Sprich a-b=a
: "a" (a), "b" (b)       //"a" in Register eax und "b" in ebx
);
return a;                //Ausgabe von a
}

/*analog für InlineAddition */

int inlineAddition(int a, int b) 
{
__asm__
(
"addl %%ebx, %%eax;"
: "=a" (a)
: "a" (a), "b" (b)
);
return a;
}
/*  +++++++++++++++++++Anzahl der Felder++++++++++++++++++++++ */

/* Für die korrekte Reservierung durch Malloc benötigt man die Anzahl der Felder. Erste Zeile soll "n" Arrays und die zweite Zeile soll "k" Felder enthalten */ 

char temp1;


FILE *fp;
fp = fopen(argv[1], "r");

while((temp1 = getc(fp))!=EOF)
{

if((temp1==32||temp1==10)&&(no==0))  /*sobald ein Lehrzeichen erscheint, wird durch ASCII "32" im temp signalisiert, dass ein neues Feld belegt wird. 
                                       no==0 steht für die auktelle, erste Zeile */
{
n++;                                /*diese Felder werden durch Inkrementierung gezählt.*/
}
if((temp1==32)&&(no==1))            /*Analog für "k", stehend für die Anzahl der Felder in der ersten Zeile */ 
{
k++;
}
if(temp1==10)                      /*mit temp==10 wird signalisiert, dass eine neue Zeile beginnt. "no" wird inkrementiert.*/
{
no++;
if(no==2)                         /*Bei no==2 (von 0-3), wird signalisiert, dass eine dritte Zeile (leer oder nicht leer) vorhanden ist. Eine Fehlermeldung
                                    erscheint*/
{
fprintf(stderr,"Error: Es sind exakt 2 Zeilen erlaubt." );
return EXIT_FAILURE;
}
}
}

fclose(fp);
k++;                              /*Das letzte Feld kann nicht gezählt werden, da am Ende der Datei EOF steht. Also mussnach dem Prozess 
                                   k einmalig inkrementiert werden */





/*  +++++++++++++++++++REDEFINE++++++++++++++++++++++ */

/*Mit der Anzhal der Felder, kann der Speicher reserviert werden. Die zweite Zeile wird noch Mal aufgeteilt. 
Einmal in Müllbox-Größe "g" und Fitverfahren (ff, bf..etc) in "g_m"*/

int *c =(int*)malloc(n*(sizeof(*c))); 
int *g =(int*)malloc(k*(sizeof(*g))); 
int *g_m =(int*)malloc(k*(sizeof(*g_m))); 



char temp;
int tomp;
no=n=k=fir=0;

/*  +++++++++++++++++++ CHECK 2++++++++++++++++++++++ */
FILE *fp1;
fp1 = fopen(argv[1], "r");

if(fp1 == NULL) {
printf("Datei konnte nicht geoeffnet werden.\n");
}else {
while((temp = getc(fp1))!=EOF)


{

/* LINE ONE */

/*Damit die Container-Größen korrekt gespeichert werden, werden die ASCII-Werte gespeichert und mit 48 Subtrahiert. Bei weiteren Stellen, wird c[i], wobei i der aktuelle Container ist, mit 10 multipliziert. Anschließend wird der nächste ASCII-Wert (sofern es sich um eine Zahl handelt), auf c[i] addiert, nachdem dieser Wert mit 48 subtrahiert wurde. Bei temp==32, wird i inkremtiert und der Algorithmus zurückgesetzt. "fir" singalisiert, ob es sich um die erste Stelle der Zahl handelt, die auf c[i] gespeichert wird. Erst ab fir==1, wird c[i], sofern weitere Stellen eingelesen werden, mit 10 multipliziert. */

if((fir==1)&&(no==0)&&(temp!=32)&&(temp!=10))  // C einlesen 
{
tomp = inlineSubtraction(temp, ac);
c[n]=c[n]*10;
tomp = inlineSubtraction(temp, ac);
c[n]= inlineAddition(c[n], tomp);
}

else if((fir==0)&&(no==0)&&(temp!=32)&&(temp!=10))
{
c[n]=temp;
c[n]= inlineSubtraction(c[n], ac);
fir=1;
}

else if((temp==32||temp==10)&&(no==0))
{
n++;
fir=0;
}

/* ERROR: Sobald ein ASCII-Wert eingelesen wird, der nicht eine Zahl, new-line oder Leerzeichen darstellt, wird das Programm abgebrochen. */

if((no==0)&&(temp<48||temp>57)&&(temp!=10)&&(temp!=32))
{
fprintf(stderr,"Error: Ungueltige Zeichen, oder negative Zahlen vorhande." );
free(c);
free(g);
free(g_m);
return EXIT_FAILURE;
}

/* Etwas aufwendiger, aber im Prinzip dieselbe Funktionsweise, wird erst unteschieden, ob auf g[i], oder g_m[i] ("i" stehe nachwievor für das aktuelle Array) temp gespeichert und verarbeitet werden soll. g_m soll ausschließlich mindestens einen Nicht-Nummerischen Charakter (0-9) enthalten. Sollte g_m nicht die Adresse für "ff", "bf", etc darstellen, wird das Programm abgebrochen. g_m wird mit 1000 multipliziert, da seine einzulesenden charakter 3 Stellen enthalten. Bsp f==102, laut ASCII. je nachdem, ob die Fit-Befehle, oder Müllbox-Größen eingelesen werden, werden die nicht aktiven Arrays gleich Null gesetzt. */

if((fir==1)&&(no==1)&&(temp!=32)&&(temp!=10)&&(temp<48||temp>57))  /* g_m wird verarbeitet. Die erste Stelle wurde bereits gespeichert. */
{
g_m[k]=g_m[k]*1000;
g_m[k] = inlineAddition(g_m[k], temp);
}
else if((fir==1)&&(no==1)&&(temp!=32)&&(temp!=10)&&(temp>47)&&(temp<58))  /*g wird verarbeitet. Die erste Stelle wurde bereits gespeichert.*/
{
g[k]=g[k]*10;
tomp = inlineSubtraction(temp, ac);
g[k] = inlineAddition(g[k], tomp);
}


if((fir==0)&&(no==1)&&(temp<48||temp>57)) /* Erste Stelle g_m */
{
g_m[k]=temp;
g[k]=0;
fir=1;

}
else if((fir==0)&&(no==1)&&(temp>47)&&(temp<58))  /* Erste Stelle g */
{
g_m[k]=0;


g[k] = inlineSubtraction(temp, ac);
fir=1;
}

if((temp==32)&&(no==1))                           /* bei Leerzeichen wird k inkrementiert, damit das nächste Feld verabeitet wird. Der Algorithmus wird zurückgesetzt. */
{

if(g_m[k]==102102||g_m[k]==98102||g_m[k]==97119102||g_m[k]==110102||g_m[k]==0)   
/* Alle auffälligen Charakte werden in g_m gespeichert. Sobald g_m nicht die Fit-Befele enthält, oder gleich Null ist, wird das Programm abgebrochen */
{
k++;
fir=0;
}
else
{
fprintf(stderr,"Error: Ungueltige Zeichen, oder negative Zahlen vorhande." );
free(c);
free(g);
free(g_m);
return EXIT_FAILURE;
}



}

if(temp==10)  /*nächste Zeile*/
{
no++;
fir=0;
}


}
fclose(fp1);
}
k++;



/*  +++++++++++++++++++ Zeiger und Box auf Standart++++++++++++++++++++++ */


/*Auf "v" werden die Container-Größen kopiert. v wird anschließend mit der Quick-Sort-Funktion sortiert. "y" signalisiert mit "-1", ob ein Container leer ist. Mit y2 wird angeben, in welchem Container, die Müllbox sortiert wird. */

int *v =(int*)malloc(n*(sizeof(*v))); 
int *y =(int*)malloc(n*(sizeof(*y))); 
int *y2 =(int*)malloc(k*(sizeof(*y2))); 




for(i=0;i<n;i++) //Standart: Empty Container
{
y[i]=-1;
}

for(i=0;i<k;i++) //Standart: Empty Box
{
y2[i]=-1;
}






/*  ********************************** FIT FIT ***************************** */

/* Im zweiten Teil des Programms, werden die Müllboxen nach den vorgegebenen Fit-Verfahren sortiert. Dies geschieht innerhalb einer Schleife, in der alle Müllboxen überprüft werden, in welchem Container - sofern ausreichen Platz vorhanden ist - sortiert werden */

int blanc = 102102;   /*standart ist First Fit, falls  kein Fit-Befehl angeben wurde */


for(f=0;f<k;f++)
{



/*blanc steht für die aktuelle, zu benutztende Strategie */

if(g_m[f]==102102)
{blanc = 102102;}              /*First Fit*/
else if(g_m[f]==98102)
{blanc =98102;}                /*Best Fit*/
else if(g_m[f]==97119102)
{blanc =97119102;}             /*AWF*/
else if(g_m[f]==110102) 
{blanc =110102;}               /*Next Fit*/
else
{blanc =blanc;}


/*  ********** Sort Container FIT ***************** */


/* Falls nötig, wird v nach der Größe sortiert. Dies ist bei bf, awf und nf wichtig. Da die Laufzeit mit der Funktion beeinträchtigt wird, wird im Programm versucht, diese so selten, wie nötig aufzurufen */

if(g_m[f]==98102||blanc==97119102||blanc==110102)
{
for(i=0;i<n;i++)
{
v[i]=c[i];																																		
}
qsort(v,n,sizeof(int),cmpfunc);
}




/*  ********** FIRST FIT ***************** */



if((blanc==102102)&&(g[f]!=0))
{
i=0;
while((y2[f]==-1)&&(g[f]!=0))
{

// check
if((i==n-1)&&(c[n-1]<g[f]))  /*Falls kein Container gefunden wird, der ausreichen Platz für die Müllbox hat, wird das Programm abgebrochen */
{
fprintf(stdout,"validation failed" );
free(c);
free(y);
free(g);
free(g_m);
free(v);
free(y2);
return EXIT_FAILURE;
}

if (c[i]>=g[f])           /* falls ausreichend, wird für g[f], auf  y2[f]==i markiert und anschließend im letzten Abschnitt einsortiert */
{

y2[f]=i;
y[i]=-2;
c[i] = inlineSubtraction(c[i], g[f]);
nxtf=i;                       /* Falls Next Fit aufgerufen wird, wird der aktuelle Container auf nxtf gespeichert */
}
i++;
}
}




/*  ********** BEST FIT ***************** */

/* Bei Best-Firt, wird von i bis (n-1) ein freies Array v[i] gesucht, das nach Aufruf "bf" der Größe sortiert wurde. Nachdem ein freies Array gefunden wurde, wird das erste Array c[j] gesucht, das dieselbe Größe von v[i] hat. Wie bei "ff" wird y2[f]=j; dann markiert. y[i]=-2 signalisiert, dass Container_i nicht leer ist. */


else if((blanc==98102)&&(g[f]!=0))
{
i=0;
while(y2[f]==-1)
{

if((i==n-1)&&(v[i]<g[f]))
{
fprintf(stdout,"validation failed" );
free(c);
free(y);
free(g);
free(g_m);
free(v);
free(y2);
return EXIT_FAILURE;
}


if (v[i]>=g[f])
{
j=0;
while(y2[f]==-1)
{

if (v[i]==c[j])
{
y2[f]=j;
y[j]=-2;
c[j] = inlineSubtraction(c[j], g[f]);
v[i] = inlineSubtraction(v[i], g[f]);


for(s=i;s>0;s--)  /* Da Quick-Sort bei vielen Daten leicht überlastet, werden nur die Stellen ab s=i bis s=0 sortiert, statt alle Arrays zu sortieren */
{

if(v[s]<v[s-1])
{
temp=v[s];
v[s]=v[s-1];
v[s-1]=temp;
}



}


nxtf=j;
}

j++;
}
}
i++;
}
}




/*  ********** Worst FIT ***************** */

/* V[i] wird wieder nach der Größe Sortiert. Falls v[n-2], das zweit größte Array, kein Platz bietet, wird g[k] auf v[n-1] markiert. 
Wie bei "bf" wird c[i] gesucht und ein Marker auf y2[f]=i gesetzt */


else if((blanc==97119102)&&(g[f]!=0))
{

if(v[n-1]<g[f])
{
fprintf(stdout,"validation failed" );
free(c);
free(y);
free(g);
free(g_m);
free(v);
free(y2);
return EXIT_FAILURE;
}



if(g[f]<=v[n-2])
{
i=0;
while((y2[f]==-1)&&(g[f]!=0))
{
if(c[i]==v[n-2])
{
y2[f]=i;
y[i]=-2;
c[i] = inlineSubtraction(c[i], g[f]);
nxtf=i;
}
i++;
}
}

else if(g[f]<=v[n-1])
{
i=0;
while((y2[f]==-1)&&(g[f]!=0))
{

if(c[i]==v[n-1])
{
y2[f]=i;
y[i]=-2;
c[i] = inlineSubtraction(c[i], g[f]);
nxtf=i;
}
i++;
}
}


}



/*  ********** NEXT FIT ***************** */

/* nxtf ist standartmäßig gleich null, oder, falls ein Container bereits befüllt wurde, dann gilt: nxtf= container_i. Wie in der 
Aufgabenstellung werden die Boxen nach nxtf = (nxtf+1)%(n) einsortiert, falls nxtf=i oder nxtf=0 keinen Platz bieten. Falls v[n-1]<g[f], dann wird das Programm abgebrochen. */


else if((blanc==110102)&&(g[f]!=0))
{

if(v[n-1]<g[f])
{
fprintf(stdout,"validation failed" );
free(c);
free(y);
free(g);
free(g_m);
free(v);
free(y2);
return EXIT_FAILURE;
}


	
if(c[nxtf]>=g[f])    

{
y2[f]=nxtf;
y[nxtf]=-2;

c[nxtf] = inlineSubtraction(c[nxtf], g[f]);
nxtf=nxtf;
}


else 
{

while(y2[f]==-1)
{


nxtf = (nxtf+1)%(n);

if(c[nxtf]>=g[f])
{
y2[f]=nxtf;
y[nxtf]=-2;
c[nxtf] = inlineSubtraction(c[nxtf], g[f]);
}

}

}
/*
*/

}


}

/*  ********** AUSGABE BEENDEN ***************** */

/*Nachdem alle Marker gesetzt wurden, werden die einzelnen Indizes, i bis n-1 in der Datei geschrieben, die im Pfad "argv[2]" angegeben worden ist. Anschließend werden die Müllboxen in der Datei geschrieben, die die folgende Bedingungen erfüllen: Falls y2[j]==i, dann wird g[j] in der Datei geschrieben. Falls y[i]==-1 ist, dann ist der Contaner leer, es wird also null nach dem Index i: geschrieben. */

FILE* file;
file = fopen(argv[2],"w");
for(i=0;i<n;i++)
{
fprintf(file,"%d: ",i);


if(y[i]==-2)
{
for(j=0;j<k;j++)
{
if(y2[j]==i)
{
fprintf(file," %d",g[j]);
}
}
}
else if(y[i]==-1)
{
fprintf(file," 0");
}
fprintf(file,"\n");
}	

fclose(file);


free(c);
free(g_m);
free(y);
free(y2);
free(g);
free(v);


return EXIT_SUCCESS;
}
