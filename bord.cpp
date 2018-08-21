/*
*/
//---------------------------------------------------------------------------

//--Include's----------------------------------------------------------------
#include "main.h"

//--Define's-----------------------------------------------------------------

//--Struct Define's----------------------------------------------------------
 
//--Vars---------------------------------------------------------------------
trie wb(NULL, -1, 0);

//--Functions----------------------------------------------------------------
bord::bord(void)
{
  int i;

  for (i=0; i<49; i++) ichrs[i]=-2;

  iver[0][0]=ichrs+ 0; iver[0][1]=ichrs+ 1; iver[0][2]=ichrs+ 2; iver[0][3]=ichrs+3;
  iver[0][4]=ichrs+ 4; iver[0][5]=ichrs+ 5; iver[0][6]=ichrs+ 6;
  iver[1][0]=ichrs+ 7; iver[1][1]=ichrs+ 8; iver[1][2]=ichrs+ 9; iver[1][3]=ichrs+10;
  iver[1][4]=ichrs+11; iver[1][5]=ichrs+12; iver[1][6]=ichrs+13;
  iver[2][0]=ichrs+14; iver[2][1]=ichrs+15; iver[2][2]=ichrs+16; iver[2][3]=ichrs+17;
  iver[2][4]=ichrs+18; iver[2][5]=ichrs+19; iver[2][6]=ichrs+20;
  iver[3][0]=ichrs+21; iver[3][1]=ichrs+22; iver[3][2]=ichrs+23; iver[3][3]=ichrs+24;
  iver[3][4]=ichrs+25; iver[3][5]=ichrs+26; iver[3][6]=ichrs+27;
  iver[4][0]=ichrs+28; iver[4][1]=ichrs+29; iver[4][2]=ichrs+30; iver[4][3]=ichrs+31;
  iver[4][4]=ichrs+32; iver[4][5]=ichrs+33; iver[4][6]=ichrs+34;
  iver[5][0]=ichrs+35; iver[5][1]=ichrs+36; iver[5][2]=ichrs+37; iver[5][3]=ichrs+38;
  iver[5][4]=ichrs+39; iver[5][5]=ichrs+40; iver[5][6]=ichrs+41;
  iver[6][0]=ichrs+42; iver[6][1]=ichrs+43; iver[6][2]=ichrs+44; iver[6][3]=ichrs+45;
  iver[6][4]=ichrs+46; iver[6][5]=ichrs+47; iver[6][6]=ichrs+48;

  ihor[0][0]=ichrs+ 0; ihor[1][0]=ichrs+ 1; ihor[2][0]=ichrs+ 2; ihor[3][0]=ichrs+3;
  ihor[4][0]=ichrs+ 4; ihor[5][0]=ichrs+ 5; ihor[6][0]=ichrs+ 6;
  ihor[0][1]=ichrs+ 7; ihor[1][1]=ichrs+ 8; ihor[2][1]=ichrs+ 9; ihor[3][1]=ichrs+10;
  ihor[4][1]=ichrs+11; ihor[5][1]=ichrs+12; ihor[6][1]=ichrs+13;
  ihor[0][2]=ichrs+14; ihor[1][2]=ichrs+15; ihor[2][2]=ichrs+16; ihor[3][2]=ichrs+17;
  ihor[4][2]=ichrs+18; ihor[5][2]=ichrs+19; ihor[6][2]=ichrs+20;
  ihor[0][3]=ichrs+21; ihor[1][3]=ichrs+22; ihor[2][3]=ichrs+23; ihor[3][3]=ichrs+24;
  ihor[4][3]=ichrs+25; ihor[5][3]=ichrs+26; ihor[6][3]=ichrs+27;
  ihor[0][4]=ichrs+28; ihor[1][4]=ichrs+29; ihor[2][4]=ichrs+30; ihor[3][4]=ichrs+31;
  ihor[4][4]=ichrs+32; ihor[5][4]=ichrs+33; ihor[6][4]=ichrs+34;
  ihor[0][5]=ichrs+35; ihor[1][5]=ichrs+36; ihor[2][5]=ichrs+37; ihor[3][5]=ichrs+38;
  ihor[4][5]=ichrs+39; ihor[5][5]=ichrs+40; ihor[6][5]=ichrs+41;
  ihor[0][6]=ichrs+42; ihor[1][6]=ichrs+43; ihor[2][6]=ichrs+44; ihor[3][6]=ichrs+45;
  ihor[4][6]=ichrs+46; ihor[5][6]=ichrs+47; ihor[6][6]=ichrs+48;
}

void bord::clear(void)
{
  int i;

  for (i=0; i<49; i++) ichrs[i]=-2;
  for (i=0; i<49; i++) ispeler[i]=0;
  eindscore=0;
}

bool bord::doe_zet(int t, int ichr, int speler)
{
  if (ichrs[t]!=-2) return false;
  ichrs[t]=ichr;
  if (speler!=-1)
    ispeler[t]=(speler)?1:-1;
  return true;
}

