/*
*/
//---------------------------------------------------------------------------

//--Include's----------------------------------------------------------------
#include "main.h"

//--Define's-----------------------------------------------------------------

//--Struct Define's----------------------------------------------------------
 
//--Vars---------------------------------------------------------------------

//--Functions----------------------------------------------------------------
int Waardeer(SPELINFO *si)
{
  if (si->punten1>si->punten2)
  {
    ++Winst[si->speler1][si->speler2];
    ++Verlies[si->speler2][si->speler1];
  }
  if (si->punten1<si->punten2)
  {
    ++Winst[si->speler2][si->speler1];
    ++Verlies[si->speler1][si->speler2];
  }
  if (si->punten1==si->punten2)
  {
    ++Gelijk[si->speler1][si->speler2];
    ++Gelijk[si->speler2][si->speler1];
  }
  return 0;
}

char *strpad(int i)
{
  static char pad[MAX_PATH];

  memset(pad, ' ', i);
  pad[i]=NULL;

  return pad;
}

int fprint_waarde(FILE *fout)
{
  int i, j, maxlen=0;
  int nwinst, nverlies, ngelijk;

  if (fout==NULL) return 1;

  for (i=0; i<AantalProgs; ++i)
  {
    if ((int)strlen(ProgPath[i])>maxlen)
      maxlen=strlen(ProgPath[i]);
  }

  fprintf(fout, "\n%s      ", strpad(maxlen));
  for (j=0; j<AantalProgs; ++j)
    fprintf(fout, "     [%2d] ", j+1);
  fprintf(fout, "\n");


  for (i=0; i<AantalProgs; ++i)
  {
    fprintf(fout, "%s%s [%2d]:", strpad(maxlen-strlen(ProgPath[i])),
            ProgPath[i], i+1);

    nwinst=0; nverlies=0;

    for (j=0; j<AantalProgs; ++j)
    {
      fprintf(fout, " %2d <> %2d ", Winst[i][j], Verlies[i][j]);
      nwinst+=Winst[i][j]; nverlies+=Verlies[i][j];
    }
    fprintf(fout, "\n%s     :", strpad(maxlen));

    ngelijk=0;
    for (j=0; j<AantalProgs; ++j)
    {
      fprintf(fout, "    %2d    ", Gelijk[i][j]);
      ngelijk+=Gelijk[i][j];
    }

    fprintf(fout, "\nw: %3d; v: %3d; g: %3d\n",
            nwinst, nverlies, ngelijk);
  } 
 
  fprintf(fout, "\n-------------------"
                "------------------\n");

  return 0;
}


