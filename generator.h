
#define SIZE_READ       100
#define NB_READ   950000

int NB_GET_READ = 0;
int SIZE_DATA = 0;
char *DATA;

void initGenerator()
{
  FILE *fdata;
  int size_file;
  char BUF[128];
  int i;

  fdata = fopen("generator.txt","r");
  fseek(fdata,0,SEEK_END);
  size_file = ftell(fdata);
  rewind(fdata);

  DATA = (char *) malloc(size_file);
  SIZE_DATA = 0;
  while (fgets(BUF,128,fdata)!=NULL)
    {
      i=0;
      while(BUF[i]!='\n') 
	{
	  DATA[SIZE_DATA] = BUF[i];
	  SIZE_DATA++;
	  i++;
	}
    }
  fclose(fdata);
}

int getRead(char *seq)
{
  int i, k;

  if (NB_GET_READ  == NB_READ) return 0;

  k = rand()%(SIZE_DATA-SIZE_READ);
  for (i=0; i<SIZE_READ; i++)
    {
      seq[i] = DATA[k+i];
    }
  seq[i] = '\0';
  NB_GET_READ++;
  return 1;
}
