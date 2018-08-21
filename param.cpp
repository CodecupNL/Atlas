/*
*/
//---------------------------------------------------------------------------

//--Include's----------------------------------------------------------------
#include "main.h"

//--Define's-----------------------------------------------------------------

//--Struct Define's----------------------------------------------------------
 
//--Vars---------------------------------------------------------------------
char ProgPath[MAX_PROGS][MAX_PATH];
char WbPath[MAX_PATH];
char BlPath[MAX_PATH];
char LgPath[MAX_PATH];
int  AantalProgs = 0;
int  SwitchWBmode = 0;
int  SwitchBLmode = 0;
int  SwitchLGmode = 0;
char Letters[28] = "A";

//--Functions----------------------------------------------------------------
int IsAlpha(char *s)
{
  while (*s!=NULL)
  {
    if ((*s<'A' || *s>'Z') && *s!='-')
      return 0;
    ++s;
  }
  return 1;
}

int SetLetters(char *s)
{
  int i;
  int let[26], len;

  memset(let, 0, sizeof(let));
  
  for (i=0; *s!=NULL; ++s)
  {
    if (*s=='-') i = 1;
    else
    {
      if (!i) len = *s;
      while (len<=*s)
        let[len++-'A']=1;
      len = *s;
      i=0;
    }
  }

  for (i=0, len=0; i<26; ++i)
  {
    if (let[i]) Letters[len++]='A'+i;
  }
  Letters[len]=NULL;

  return 1;
}

int IsExe(char *s)
{
  int len=strlen(s);
  if (!strcmp(&s[len-4], ".EXE")) return 1;
  return 0;
}

char *ExtractPath(char *fullpath, char *path)
{
  int i, r=0;

  for (i=0; fullpath[i]!=NULL; ++i)
  {
    if (fullpath[i]=='\\') r=i;
  }

  strncpy(path, fullpath, ++r);

  return &path[r];
}

int AddProgs(char *s)
{
  HANDLE          hFile;
  WIN32_FIND_DATA FileData;
  int             done;

  if (AantalProgs>=MAX_PROGS) return 0;

  hFile=FindFirstFile(s, &FileData);
  if (hFile==INVALID_HANDLE_VALUE) return 0;

  done=1;
  while (done)
  {
    strcpy(ExtractPath(s, ProgPath[AantalProgs]), FileData.cFileName);
    //printf("- %s\n", ProgPath[AantalProgs]);

    ++AantalProgs;
    
    if (AantalProgs>=MAX_PROGS) return 0;

    done = FindNextFile(hFile, &FileData);
  }

  FindClose(hFile);

  return 1;
}

int ScanParam(int argc, char **argv)
{
  int   i;
  char *arg;

  AantalProgs = 0;
  memset(Winst, 0, sizeof(Winst));
  memset(Verlies, 0, sizeof(Verlies));
  memset(Gelijk, 0, sizeof(Gelijk));
  strcpy(Letters, "A");

  for (i=1; i<argc; ++i)
  {
    arg=argv[i];
    strupr(arg);
     
    if (arg[0]=='/' || arg[0]=='-')
    {
      ++arg;
      if (!strcmp(arg, "WB")) SwitchWBmode=3;
      if (!strcmp(arg, "BL")) SwitchBLmode=3;
      if (!strcmp(arg, "LG")) SwitchLGmode=3;
    }
    else if (IsExe(arg))
    {
      AddProgs(arg);
    //  printf("%s\n", arg);
    }
    else if (SwitchWBmode==2)
    {
      strcpy(WbPath, arg);
      SwitchWBmode=1;
    }
    else if (SwitchBLmode==2)
    {
      strcpy(BlPath, arg);
      SwitchBLmode=1;
    }
    else if (SwitchLGmode==2)
    {
      strcpy(LgPath, arg);
      SwitchLGmode=1;
    }
    else if (IsAlpha(arg))
    {
      SetLetters(arg);
   //   printf("%s\n", Letters);
    }

    if (SwitchWBmode>1) { --SwitchWBmode; strcpy(WbPath, "words.dat"); }
    if (SwitchBLmode>1) { --SwitchBLmode; strcpy(BlPath, "."); }
    if (SwitchLGmode>1) { --SwitchLGmode; strcpy(LgPath, "spellog.txt"); }
  }

  if (AantalProgs<2) return 0;

  return 1;
}
