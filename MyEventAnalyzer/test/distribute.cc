#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include "math.h"
#include "math.h"

#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TStyle.h"

#include "TTree.h"

using namespace std;

string output_dir = "/afs/cern.ch/work/f/fnemes/main_workspace/2023/13p6_TeV/CMSSW_13_0_7_TOTEM/src/MyEventAnalyzer/MyEventAnalyzer/test/" ; 

int main()
{
  ifstream files("/afs/cern.ch/work/f/fnemes/main_workspace/2023/13p6_TeV/CMSSW_13_0_7_TOTEM/src/template/files.txt") ;
  
  
  string filename ;
  
  int index = 0 ;

  ofstream submitfile("/afs/cern.ch/work/f/fnemes/main_workspace/2023/13p6_TeV/CMSSW_13_0_7_TOTEM/src/MyEventAnalyzer/MyEventAnalyzer/test/submit.sh") ;
  
  string diagonal = "LBRT" ;
//  string diagonal = "LTRB" ;
  
  while(files >> filename)
  {
  
    string suffix = "" ;
    
    if(diagonal.compare("LTRB") == 0) suffix = "_LTRB" ;
  
    ifstream cfg_part1("/afs/cern.ch/work/f/fnemes/main_workspace/2023/13p6_TeV/CMSSW_13_0_7_TOTEM/src/template/cfg_analyzer_part1.py") ;
    ifstream cfg_part2(("/afs/cern.ch/work/f/fnemes/main_workspace/2023/13p6_TeV/CMSSW_13_0_7_TOTEM/src/template/cfg_analyzer_part2" + suffix + ".py").c_str()) ;

    stringstream ss ;
    
    ss << index  ;

    string dirindex = ss.str() ;
    if(index < 10) dirindex = "0" + dirindex ;

    // cout << dirindex << endl ;
    
    ofstream cfgfile(output_dir + "dir_" + dirindex + "/cfg_analyzer.py") ;
    
    string line ;
    int linecounter = 0 ;
    
    while(getline(cfg_part1, line))
    {  
      cfgfile << line ;
      if(linecounter < 29) cfgfile << endl ;
      ++linecounter ;
    }
    
    cfgfile << filename ;

    while(getline(cfg_part2, line))
    {  
      cfgfile << line << endl ;
    }
    
    cfg_part1.close() ;
    cfg_part2.close() ;
    
    submitfile << "cd dir_" << dirindex << endl ;
    submitfile << "cmsRun cfg_analyzer.py >> /dev/null &" << endl ;
    submitfile << "cd .." << endl ;

      
    ++index ;
  }
}
