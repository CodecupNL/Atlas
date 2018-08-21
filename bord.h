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
    void load_from_file(char *filename);
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
    void print(void);
    int regelwaarde(int *iline[7]);
    int waarde(void);
};

extern trie wb;
