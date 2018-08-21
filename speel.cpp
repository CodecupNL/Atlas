/*
*/
//---------------------------------------------------------------------------

//--Include's----------------------------------------------------------------
#include "main.h"

//--Define's-----------------------------------------------------------------

//--Struct Define's----------------------------------------------------------
 
//--Vars---------------------------------------------------------------------
bord bord[2];

//--Functions----------------------------------------------------------------
int ProcessAlive(HANDLE p)
{
  DWORD e;
  GetExitCodeProcess(p, &e);
  MessageBox(NULL, (e == STILL_ACTIVE)?"Still Alive":"Died", "Process Info", MB_OK);
  return 0;  
}

HANDLE ForkChildProcess(TCHAR *cmd, PHANDLE inH, PHANDLE outH, PHANDLE errH) 
{ 
  STARTUPINFO         si; 
  PROCESS_INFORMATION pi; 
  SECURITY_ATTRIBUTES lsa; 

  HANDLE ChildIn; 
  HANDLE ChildOut; 
  HANDLE ChildErr; 

  lsa.nLength=sizeof(SECURITY_ATTRIBUTES); 
  lsa.lpSecurityDescriptor=NULL; 
  lsa.bInheritHandle=TRUE; 

  //Create Parent_Write to ChildStdIn Pipe 
  if (!CreatePipe(&ChildIn, inH, &lsa, 0)) 
    return NULL; 

  //Create ChildStdOut to Parent_Read pipe 
  if (!CreatePipe(outH, &ChildOut, &lsa, 0)) 
    return NULL;

  //Create ChildStdErr to Parent_Read pipe 
  if (!CreatePipe(errH, &ChildErr, &lsa, 0))
    return NULL;

  // Lets Redirect Console StdHandles - easy enough
  memset(&si, 0, sizeof(STARTUPINFO));
  si.cb=sizeof(STARTUPINFO); 
  si.dwFlags=STARTF_USESTDHANDLES|STARTF_USESHOWWINDOW; 
  si.hStdInput =ChildIn;
  si.hStdOutput=ChildOut;
  si.hStdError =ChildErr;
  si.wShowWindow=SW_HIDE;

  //Create Child Process 
  if (!CreateProcess(NULL, cmd, NULL, NULL, TRUE,
                     NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE,
                     NULL, NULL, &si, &pi)) 
    return NULL;

  CloseHandle(ChildIn); 
  CloseHandle(ChildOut); 
  CloseHandle(ChildErr);

  return pi.hProcess; 
}

int ReadStdout(HANDLE out, char *buffer, int *buflen)
{
  DWORD bytesread;
  int   intr=*buflen;

  buffer[*buflen]=NULL;
  if (!ReadFile(out, &buffer[*buflen],
                32-*buflen, &bytesread, NULL))
    return 0;
  *buflen += bytesread;
  buffer[*buflen] = NULL;

  return 1;
}

int WriteStdin(HANDLE in, char *format, ...)
{
  va_list arg;
  char    string[256];
  DWORD   bytestowrite;

  va_start(arg, format);
  vsprintf(string, format, arg);
  va_end(arg);
 
  bytestowrite = strlen(string);
  WriteFile(in, string, bytestowrite, &bytestowrite, NULL);

  return 0;
}

int Speel(SPELINFO *si)
{
  SPELERINFO speler[2];

  char letter, vletter;
  int  b, ronde, buflen;
  int  plek, plaats;
  char buffer[40];

//  MessageBox(NULL, si->speler1cmd, si->speler2cmd, MB_OK);
  
  // Fork speler1
  speler[0].Process = ForkChildProcess(si->speler1path, &speler[0].Stdin,
                                       &speler[0].Stdout, &speler[0].Stderr);
  if (speler[0].Process==NULL) return 0;

  // Fork speler2
  speler[1].Process = ForkChildProcess(si->speler2path, &speler[1].Stdin,
                                       &speler[1].Stdout, &speler[1].Stderr);
  if (speler[1].Process==NULL) return 0;

  letter=si->beginletter;
  bord[0].clear(); bord[0].doe_zet(24, letter-'A', -1);
  bord[1].clear(); bord[1].doe_zet(24, letter-'A', -1);

  b = 0;
  WriteStdin(speler[b].Stdin, "%c\n", letter);
  WriteStdin(speler[!b].Stdin, "%c\n", letter);
  WriteStdin(speler[b].Stdin, "start\n");

  buflen = 0;
  while (ReadStdout(speler[b].Stdout, buffer, &buflen))
  { if (sscanf(buffer, "%1s %d", &letter, &plaats) == 2) break; }

  for (ronde=1; ronde<49; ++ronde)
  {
    //printf("\t\tletter: %c\n", letter);
    //printf("\t\tplaats: %d\n", plaats);
    bord[b].doe_zet(plaats, letter-'A', b);
    
    b=(b)?0:1;
    WriteStdin(speler[b].Stdin, "%c\n", letter);
    vletter=letter;

    buflen=0;
    while (ReadStdout(speler[b].Stdout, buffer, &buflen))
    {
      if (sscanf(buffer, (ronde==48)?"%d":"%d%1s%d",
          &plek, &letter, &plaats) == ((ronde==48)?1:3)) break;
    }

    bord[b].doe_zet(plek, vletter-'A', !b);

    //printf("\t\t  plek: %d\n",  plek);
  }

  si->punten1=bord[0].waarde();
  si->punten2=bord[1].waarde();

  if (fbordlog!=NULL)
  {
    fprintf(fbordlog, "speler1: %s\n", si->speler1path);
    bord[0].fprint(fbordlog, 0);
    fprintf(fbordlog, "waarde: %5d\n\n", si->punten1);
    fprintf(fbordlog, "speler2: %s\n", si->speler2path);
    bord[1].fprint(fbordlog, 1);
    fprintf(fbordlog, "waarde: %5d\n\n", si->punten2);
    fprintf(fbordlog, "-------------------"
            "------------------\n\n");
  }

  TerminateProcess(speler[0].Process, 0);
  TerminateProcess(speler[1].Process, 0);
  
  return 0;
}
