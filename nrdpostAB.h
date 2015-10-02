#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>

using namespace std;
#define REGIONTYPE 3	
#define MAXREGION 200
#define MAXSUBVOL 4000
#define STATTYPE 2

//Eventually, make this an input argument so no need to recompile
string fakename="default.sa1";


  int nelement;  // total number of elements(volume)
	int totalsteps;
	int istotalstepsknown;
	int neleflag;	
	//char* filename;
//	char* outfile;
    string filename;
    string outfile;
    string avgfile;
    string molnameinput;
    string multipleinput;
    string mollist;
    string cclohead;
    string cnumdata;
    string nrdpostfilename;
    string selmapname;

    string meshfilename;
    string subregion[MAXREGION]; //max sub region number 
    float subregavg[MAXREGION][REGIONTYPE][STATTYPE]; //[subreg_name][0all_1:cyt_2:submem][//0avg//1variance]   
    float subregavga0;
    float subregavga1;
    int subregavgacnt;
    float subregvolsuma;

    
    int subregcnt[MAXREGION][REGIONTYPE]; //[subreg_name_numbering][count for //0all//1dend//2cytosol] //need initialize
    float subregvolsum[MAXREGION][REGIONTYPE]; //[subreg_volumesum][count for //0all//1dend//2cytosol] //need initialize
    
    int subregioncount;
    int islistfound;
    int isallregavg;
    int isavgfilename;
    
    string regionheaderinfo[MAXSUBVOL]; 
    float meshvolume[MAXSUBVOL];
    int volnum[MAXSUBVOL];
    string ccolheadtmp;
    
    
    
    size_t found;
  
  
	char argtmp[256];
	char mollisttmp[20];
  string cmollisttmp;
	
	int nelementtmp;
	int targetmolecule;
	int isprintscreen;
	int isforinformation;
	int isextractingall;
	int isextractingmultiple;
	int nmultiple;
	int ismeshfileexist;
	
	
	int totalmoleculekind;
	int isSpcfound;
	
	  int nmolcount;
	    int is0sthead;
	    int dotcount;
	    int dataalinecount;
	    
	    float divnptonM;
	    
	    float f_dt;


	    
	    //for x sort
      int sortlinecount;
      int sortcharcount;
      int sortsublinecount;
      int sortblockcount;
      char sorttmp[20];

      
      int isdatanumberofmolecule;
     
	    int isxsort;
	    int isysort;
	    int isaverage;
	    float xyout_cord[2000];
 	    float xyout_datasum[2000];
 	    float xyout_numberadd[2000];
 	    float xyout_volumesum[2000];
 	    
 	    float xyout_varsum[2000];
      float tmpvar;

	    int nselected;
      int ncoord;
	    int xyout_cmap[2000];
 	    int xyout_nelement[2000];
 	    float xyout_x[2000];
 	    float xyout_y[2000];
 	    float xyout_volume[2000];
 	    

	char tmpchar[20]; 	
	
	
	
	void CodeTest();
	void ReadData();
  void ReadMesh();
	void Readsubdomain();
	void Initialize();
  int Chknumber();
 	
 	

using namespace std;
