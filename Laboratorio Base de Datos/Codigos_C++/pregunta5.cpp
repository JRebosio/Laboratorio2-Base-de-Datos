#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath> 
#include <algorithm>   
#include <vector>

using namespace std;

int main() {
  const char delim=',';
  int dia, mes;
  string line,basename,id;
  basename.resize(39);
  map<string,string> idbasename;
  map<string, int> basenameservices;
  vector<pair<string,int> > orden;

  ifstream in("../TAXI_NY/driver.csv");
  
  getline(in , line);
  
  
   while(getline(in , line)){
     stringstream ln(line);
     ln.ignore(100,delim);
     ln.ignore(100,delim);;
     ln.ignore(27);
     ln.ignore(10,delim);;
     ln.ignore(100,delim);
     getline(ln,id,delim);
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     
     if(ln.peek()=='\"') ln.ignore();
     if(ln.peek()==' ') continue;
      ln.read( &basename[0], 39 );
      idbasename[id]=basename;   
    }

  
  ifstream on("../TAXI_NY/service.csv");
  
  getline(on , line);
  
  while(getline(on , line) ){

     stringstream ss(line);

     ss.ignore(100,delim);

     getline(ss,id,delim);
     
     ss>>dia;
     
     ss.ignore();
     
     ss>>mes;
     
     if( dia==28 && mes==12 )
        if( idbasename.find(id)!=idbasename.end() ) basenameservices[idbasename[id]]+=1;
    }
   

  
  for ( const auto& u:basenameservices ) 
  {
    orden.emplace_back(u.first, u.second);
  }

  sort(orden.begin(), orden.end(),
        [](const pair<string, double>& p1, const pair<string, double>&p2) { return p1.second > p2.second; }); 
 
 ofstream resultado;
 resultado.open("../Respuestas(ArchivosCSV)/ResultadoPregunta5.csv");
 resultado<<"Nombre De La Empresa, Cantidad De Sercicios Realizados El 28/12, Empresas que reportaron servicios el 28 de Diciembre = "<<orden.size()<<"\n";
 
 for(auto const& u:orden) resultado<<"\""<<u.first<<"\""<<","<<u.second<<"\n";

 resultado.close();	
 return 0;
}