bool bord::vol(void)
{
  int i;
  for (i=0; i<49; i++)
  {
    if (ichrs[i]==-2) return false;
  }
  return true;
}

void bord::print(int speler)
{
  fprint(stdout, speler);
}

void bord::fprint(FILE *fout, int speler)
{
  int i, letter;
  if (speler!=-1)
    speler=(speler)?1:-1;
  for (i=0; i<49; i++)
  {
    if ((i%7)==0) fprintf(fout, "\t");
    if (ichrs[i]==-2) letter='*';
    else letter=((ispeler[i]!=speler)?'a':'A')+ichrs[i];
    if (ispeler[i]==0) fprintf(fout, "<%c>", letter);
    else fprintf(fout, " %c ", letter);
    if ((i%7)==6) fprintf(fout, "\n");
  }
}

int bord::regelwaarde(int *iline[7])
{
  int hoogste=0, result;

  if (wb.knownn(iline, 7)) return 13;

  if (wb.knownn(iline, 6)) return 8;
  
  if (wb.knownn(iline+1, 6)) return 8;

  result=wb.knownn(iline, 5)+wb.knownn(iline+5, 2);
  if (result==6) return result;
  hoogste=result;

  result=wb.knownn(iline, 2)+wb.knownn(iline+2, 5);
  if (result==6) return result;
  hoogste=result;

  if (hoogste==5) return 5;

  if (wb.knownn(iline+1, 5)) return 5;

/* 4/3 */
  result=wb.knownn(iline, 4)+wb.knownn(iline+4, 3);
  if (result==5) return result;
  if (result>hoogste) hoogste=result;
  
  result=wb.knownn(iline, 3)+wb.knownn(iline+3, 4);
  if (result==5) return result;
  if (result>hoogste) hoogste=result;
  

/* 4/2 */
  result=wb.knownn(iline, 4)+wb.knownn(iline+4, 2);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline, 4)+wb.knownn(iline+5, 2);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;
  
  result=wb.knownn(iline+1, 4)+wb.knownn(iline+5, 2);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

/* 2/4 */
  result=wb.knownn(iline, 2)+wb.knownn(iline+2, 4);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline, 2)+wb.knownn(iline+3, 4);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline+1, 2)+wb.knownn(iline+3, 4);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

/* 3/3 */
  result=wb.knownn(iline, 3)+wb.knownn(iline+3, 3);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline, 3)+wb.knownn(iline+4, 3);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline+1, 3)+wb.knownn(iline+4, 3);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

/* 3/2/2 */
  result=wb.knownn(iline, 3)+wb.knownn(iline+3, 2)+wb.knownn(iline+5, 2);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline, 2)+wb.knownn(iline+2, 3)+wb.knownn(iline+5, 2);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline, 2)+wb.knownn(iline+2, 2)+wb.knownn(iline+4, 3);
  if (result==4) return result;
  if (result>hoogste) hoogste=result;

/*       */
  if (hoogste==3) return 3;

/* 3/2 */
  result=wb.knownn(iline, 3)+wb.knownn(iline+4, 2);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline+1, 3)+wb.knownn(iline+4, 2);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline+1, 3)+wb.knownn(iline+5, 2);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

/* 2/3 */
  result=wb.knownn(iline, 2)+wb.knownn(iline+3, 3);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline+1, 2)+wb.knownn(iline+3, 3);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline+1, 2)+wb.knownn(iline+4, 3);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

/* 2/2/2 */
  result=wb.knownn(iline, 2)+wb.knownn(iline+2, 2)+wb.knownn(iline+4, 2);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline, 2)+wb.knownn(iline+2, 2)+wb.knownn(iline+5, 2);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline, 2)+wb.knownn(iline+3, 2)+wb.knownn(iline+5, 2);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  result=wb.knownn(iline+1, 2)+wb.knownn(iline+3, 2)+wb.knownn(iline+5, 2);
  if (result==3) return result;
  if (result>hoogste) hoogste=result;

  if (hoogste==2) return 2;

/* 2/2 */
  result=wb.knownn(iline+1, 2)+wb.knownn(iline+4, 2);
  if (result==2) return result;
  if (result>hoogste) hoogste=result;

  return hoogste;
}

int bord::waarde(void)
{
  eindscore=regelwaarde(iver[0])+regelwaarde(iver[1])+regelwaarde(iver[2])+
            regelwaarde(iver[3])+regelwaarde(iver[4])+regelwaarde(iver[5])+
            regelwaarde(iver[6])+
            regelwaarde(ihor[0])+regelwaarde(ihor[1])+regelwaarde(ihor[2])+
            regelwaarde(ihor[3])+regelwaarde(ihor[4])+regelwaarde(ihor[5])+
            regelwaarde(ihor[6]);
  return eindscore;
}
