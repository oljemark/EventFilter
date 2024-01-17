#include <iostream>

#include "TFile.h"
#include "TH2F.h"
#include "TCanvas.h"
#include "TPaveStats.h"
#include "TStyle.h"

#include "TTree.h"

using namespace std;

TTree *tree = NULL ;

Bool_t valid_left_near ;
Double_t x_ln ;
Double_t y_ln ;

Bool_t valid_left_far ;
Double_t x_lf ;
Double_t y_lf ;

Bool_t valid_right_near ;
Double_t x_rn ;
Double_t y_rn ;

Bool_t valid_right_far ;
Double_t x_rf ;
Double_t y_rf ;

double Lx_near_meter ;
double Lx_far_meter ;

double vx_near ;
double vx_far ;

double Ly_near_meter ;
double Ly_far_meter =  0.0 ;

double vy_near ;
double vy_far ;

map<string, TH2F*> histosTH2F;
map<string, TH1F*> histosTH1F;

const int scenario_optics_default    = 0 ;
const int scenario_optics_HB_120_m   = 1 ;
const int scenario_optics_VHB_3_6_km = 2 ;

int scenario_optics = scenario_optics_HB_120_m ;

class myvec 
{
  double x,y ;
  
  public:
  
  myvec(double x=0, double y=0) : x(x), y(y) {} ;

  double length() ;
  void normalize() ;
  
  double scalar(myvec) ;
} ;

double myvec::length()
{
  double length = sqrt((x*x) + (y*y)) ;
  return length ;
}

void myvec::normalize()
{
  double the_length = length() ;

  x = x / the_length ;
  y = y / the_length ;
}

double myvec::scalar(myvec a)
{
  double result = ((x * a.x) + (y * a.y)) ;
  
  return result ;
}

class mycut
{
  double x1, y1, x2, y2 ;
  myvec unit_vec, normal_vec ;

  public:
  
  mycut(double, double, double, double) ;
  double projection(double, double) ;
} ;

mycut::mycut(double x1, double y1, double x2, double y2): x1(x1), y1(y1), x2(x2), y2(y2)
{
  myvec unit_vec_1(x2 - x1, y2 - y1) ;
  myvec normal_vec_1(y2 - y1, x1 - x2) ;
  
  unit_vec_1.normalize() ;
  normal_vec_1.normalize() ;
  
  unit_vec = unit_vec_1 ;
  normal_vec = normal_vec_1 ;
}

double mycut::projection(double x, double y) 
{
  myvec a_vec(x - x1, y - y1) ;
  double proj = a_vec.scalar(normal_vec) ;
  
  return proj ;
}


