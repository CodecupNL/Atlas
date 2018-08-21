/*
*/
//---------------------------------------------------------------------------

//--Include's----------------------------------------------------------------
#include "main.h"

//--Define's-----------------------------------------------------------------

//--Struct Define's----------------------------------------------------------
 
//--Vars---------------------------------------------------------------------
FILE *fbordlog;
FILE *fspellog;
int   Winst[MAX_PROGS][MAX_PROGS];
int   Verlies[MAX_PROGS][MAX_PROGS];
int   Gelijk[MAX_PROGS][MAX_PROGS];
char  BordlogPath[MAX_PATH];

//--Functions----------------------------------------------------------------
int main(int argc, char **argv)
{
  int i, letter;
  int spel, maxspel;
  SPELINFO si;

  if (!ScanParam(argc, argv))
  {
    return 1;
  }

  if (SwitchWBmode && !wb.load_from_file(WbPath))
    return 1;

  spel=0;
  maxspel=AantalProgs*(AantalProgs-1)*strlen(Letters);

  printf("%d deelnemers gevonden:\n", AantalProgs);
  for (i=0; i<AantalProgs; ++i)
    printf("- %s\n", ProgPath[i]);
  printf("\n");

  for (si.speler1=0; si.speler1<AantalProgs; ++si.speler1)
  {
    for (si.speler2=0; si.speler2<AantalProgs; ++si.speler2)
    {
      for (letter=0; letter<(int)strlen(Letters); ++letter)
      {
        if (si.speler1==si.speler2) continue;

        printf("Bezig met spel: %5d/%d\r", ++spel, maxspel);

        strcpy(si.speler1path, ProgPath[si.speler1]);
        strcpy(si.speler2path, ProgPath[si.speler2]);
        si.beginletter=Letters[letter];

        if (SwitchBLmode)
        {
          sprintf(BordlogPath, "%s\\%.2d-VS-%.2d.txt",
                  BlPath, si.speler1+1, si.speler2+1);
          fbordlog = fopen(BordlogPath, "a");
        }

        Speel(&si);

        if (fbordlog!=NULL)
        {
          fclose(fbordlog);
          fbordlog=NULL;
        }

        Waardeer(&si);
      }
    }
  }
  
  printf("\n");

  if (SwitchLGmode)
  {
    fspellog=fopen(LgPath, "a");
    fprint_waarde(fspellog);
    fclose(fspellog);
  }

  return 0;
}