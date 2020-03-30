#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <cmath> 
#include <algorithm>   
#include <vector>

using namespace std;

int main() {
  string line, nombre, id, id2, headers;	
  ifstream in("../TAXI_NY/driver.csv");
  const char delim=',';
  getline(in , line);

  while(getline(in , line) && nombre!="PAULINO,RAMON"){
     stringstream ln(line);
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     ln.ignore();
     ln>>nombre;
     ln.ignore(100,delim);
     ln.ignore(100,delim);
     getline(ln,id,delim);
    }
  
  
  ifstream on("../TAXI_NY/service.csv");
 
  ofstream resultado;
  resultado.open ("../Respuestas(ArchivosCSV)/ResultadoPregunta1.csv");

  getline(on , headers);
  resultado<<headers<<'\n';		
  
  
  while(getline(on , line) ){
     stringstream ss(line);
     ss.ignore(100,delim);
     getline(ss,id2,delim);
     if(id2 ==id)  resultado<<line<<'\n';
	}
 	resultado.close();	
  return 0;		

}
