/*
*/
//---------------------------------------------------------------------------

//--Include's----------------------------------------------------------------
#include "main.h"

//--Define's-----------------------------------------------------------------

//--Struct Define's----------------------------------------------------------
 
//--Vars---------------------------------------------------------------------
int score[8]={0, 0, 1, 2, 3, 5, 8, 13};

//--Functions----------------------------------------------------------------
trie::trie(trie *p, int ic, int d)
{
  int i;
  
  parent=p;
  ichr=ic;
  depth=d;
  end=false;
  for (i=0; i<26; i++) childs[i]=NULL;
}

trie::~trie()
{
  int i;
  for (i=0; i<26; i++) if (childs[i]!=NULL) delete childs[i];
}

void trie::add(int *ilist)
{
  if (*ilist==-1)
  {
    end=true;
    return;
  }
  if (childs[*ilist]==NULL) childs[*ilist]=new trie(this, *ilist, depth+1);
  childs[*ilist]->add(ilist+1);
}

bool trie::known(int *ilist)
{
  if (*ilist==-1)
  {
    if (end) return true;
    return false;
  }
  if (childs[*ilist]==NULL) return false;
  return childs[*ilist]->known(ilist+1);
}

int trie::knownn(int **ilist, int length)
{
  if (depth==length)
  {
    if (end) return score[length];
    return 0;
  }
  if (childs[**ilist]==NULL) return 0;
  return childs[**ilist]->knownn(ilist+1, length);
}

void trie::print(char *buf)
{
  int i;

  if (end)
  {
    buf[depth]='\0';
    printf("%s\n", buf);
  }
  for (i=0; i<26; i++)
  {
    if (childs[i]!=NULL)
    {
      buf[depth]='A'+i;
      childs[i]->print(buf);
    }
  }
}

int trie::load_from_file(char *filename)
{
  FILE *instr=fopen(filename, "r");
  char buf[256];
  int ibuf[256];
  int i, l;

  if (instr==NULL) return 0;

  while (!feof(instr))
  {
    fgets(buf, 256, instr);
    l=strlen(buf)-1;
    if (l!=0)
    {
      for (i=0; i<l; i++) ibuf[i]=buf[i]-'A';
      ibuf[l]=-1;
      add(ibuf);
    }
  }

  return 1;
}
