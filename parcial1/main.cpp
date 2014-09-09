#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <math.h>
#include <time.h>
#include <algorithm>
using namespace std;

class nodo{
	public:
		string ID;
		int dis;
		int f;
		vector<nodo*> childs;
		nodo *parent;
	public:
		nodo(string ID);
		void generateChilds();
		friend nodo* findByBFS(nodo &ini);
		friend nodo* findByDFS(nodo &ini);
		void setParent(nodo *parent){parent=parent;};
		void printWayToParent();
};

vector<string> Nodos; //Arreglo de los nodos generados
string Fresult = "123804765"; //Resultado esperado
string firstConfig; //Primera Configuracion
bool resultFinded = false; //Resultado encontrado

nodo::nodo(string id){
	ID = id;
	dis = -1;
	childs.clear();
}
void nodo::printWayToParent(){
	nodo* aux = this;
	while(aux->parent!=aux){
		cout << aux->ID << endl;
		aux = aux->parent;
	}
}
void nodo::generateChilds(){
	string id1,id2,id3,id4;
	id1 = id2 = id3 = id4 = ID;
	vector<string> childsAux;
	switch(ID.find('0')){
		case 0:
			swap(id1[0],id1[1]);
			swap(id2[0],id2[3]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			break;
		case 1:
			swap(id1[1],id1[0]);
			swap(id2[1],id2[4]);
			swap(id3[1],id3[2]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			childsAux.push_back(id3);
			break;
		case 2:
			swap(id1[2],id1[1]);
			swap(id2[2],id2[5]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			break;
		case 3:
			swap(id1[3],id1[0]);
			swap(id2[3],id2[4]);
			swap(id3[3],id3[6]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			childsAux.push_back(id3);
			break;
		case 4:
			swap(id1[4],id1[1]);
			swap(id2[4],id2[5]);
			swap(id3[4],id3[7]);
			swap(id4[4],id4[3]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			childsAux.push_back(id3);
			childsAux.push_back(id4);
			break;
		case 5:
			swap(id1[5],id1[2]);
			swap(id2[5],id2[4]);
			swap(id3[5],id3[8]);
			childsAux.push_back(id1);
			childsAux.push_back(id3);
			childsAux.push_back(id4);
			break;
		case 6:
			swap(id1[6],id1[3]);
			swap(id2[6],id2[7]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			break;
		case 7:
			swap(id1[7],id1[6]);
			swap(id2[7],id2[4]);
			swap(id3[7],id3[8]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			childsAux.push_back(id3);
			break;
		case 8:
			swap(id1[8],id1[7]);
			swap(id2[8],id2[5]);
			childsAux.push_back(id1);
			childsAux.push_back(id2);
			break;
	}
	nodo *aux;
	for(vector<string>::iterator it = childsAux.begin();it!=childsAux.end();++it){
		if(!(find(Nodos.begin(), Nodos.end(),*it)!=Nodos.end()))
		{
			aux = new nodo(*it);
			aux->setParent(aux);
			childs.push_back(aux);
			Nodos.push_back(*it);
		}
	}
}

nodo* findByBFS(nodo &ini){
	queue<nodo*> Q;
	// ini.dis = 0;
	Q.push(&ini);
	nodo *aux;
	nodo *result;
	while(!Q.empty() && !resultFinded){
		aux = Q.front(); Q.pop();
		aux->generateChilds();
		for(vector<nodo*>::iterator it = aux->childs.begin();it!=aux->childs.end();++it){
			// (*it)->dis=aux->dis+1;
			(*it)->parent = aux;
			Q.push((*it));
			if((*it)->ID==Fresult){resultFinded=true;result = (*it);}
		}
	}
	return result;
};

nodo* findByDFS(nodo &ini){
	vector<nodo*> Q;
	// ini.dis = 0;
	Q.push_back(&ini);
	nodo *aux;
	nodo *result;
	while(!Q.empty() && !resultFinded){
		aux = Q.back(); Q.pop_back();
		aux->generateChilds();
		for(vector<nodo*>::iterator it = aux->childs.begin();it!=aux->childs.end();++it){
			// (*it)->dis=aux->dis+1;
			(*it)->parent = aux;
			Q.push_back((*it));
			if((*it)->ID==Fresult){resultFinded=true;result = (*it);}
		}
	}
	return result;
};

void DFS_VISIT(nodo* ini,unsigned &time,nodo *result){
	time++;
	ini->dis = time;
	ini->generateChilds();
	vector<nodo*>::iterator it=ini->childs.begin();
	while(it!=ini->childs.end() && !resultFinded){
		(*it)->setParent(ini);
		if((*it)->ID!=Fresult && !resultFinded){
			DFS_VISIT(*it,time,result);
		}
		if((*it)->ID==Fresult){result = (*it);resultFinded=true;}
		it++;
	}
	time++;
	ini->f = time;
};

int main(int argc,char const *argv[])
{
	clock_t t;
	firstConfig = "410532786";
	nodo config1(firstConfig);
	config1.setParent(&config1);
	Nodos.push_back(config1.ID);
	t=clock();
	nodo *result = findByBFS(config1);
	// nodo *result = findByDFS(config1);
	t = clock()-t;
	result->printWayToParent();
	cout << endl << "Segundos: " << (float)t/CLOCKS_PER_SEC << endl;
	return 0;
}