void book_histograms()
{
  int bins_1 = 400 ;

  double limit_1 = 40.0 ;
  double limit_2 = 40.0 ;
  double limit_3 = 400.0 ;
  double limit_4 = 200.0 ;

  if(scenario_optics == scenario_optics_HB_120_m)
  {
    limit_3 = 600.0 ;
    limit_4 = 600.0 ;
  }

  if(scenario_optics == scenario_optics_HB_120_m)
  {
    Lx_near_meter =  -9.03 ;
    Lx_far_meter =  -10.55 ;

    vx_near = -2.30 ;
    vx_far =  -1.91 ;

    Ly_near_meter = 242.09 ;
    Ly_far_meter =  277.06 ;

    vy_near = 0.025218 ;
    vy_far =  0.000055 ;
  }
  else if(scenario_optics == scenario_optics_VHB_3_6_km)
  {
    Lx_near_meter = 67.7 ;
    Lx_far_meter =  44.9 ;

    vx_near = -0.652 ;
    vx_far =  -0.536 ;

    Ly_near_meter = 252.6 ;
    Ly_far_meter =  293.4 ;

    vy_near = 0.024 ;
    vy_far =  0.000 ;
  }
  else
  {
    exit(1) ;
  }

  histosTH2F["hthx2DIM"] = new TH2F("hthx2DIM"  , "#theta_{X}^{R} vs #theta_{X}^{L}" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["y_left_near_y_right_near"] = new TH2F("y_left_near_y_right_near"  , "y_left_near_y_right_near" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_near_x_right_near"] = new TH2F("x_left_near_x_right_near"  , "x_left_near_x_right_near" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_left_far_y_right_far"] =   new TH2F("y_left_far_y_right_far"    , "y_left_far_y_right_far"   ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_far_x_right_far"] =   new TH2F("x_left_far_x_right_far"    , "x_left_far_x_right_far"   ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_left_near_dx_left"] = new TH2F("x_left_near_dx_left"  , "x_left_near_dx_left" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_left_near_dy_left"] = new TH2F("y_left_near_dy_left"  , "y_left_near_dy_left" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right"] = new TH2F("x_right_near_dx_right"  , "x_right_near_dx_right" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_right_near_dy_right"] = new TH2F("y_right_near_dy_right"  , "y_right_near_dy_right" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_left_near_dx_left_cut1"] = new TH2F("x_left_near_dx_left_cut1"  , "x_left_near_dx_left_cut1" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_left_near_dy_left_cut1"] = new TH2F("y_left_near_dy_left_cut1"  , "y_left_near_dy_left_cut1" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_cut1"] = new TH2F("x_right_near_dx_right_cut1"  , "x_right_near_dx_right_cut1" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_right_near_dy_right_cut1"] = new TH2F("y_right_near_dy_right_cut1"  , "y_right_near_dy_right_cut1" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_left_near_dx_left_cut2"] = new TH2F("x_left_near_dx_left_cut2"  , "x_left_near_dx_left_cut2" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_left_near_dy_left_cut2"] = new TH2F("y_left_near_dy_left_cut2"  , "y_left_near_dy_left_cut2" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_cut2"] = new TH2F("x_right_near_dx_right_cut2"  , "x_right_near_dx_right_cut2" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_right_near_dy_right_cut2"] = new TH2F("y_right_near_dy_right_cut2"  , "y_right_near_dy_right_cut2" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_left_near_dx_left_cut3"] = new TH2F("x_left_near_dx_left_cut3"  , "x_left_near_dx_left_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_left_near_dy_left_cut3"] = new TH2F("y_left_near_dy_left_cut3"  , "y_left_near_dy_left_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_cut3"] = new TH2F("x_right_near_dx_right_cut3"  , "x_right_near_dx_right_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_right_near_dy_right_cut3"] = new TH2F("y_right_near_dy_right_cut3"  , "y_right_near_dy_right_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["y_left_near_y_right_near_cut1"] = new TH2F("y_left_near_y_right_near_cut1" , "y_left_near_y_right_near_cut1" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_near_x_right_near_cut1"] = new TH2F("x_left_near_x_right_near_cut1" , "x_left_near_x_right_near_cut1" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["y_left_far_y_right_far_cut1"]   = new TH2F("y_left_far_y_right_far_cut1"   , "y_left_far_y_right_far_cut1"   ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_far_x_right_far_cut1"]   = new TH2F("x_left_far_x_right_far_cut1"   , "x_left_far_x_right_far_cut1"   ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_left_near_x_right_near_cut3"] = new TH2F("x_left_near_x_right_near_cut3" , "x_left_near_x_right_near_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_far_x_right_far_cut3"]   = new TH2F("x_left_far_x_right_far_cut3"   , "x_left_far_x_right_far_cut3"   ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_left_near_x_right_near_cut4"] = new TH2F("x_left_near_x_right_near_cut4" , "x_left_near_x_right_near_cut4" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_far_x_right_far_cut4"]   = new TH2F("x_left_far_x_right_far_cut4"   , "x_left_far_x_right_far_cut4"   ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["theta_x_star_left_right"] = new TH2F("theta_x_star_left_right"  , "theta_x_star_left_right" ,bins_1, -limit_4, limit_4, bins_1,  -limit_3, limit_3);
  histosTH2F["theta_x_star_left_right_cut1"] = new TH2F("theta_x_star_left_right_cut1"  , "theta_x_star_left_right_cut1" ,bins_1, -limit_4, limit_4, bins_1,  -limit_3, limit_3);
  histosTH2F["theta_x_star_left_right_cut2"] = new TH2F("theta_x_star_left_right_cut2"  , "theta_x_star_left_right_cut2" ,bins_1, -limit_4, limit_4, bins_1,  -limit_3, limit_3);
  histosTH2F["theta_x_star_left_right_cut3"] = new TH2F("theta_x_star_left_right_cut3"  , "theta_x_star_left_right_cut3" ,bins_1, -limit_4, limit_4, bins_1,  -limit_3, limit_3);
  histosTH2F["theta_x_star_left_right_cut4"] = new TH2F("theta_x_star_left_right_cut4"  , "theta_x_star_left_right_cut4" ,bins_1, -limit_4, limit_4, bins_1,  -limit_3, limit_3);

  histosTH2F["x_star_left_right"] = new TH2F("x_star_left_right"  , "x_star_left_right" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_star_left_right_cut1"] = new TH2F("x_star_left_right_cut1"  , "x_star_left_right_cut2" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_star_left_right_cut2"] = new TH2F("x_star_left_right_cut2"  , "x_star_left_right_cut2" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_star_left_right_cut3"] = new TH2F("x_star_left_right_cut3"  , "x_star_left_right_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_star_left_right_cut4"] = new TH2F("x_star_left_right_cut4"  , "x_star_left_right_cut4" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["y_star_left_right"] = new TH2F("y_star_left_right"  , "y_star_left_right" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH1F["projection"] = new TH1F("projection"  , "projection" , bins_1, -limit_1, limit_1);
  histosTH1F["proj_2"] = new TH1F("proj_2"  , "projection" , bins_1, -limit_1, limit_1);
  histosTH1F["proj_2_cut3"] = new TH1F("proj_2_cut3"  , "proj_2_cut3" , bins_1, -limit_1, limit_1);
  histosTH1F["proj_3"] = new TH1F("proj_3"  , "projection" , bins_1, -limit_1, limit_1);
  histosTH1F["theta_x_star_right"] = new TH1F("theta_x_star_right"  , "theta_x_star_right" , 25*bins_1,  -limit_3, limit_3);
  histosTH1F["theta_x_star_left_right_proj"] = new TH1F("theta_x_star_left_right_proj"  , "theta_x_star_left_right_proj" ,bins_1, -limit_4, limit_4);
  histosTH1F["theta_x_star_left_right_cut1_proj"] = new TH1F("theta_x_star_left_right_cut1_proj"  , "theta_x_star_left_right_cut1_proj" ,bins_1, -limit_4, limit_4);
  histosTH1F["theta_x_star_left_right_cut2_proj"] = new TH1F("theta_x_star_left_right_cut2_proj"  , "theta_x_star_left_right_cut2_proj" ,bins_1, -limit_4, limit_4);
  histosTH1F["theta_x_star_left_right_cut3_proj"] = new TH1F("theta_x_star_left_right_cut3_proj"  , "theta_x_star_left_right_cut3_proj" ,bins_1, -limit_4, limit_4);
  histosTH1F["theta_x_star_left_right_cut4_proj"] = new TH1F("theta_x_star_left_right_cut4_proj"  , "theta_x_star_left_right_cut4_proj" ,bins_1, -limit_4, limit_4);

  histosTH1F["proj_4_cut4"] = new TH1F("proj_4_cut4"  , "proj_4_cut4" , bins_1, -limit_1, limit_1);

  histosTH2F["x_left_near_y_left_near"] = new TH2F("x_left_near_y_left_near", "x_left_near_y_left_near" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_far_y_left_far"] = new TH2F("x_left_far_y_left_far", "x_left_far_y_left_far" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_right_near_y_right_near"] = new TH2F("x_right_near_y_right_near", "x_right_near_y_right_near" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far"] = new TH2F("x_right_far_y_right_far", "x_right_far_y_right_far" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_left_near_y_left_near_cut3"] = new TH2F("x_left_near_y_left_near_cut3", "x_left_near_y_left_near_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_left_far_y_left_far_cut3"] = new TH2F("x_left_far_y_left_far_cut3", "x_left_far_y_left_far_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_right_near_y_right_near_cut3"] = new TH2F("x_right_near_y_right_near_cut3", "x_right_near_y_right_near_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far_cut3"] = new TH2F("x_right_far_y_right_far_cut3", "x_right_far_y_right_far_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["x_right_near_y_right_near_band1"] = new TH2F("x_right_near_y_right_near_band1", "x_right_near_y_right_near_band1" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far_band1"] = new TH2F("x_right_far_y_right_far_band1", "x_right_far_y_right_far_band1" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_y_right_near_band2"] = new TH2F("x_right_near_y_right_near_band2", "x_right_near_y_right_near_band2" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far_band2"] = new TH2F("x_right_far_y_right_far_band2", "x_right_far_y_right_far_band2" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_y_right_near_band_none"] = new TH2F("x_right_near_y_right_near_band_none", "x_right_near_y_right_near_band_none" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far_band_none"] = new TH2F("x_right_far_y_right_far_band_none", "x_right_far_y_right_far_band_none" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_band1"] = new TH2F("x_right_near_dx_right_band1"  , "x_right_near_dx_right_band1" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_band2"] = new TH2F("x_right_near_dx_right_band2"  , "x_right_near_dx_right_band2" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_band_none"] = new TH2F("x_right_near_dx_right_band_none"  , "x_right_near_dx_right_band_none" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  
  histosTH2F["x_right_near_y_right_near_band1_cut3"] = new TH2F("x_right_near_y_right_near_band1_cut3", "x_right_near_y_right_near_band1_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far_band1_cut3"] = new TH2F("x_right_far_y_right_far_band1_cut3", "x_right_far_y_right_far_band1_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_y_right_near_band2_cut3"] = new TH2F("x_right_near_y_right_near_band2_cut3", "x_right_near_y_right_near_band2_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far_band2_cut3"] = new TH2F("x_right_far_y_right_far_band2_cut3", "x_right_far_y_right_far_band2_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_y_right_near_band_none_cut3"] = new TH2F("x_right_near_y_right_near_band_none_cut3", "x_right_near_y_right_near_band_none_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_far_y_right_far_band_none_cut3"] = new TH2F("x_right_far_y_right_far_band_none_cut3", "x_right_far_y_right_far_band_none_cut3" ,bins_1,  -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_band1_cut3"] = new TH2F("x_right_near_dx_right_band1_cut3"  , "x_right_near_dx_right_band1_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_band2_cut3"] = new TH2F("x_right_near_dx_right_band2_cut3"  , "x_right_near_dx_right_band2_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);
  histosTH2F["x_right_near_dx_right_band_none_cut3"] = new TH2F("x_right_near_dx_right_band_none_cut3"  , "x_right_near_dx_right_band_none_cut3" ,bins_1, -limit_1, limit_1, bins_1,  -limit_2, limit_2);

  histosTH2F["y_left_near_y_right_near"]->GetXaxis()->SetTitle("y_{left,near} (mm)") ;
  histosTH2F["y_left_near_y_right_near"]->GetYaxis()->SetTitle("y_{right,near} (mm)") ;

  histosTH2F["y_left_far_y_right_far"]->GetXaxis()->SetTitle("y_{left,far} (mm)") ;
  histosTH2F["y_left_far_y_right_far"]->GetYaxis()->SetTitle("y_{right,far} (mm)") ;

  histosTH1F["theta_x_star_left_right_cut2_proj"]->GetXaxis()->SetTitle("#theta_{x,left}*  (#murad)") ;

  histosTH2F["x_star_left_right_cut2"]->GetXaxis()->SetTitle("x_{left}* (mm)") ;
  histosTH2F["x_star_left_right_cut2"]->GetYaxis()->SetTitle("x_{right}* (mm)") ;
  
  histosTH1F["theta_x_star_left_right_proj"]->GetXaxis()->SetTitle("#theta_{x,left}* - #theta_{x,right}* (#murad)") ; 
  
  
}

void end_job()
{
  string plots_directory = "Plots/" ;

  for (const auto &p : histosTH2F)
    p.second->Write(p.first.c_str());

  for (const auto &p : histosTH1F)
    p.second->Write(p.first.c_str());

}

 string diagonal = "LBRT" ;
// string diagonal = "LTRB" ;

main()
{

  mycut *cut1 = NULL  ;
  mycut *cut2 = NULL  ;
  mycut *cut2_2 = NULL  ;
  mycut *cut3 = NULL  ;
  mycut *cut4 = NULL  ;

  double cut2_2_sigma = 0 ;
  
  if(scenario_optics == scenario_optics_HB_120_m)
  {
    if(diagonal.compare("LBRT") == 0)
    {
      cut1 = new mycut(-6.92636, 10.1021 , -3.39028, 6.44269) ;
      cut2 = new mycut(  -1.61037,  1.7786, -0.242165, 0.602754) ;
      cut2_2 = new mycut( -1.03231, 2.12436, -1.03231, 0.40036) ;
      cut3 = new mycut( 7.82283,  -0.0912076, 16.1149, 1.13814) ;
      cut4 = new mycut(  -0.717142,   -0.0161017,   0.163698,   1.12903) ;


      cut2_2_sigma = 1.2 ;
    }
    else if(diagonal.compare("LTRB") == 0)
    {
      cut1 = new mycut(-6.92636, 10.1021 , -3.39028, 6.44269) ;
      cut2 = new mycut(   -0.882548,    1.45932,    2.49109,    -0.915678) ;
      cut2_2 = new mycut( 0.78, 2.12436, 0.78, 0.40036) ;
      cut3 = new mycut( 7.82283,  -0.0912076, 16.1149, 1.13814) ;
      cut4 = new mycut(1.24783, 1.54301, -0.61326, -0.141314) ;


      cut2_2_sigma = 1.2 ;
    }
    else
    {
      cout << "No such diagonal" << endl ;
      exit(1) ;
    }

  }
  else if(scenario_optics == scenario_optics_VHB_3_6_km)
  {
    cut1 = new mycut(-6.92636, 10.1021 , -3.39028, 6.44269) ;
    cut2 = new mycut( 6.3982,  -6.61457,  2.73925,-9.00424) ;
    cut2_2 = new mycut( -1.03231, 2.12436, -1.03231, 0.40036) ;

    // cut2_2_sigma = 10.0 ; // neutralize cut
  }

  double distance_mm = (220000 - 213000) ;


  TFile *file = new TFile(("ntuple_" + diagonal + ".root").c_str(), "READ") ;

  TTree *tree = (TTree *)file->Get("TReducedNtuple") ;
  
  tree->SetBranchAddress("track_right_far_valid", &valid_right_far) ;
  tree->SetBranchAddress("track_right_far_x",     &x_rf) ;
  tree->SetBranchAddress("track_right_far_y",     &y_rf) ;

  tree->SetBranchAddress("track_left_far_valid",  &valid_left_far) ;
  tree->SetBranchAddress("track_left_far_x",      &x_lf) ;
  tree->SetBranchAddress("track_left_far_y",      &y_lf) ;

  tree->SetBranchAddress("track_right_near_valid",&valid_right_near) ;
  tree->SetBranchAddress("track_right_near_x",    &x_rn) ;
  tree->SetBranchAddress("track_right_near_y",    &y_rn) ;

  tree->SetBranchAddress("track_left_near_valid", &valid_left_near) ;
  tree->SetBranchAddress("track_left_near_x",     &x_ln) ;
  tree->SetBranchAddress("track_left_near_y",     &y_ln) ;
  
  Int_t entries = (Int_t)tree->GetEntries();
  
  int read_entries = 0 ;
  
  myvec unit_vec(1.0, 1.0) ;  
  
  TFile results(("results_" + diagonal + ".root").c_str(), "RECREATE") ;
  results.cd() ;
  
  book_histograms() ;

  for(int i = 0 ; i < entries ; ++i)
  {  
    tree->GetEntry(i) ;
    
    // cout << "Check optics Ly_near_meter " << Ly_near_meter << endl ;

    bool diagonal_LBRT = ((y_lf < 0) && (y_ln < 0) && (y_rn > 0) && (y_rf > 0)) && (diagonal.compare("LBRT") == 0) ;
    bool diagonal_LTRB = ((y_lf > 0) && (y_ln > 0) && (y_rn < 0) && (y_rf < 0)) && (diagonal.compare("LTRB") == 0) ;
  
    if(valid_left_near && valid_left_far && valid_right_far && valid_right_near && (diagonal_LBRT || diagonal_LTRB) )
    {
      histosTH2F["x_left_near_y_left_near"]->Fill(x_ln, y_ln) ;
      histosTH2F["x_left_far_y_left_far"]->Fill(x_lf, y_lf) ;
      histosTH2F["x_right_near_y_right_near"]->Fill(x_rn, y_rn) ;
      histosTH2F["x_right_far_y_right_far"]->Fill(x_rf, y_rf) ;
    

      double dx_left = (x_lf - x_ln) ;
      double dy_left = (y_lf - y_ln) ;

      double dx_right = (x_rf - x_rn) ;
      double dy_right = (y_rf - y_rn) ;

      double theta_x_left = (x_lf - x_ln) / distance_mm ;
      double theta_y_left = (y_lf - y_ln) / distance_mm ;

      double theta_x_right = (x_rf - x_rn) / distance_mm ;
      double theta_y_right = (y_rf - y_rn) / distance_mm ;

      histosTH2F["y_left_near_y_right_near"]->Fill(y_ln, y_rn) ;
      histosTH2F["x_left_near_x_right_near"]->Fill(x_ln, x_rn) ;
      histosTH2F["y_left_far_y_right_far"]->Fill(y_lf, y_rf) ;
      histosTH2F["x_left_far_x_right_far"]->Fill(x_lf, x_rf) ;

      histosTH2F["x_left_near_dx_left"]->Fill(x_ln, dx_left) ;
      histosTH2F["y_left_near_dy_left"]->Fill(y_ln, dy_left) ;

      histosTH2F["x_right_near_dx_right"]->Fill(x_rn, dx_right) ;
      histosTH2F["y_right_near_dy_right"]->Fill(y_rn, dy_right) ;

      myvec track(y_ln, y_rn) ;

      double projection = track.scalar(unit_vec) ;

      histosTH1F["projection"]->Fill(projection) ;

      double det_x = ((vx_near * Lx_far_meter) - (vx_far * Lx_near_meter)) ;
      double det_y = ((vy_near * Ly_far_meter) - (vy_far * Ly_near_meter)) ;

      double x_star_left  = ((Lx_far_meter * x_ln) - (Lx_near_meter * x_lf)) / det_x ;
      double x_star_right = ((Lx_far_meter * x_rn) - (Lx_near_meter * x_rf)) / det_x ;

      double y_star_left  = ((Ly_far_meter * y_ln) - (Ly_near_meter * y_lf)) / det_y ;
      double y_star_right = ((Ly_far_meter * y_rn) - (Ly_near_meter * y_rf)) / det_y ;

      double theta_x_star_left  = 1000.0 * ((vx_far * x_ln) - (vx_near * x_lf)) / det_x ;
      double theta_x_star_right = 1000.0 * ((vx_far * x_rn) - (vx_near * x_rf)) / det_x ;

      const bool band1=(((fabs(theta_x_star_right - 101.9) < 7.) && (diagonal.compare("LTRB") == 0)) ||
		      ((fabs(theta_x_star_right - 276.7) < 6.5) && (diagonal.compare("LBRT") == 0)));
      const bool band2=(((fabs(theta_x_star_right - 121.9) < 6.) && (diagonal.compare("LTRB") == 0)) ||
		      ((fabs(theta_x_star_right - 298.1) < 6.) && (diagonal.compare("LBRT") == 0)));
      const bool nonBand=(!band1)&&(!band2);
      if (band1) {
       histosTH2F["x_right_near_y_right_near_band1"]->Fill(x_rn, y_rn) ;
       histosTH2F["x_right_far_y_right_far_band1"]->Fill(x_rf, y_rf) ;
       histosTH2F["x_right_near_dx_right_band1"]->Fill(x_rn, dx_right) ;
      }
      if (band2) {
       histosTH2F["x_right_near_y_right_near_band2"]->Fill(x_rn, y_rn) ;
       histosTH2F["x_right_far_y_right_far_band2"]->Fill(x_rf, y_rf) ;
       histosTH2F["x_right_near_dx_right_band2"]->Fill(x_rn, dx_right) ;
      }
      if (nonBand) {
       histosTH2F["x_right_near_y_right_near_band_none"]->Fill(x_rn, y_rn) ;
       histosTH2F["x_right_far_y_right_far_band_none"]->Fill(x_rf, y_rf) ;
       histosTH2F["x_right_near_dx_right_band_none"]->Fill(x_rn, dx_right) ;
      }

      histosTH1F["theta_x_star_right"]->Fill(theta_x_star_right) ;
      histosTH2F["theta_x_star_left_right"]->Fill(theta_x_star_left, theta_x_star_right) ;
      histosTH2F["x_star_left_right"]->Fill(x_star_left, x_star_right) ;

      histosTH2F["y_star_left_right"]->Fill(y_star_left, y_star_right) ;

      double proj_1 = cut1->projection(theta_x_star_left, theta_x_star_right) ;
      double proj_2 = cut2->projection(x_star_left, x_star_right) ;
      double proj_2_2 = cut2_2->projection(x_star_left, x_star_right) ;
      double proj_3 = cut3->projection(y_rn, dy_right) ;
      double proj_4 = cut4->projection(x_lf, x_rf) ;

      histosTH1F["proj_2"]->Fill(proj_2) ;
      histosTH1F["proj_3"]->Fill(proj_3) ;

      histosTH1F["theta_x_star_left_right_proj"]->Fill(proj_1) ;

      double sigma_0 = 0.4 ;

      if(fabs(projection) < (4 * sigma_0))
      {
        histosTH2F["y_left_near_y_right_near_cut1"]->Fill(y_ln, y_rn) ;
        histosTH2F["x_left_near_x_right_near_cut1"]->Fill(x_ln, x_rn) ;
        histosTH2F["y_left_far_y_right_far_cut1"]->Fill(y_lf, y_rf) ;
        histosTH2F["x_left_far_x_right_far_cut1"]->Fill(x_lf, x_rf) ;

        histosTH2F["x_left_near_dx_left_cut1"]->Fill(x_ln, dx_left) ;
        histosTH2F["y_left_near_dy_left_cut1"]->Fill(y_ln, dy_left) ;
        histosTH2F["x_right_near_dx_right_cut1"]->Fill(x_rn, dx_right) ;
        histosTH2F["y_right_near_dy_right_cut1"]->Fill(y_rn, dy_right) ;

        histosTH2F["theta_x_star_left_right_cut1"]->Fill(theta_x_star_left, theta_x_star_right) ;
        histosTH2F["x_star_left_right_cut1"]->Fill(x_star_left, x_star_right) ;

        histosTH1F["theta_x_star_left_right_cut1_proj"]->Fill(proj_1) ;

        double sigma_3 = 0.07 ;

        if(proj_3 < (4 * sigma_3))
        {
          histosTH2F["theta_x_star_left_right_cut2"]->Fill(theta_x_star_left, theta_x_star_right) ;
          histosTH2F["x_star_left_right_cut2"]->Fill(x_star_left, x_star_right) ;

          histosTH2F["x_left_near_dx_left_cut2"]->Fill(x_ln, dx_left) ;
          histosTH2F["y_left_near_dy_left_cut2"]->Fill(y_ln, dy_left) ;
          histosTH2F["x_right_near_dx_right_cut2"]->Fill(x_rn, dx_right) ;
          histosTH2F["y_right_near_dy_right_cut2"]->Fill(y_rn, dy_right) ;

          histosTH1F["theta_x_star_left_right_cut2_proj"]->Fill(proj_1) ;



          const double sigma_3 = 2.65397e-01 ;

          // if(fabs(proj_2) < (3 * sigma_3))
          if(fabs(proj_2) < (3 * sigma_3) && (fabs(proj_2_2) < cut2_2_sigma))
          {
            histosTH1F["proj_2_cut3"]->Fill(proj_2) ;
            if (band1) {
             histosTH2F["x_right_near_y_right_near_band1_cut3"]->Fill(x_rn, y_rn) ;
             histosTH2F["x_right_far_y_right_far_band1_cut3"]->Fill(x_rf, y_rf) ;
             histosTH2F["x_right_near_dx_right_band1_cut3"]->Fill(x_rn, dx_right) ;
            }
            if (band2) {
             histosTH2F["x_right_near_y_right_near_band2_cut3"]->Fill(x_rn, y_rn) ;
             histosTH2F["x_right_far_y_right_far_band2_cut3"]->Fill(x_rf, y_rf) ;
             histosTH2F["x_right_near_dx_right_band2_cut3"]->Fill(x_rn, dx_right) ;
            }
            if (nonBand) {
             histosTH2F["x_right_near_y_right_near_band_none_cut3"]->Fill(x_rn, y_rn) ;
             histosTH2F["x_right_far_y_right_far_band_none_cut3"]->Fill(x_rf, y_rf) ;
             histosTH2F["x_right_near_dx_right_band_none_cut3"]->Fill(x_rn, dx_right) ;
            }

            histosTH1F["theta_x_star_left_right_cut3_proj"]->Fill(proj_1) ;

            histosTH2F["theta_x_star_left_right_cut3"]->Fill(theta_x_star_left, theta_x_star_right) ;
            histosTH2F["x_star_left_right_cut3"]->Fill(x_star_left, x_star_right) ;

            histosTH2F["x_left_near_dx_left_cut3"]->Fill(x_ln, dx_left) ;
            histosTH2F["y_left_near_dy_left_cut3"]->Fill(y_ln, dy_left) ;
            histosTH2F["x_right_near_dx_right_cut3"]->Fill(x_rn, dx_right) ;
            histosTH2F["y_right_near_dy_right_cut3"]->Fill(y_rn, dy_right) ;

            histosTH2F["x_left_near_y_left_near_cut3"]->Fill(x_ln, y_ln) ;
            histosTH2F["x_left_far_y_left_far_cut3"]->Fill(x_lf, y_lf) ;
            histosTH2F["x_right_near_y_right_near_cut3"]->Fill(x_rn, y_rn) ;
            histosTH2F["x_right_far_y_right_far_cut3"]->Fill(x_rf, y_rf) ;
            
            histosTH2F["x_left_near_x_right_near_cut3"]->Fill(x_ln, x_rn) ;
            histosTH2F["x_left_far_x_right_far_cut3"]->Fill(x_lf, x_rf) ;

            if(fabs(proj_4) < (3 * 0.3))
            {

              histosTH1F["theta_x_star_left_right_cut4_proj"]->Fill(proj_1) ;

              histosTH2F["theta_x_star_left_right_cut4"]->Fill(theta_x_star_left, theta_x_star_right) ;
              histosTH2F["x_star_left_right_cut4"]->Fill(x_star_left, x_star_right) ;

              histosTH2F["x_left_near_x_right_near_cut4"]->Fill(x_ln, x_rn) ;
              histosTH2F["x_left_far_x_right_far_cut4"]->Fill(x_lf, x_rf) ;
              
              histosTH1F["proj_4_cut4"]->Fill(proj_4) ;
              
            }
          }
        }
      }
    }
    
    ++read_entries ;
  }
  
  end_job() ;
  
  cout << "read_entries: " << read_entries << endl ;
}
