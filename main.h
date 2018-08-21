/*
*/
//---------------------------------------------------------------------------

#ifndef MAINH
#define MAINH

//--Define's-----------------------------------------------------------------

//--Include's----------------------------------------------------------------
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#include "resource.h"

//--Define's-----------------------------------------------------------------
#define MAX_PROGS 16

//--Macro Define's-----------------------------------------------------------

//--Class Define's-----------------------------------------------------------
class trie {
  private:
    trie *parent;
    trie *childs[26];
    int ichr;
    int depth;
    bool end;
  public:
    trie(trie *p, int ic, int d);
    ~trie();
    void add(int *ilist);
    bool known(int *ilist);
    int  knownn(int **ilist, int length);
    void print(char *buf);
    int load_from_file(char *filename);
};

class bord {
  public:
    int ichrs[49];
    int ispeler[49];
    int *iver[7][7];
    int *ihor[7][7];
    int eindscore;
    bord(void);
    void clear(void);
    bool doe_zet(int t, int ichr, int speler);
    bool vol(void);
    void print(int speler);
    void fprint(FILE *fout, int speler);
    int regelwaarde(int *iline[7]);
    int waarde(void);
};

//--Struct Define's----------------------------------------------------------
struct SPELINFO
{
  char speler1path[MAX_PATH];
  char speler2path[MAX_PATH];
  char beginletter;
  int  speler1, punten1;
  int  speler2, punten2;
};

struct SPELERINFO
{
  HANDLE Process;
  HANDLE Stdin;
  HANDLE Stdout;
  HANDLE Stderr;
};

//--External Vars------------------------------------------------------------
extern int  Winst[MAX_PROGS][MAX_PROGS];
extern int  Verlies[MAX_PROGS][MAX_PROGS];
extern int  Gelijk[MAX_PROGS][MAX_PROGS];
extern char ProgPath[MAX_PROGS][MAX_PATH];
extern char WbPath[MAX_PATH];
extern char BlPath[MAX_PATH];
extern char LgPath[MAX_PATH];
extern int  AantalProgs;
extern int  SwitchWBmode;
extern int  SwitchBLmode;
extern int  SwitchLGmode;
extern char Letters[28];
extern FILE *fbordlog;
extern trie wb;

//--Functions----------------------------------------------------------------
int ScanParam(int argc, char **argv);
int Speel(SPELINFO *si);
int Waardeer(SPELINFO *si);
int fprint_waarde(FILE *fout);

#endif
