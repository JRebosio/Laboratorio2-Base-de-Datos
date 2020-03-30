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
  string line ,active , id , nombre ;
  nombre.resize(27);
  map<string,int> CNA;
  map<string,string> idchofer;
  vector<pair<string,double> > orden;
 

  ifstream in("../TAXI_NY/driver.csv"); 
  getline(in , line);

 
  
  while( getline ( in , line ) ) {
     
     stringstream ln( line );
     
     getline(ln,active,delim);// YES o NO
     
     ln.ignore(10,delim);
     
     if( ln.peek()=='\"' )  ln.ignore();
     ln.read( &nombre[0], 27 );
     
     ln.ignore(10,delim);
     ln.ignore(100,delim);
     getline(ln,id,delim);
     
     idchofer[id]=nombre;
     if (active[0]=='N') CNA[id]=0; 
    
   }


  
  ifstream on("../TAXI_NY/service.csv");
  

  getline(on , line);
  
  while(getline(on , line) ){
     stringstream ss(line);
     ss.ignore(100,delim);
     getline(ss,id,delim);
     if(CNA.find(id)!=CNA.end())
          CNA[id]+=1;
    }

   
    int servicios=0;
    for (const auto& u:CNA) 
    {
    orden.emplace_back(u.first, u.second);
    servicios+=u.second;	
    } 
    
    //cout<<servicios; 120816 servicios
    //cout<<CNA.size(); 488 choferes inactivos
	
    sort(orden.begin(), orden.end(),
        [](const pair<string, double>& p1, const pair<string, double>&p2) { return p1.second > p2.second; });

    ofstream resultado;
    resultado.open("../Respuestas(ArchivosCSV)/ResultadoPregunta3a.csv");
     resultado<<"Nombre De Chofer Inactivo, Numero De Licencia De Vehiculo, Numero De Servicios Realizados, Numero De Servicios Realizados = "
      << servicios <<",Cantidad de choferes inactivos = "<<CNA.size()<<"\n";    	 	
     
    for(auto const& u:orden) resultado<<"\""<<idchofer[u.first]<<"\""<<","<<u.first<<","<<u.second<<'\n';

    resultado.close();

    
    orden.erase(remove_if(orden.begin(), orden.end(), [](const pair<string, int>& p){return p.second==0;}), orden.end());
    
    
 
    resultado.open("../Respuestas(ArchivosCSV)/ResultadoPregunta3b.csv");
    resultado<<"Nombre De Chofer Inactivo, Numero De Licencia De Vehiculo, Numero De Servicios Realizados, Numero De Servicios Realizados = "
      << servicios <<",Cantidad de choferes inactivos = "<<CNA.size()<<"\n";    	 	
     
    for(auto const& u:orden) resultado<<"\""<<idchofer[u.first]<<"\""<<","<<u.first<<","<<u.second<<'\n';

    resultado.close();

}
