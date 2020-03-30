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
  string line , nombre , id;
  nombre.resize(27);
  map<string,string> idchofer;
  map<string,int> NS;//Numero de servicios por chofer
  vector<pair<string,double> > orden; // para ordenar los datos
 
 
  ifstream in("../TAXI_NY/driver.csv");
 
  
  getline(in , line);
  

  
  while(getline(in , line)){
     stringstream ln(line);
     ln.ignore(10,delim);
     ln.ignore(10,delim);
     
      if(ln.peek()=='\"') ln.ignore();
      ln.read( &nombre[0], 27 );
     
     ln.ignore(10,delim);
     ln.ignore(100,delim);
     getline(ln,id,delim);
     
     NS[id]=0;
     idchofer[id]=nombre;
    
   }
  
  
  ifstream on("../TAXI_NY/service.csv");
  
  getline(on , line);

  while(getline(on , line) ){
     stringstream ss(line);
     ss.ignore(100,delim);
     getline(ss,id,delim);
     if(NS.find(id)!=NS.end()) NS[id]+=1;
    }

 
  
  for (const auto& u:NS) 
  {
    orden.emplace_back(u.first, u.second);
  }

  sort(orden.begin(), orden.end(),
        [](const pair<string, double>& p1, const pair<string, double>&p2)
          { return p1.second > p2.second; });  
	
  
  ofstream resultado;
  resultado.open ("../Respuestas(ArchivosCSV)/ResultadoPregunta2.csv");
  resultado<<"Nombre De Los Choferes, Numero De Licencia De Vehiculo,  Numero De Servicios Realizados\n";    

  int c=0;
  
  for(const auto&u : orden) {

    if(c==10) break;
    resultado<<"\""<<idchofer[u.first]<<"\""<<","<< u.first <<","<<u.second<<'\n';
    c++;
  
  }
  
  resultado.close();  
  
  return 0;
}
