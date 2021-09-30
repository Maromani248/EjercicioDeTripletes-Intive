#include <iostream>
#include <vector>
using namespace std;

//Struct que contiene una vector de string y la cantidad correspondiente.
struct par {
	vector<string> triplete;
	int cantidad;
};

//*******************************************************************************************************
//Funciones auxiliares para mostrar vectores

//Muestra el vector de vectores
void mostrar_LL(vector<vector<string>> &LL){
	
	for(vector<string> x:LL){
		cout << "( ";
		for(string y:x){
			cout << y << " ";
		}
		cout << ")";
		cout << endl;
	}
	
}
	
//Muestra el vector de usuarios	
void mostrar_vector_user(vector<string> L_user){
	
	for(string x:L_user){
		cout << x << " ";
	}
	cout << endl;
	
}	
	
//Muestra un vector
void mostrar_vector(vector<string> v){
	cout<<"[";
	for(auto x : v){
		cout<<x<<",";
	}
	cout<<"]";
}
	
//*******************************************************************************************************
//Funciones auxiliares para la funcion eliminar_repetidos_user
	
//Busca el menor de un vector
vector<string>::iterator my_menor_element(vector<string> &L){
	
	auto aux = L.begin();
	
	for(auto it = L.begin(); it!=L.end(); ++it) {
		if(*it<*aux){
			aux = it;
		}
	}
	
	return aux;
	
}
	
//Ordena un vector
void basic_sort(vector<string> &L){
	
	vector<string> L2;
	
	do{
		auto it = my_menor_element(L);
		L2.push_back(*it);
		L.erase(it);
	}while(!L.empty());
	
	L = L2; 
	
}

//*******************************************************************************************************	
	
//Elimina los elementos repetidos de un vector
void eliminar_repetidos_user(vector<string> &L){
	
	basic_sort(L);
	
	vector<string>::iterator it = L.begin();
	vector<string>::iterator it2 = it; it2++;
	
	while(it2 != L.end() && it != L.end()){
		if(*it == *it2){
			it = L.erase(it);
			it2 = it; it2++;
		}else{
			it++;
		}
	}
	
}

//Crea un vector compuesto por todos los usuarios 	
vector<string> cargar_usuarios(vector<vector<string>> &LL){
	
	vector<string> L_user;
	
	for(vector<string> x:LL){
		int contador = 0;
		for(string y:x){
			if(contador == 0){
				L_user.push_back(y);
				contador++;
			}
		}
	}
	
	eliminar_repetidos_user(L_user);
	
	return L_user;
	
}
	
//Crear un vector con todas las paginas ordenadas
vector<vector<string>> crear_vector_pages(vector<vector<string>> LL, vector<string> L_user){
	
	vector<vector<string>> L_aux;	
	
	for(int j=0; j!=L_user.size(); j++){
		vector<string> L_aux2;
		for(int i=0; i!=LL.size(); i++){ 
			if(L_user[j] == (LL[i])[0]){
				L_aux2.push_back((LL[i])[2]);
			}
		}
		L_aux.push_back(L_aux2);
	}
	
	return L_aux;
	
}	

//*******************************************************************************************************
//Funciones auxiliares para la funcion crear_lista_pares
//Se fija si el vector v esta contenido en L_pages
bool esta_contenido(vector<string> v, vector<string> L_pages){
	for(int i=0; i<L_pages.size(); i++) {
		if(L_pages[i] == v[0]){
			if(L_pages[i+1] == v[1]){
				if(L_pages[i+2] == v[2]){
					return true;
				}
			}
		}
	}
	return false;
}
	
//Crea los tripletes 
vector<par> armar_tripletes(vector<string>v ,vector<vector<string>> L_pages){
	vector<par> tripleteList;
	
	for(int i=0; i<v.size(); i++) {
		if(i < (v.size() - 2)){
			int cont = 1;
			vector<string> T_auxiliar;
			int x = i;
			T_auxiliar.push_back(v[x]);
			x++;
			T_auxiliar.push_back(v[x]);
			x++;
			T_auxiliar.push_back(v[x]);
			
			for(int j=0; j<L_pages.size(); j++) {
				if (esta_contenido(T_auxiliar, L_pages[j]) == true){
					cont++;
				}
			}
			
			par p_aux;
			p_aux.triplete = T_auxiliar;
			p_aux.cantidad = cont;
			tripleteList.push_back(p_aux);
		}
		
	}
	
	return tripleteList;
}
	
//Crea una lista de pares conteniendo una lista de paginas y la cantidad que aparecen
vector<par> crear_lista_pares(vector<vector<string>> L_pages){
	vector<par> VP_aux;
	for(int j=0;j<L_pages.size();j++) {
		vector<vector<string>> aux_pages;
		for(int i= j+1 ;i<L_pages.size();i++) { 
			aux_pages.push_back(L_pages[i]);
		}
		vector<par>  VPtrip = armar_tripletes(L_pages[j], aux_pages);
		for(int k=0;k<VPtrip.size();k++) { 
			VP_aux.push_back(VPtrip[k]);
		}
	}
	return VP_aux;
}

//*******************************************************************************************************
//Funciones auxiliares para la funcion eliminar_pares_repetidos
bool vectores_iguales(vector<string>v1, vector<string> v2){
	if(v1.size() != v2.size()){
		return false;
	}
	for(int i=0;i<v1.size();i++) { 
		if(v1[i] != v2[i]){
			return false;
		}
	}
	return true;
}

//Elimina los vectores repetidos
vector<par>  eliminar_pares_repetidos(vector<par> &v){
	vector<par> sin_reps;
	for(int i=0;i<v.size();i++) {
		bool flag = false;
		for(auto x : sin_reps){
			if(vectores_iguales((v[i]).triplete, x.triplete)){
				flag = true;
			}
		}
		if(flag == false){
			sin_reps.push_back(v[i]);
		}
	}
	return sin_reps;
}

//Busca el mayor de todos los pares dentro del vector
auto buscar_mayor(vector<par> &VPares){
	int mayor = 0;
	auto itaux = VPares.begin();
	for(auto it = VPares.begin(); it != VPares.end(); ++it){
		//		int cant = (*it).cantidad;
		if ((*it).cantidad > mayor){
			mayor = (*it).cantidad;
			itaux = it;
		}
	}
	return itaux;
}

//Define los 10 tripletes mas visitados
vector<vector<string>> diez_mayores(vector<par>VPares){
	vector<vector<string>> Resultado;
	for(int i=0;i<10;i++) { 
		if(VPares.size() != 0){
			auto itaux = buscar_mayor(VPares);
			Resultado.push_back((*itaux).triplete);
			VPares.erase(itaux);
		}
	}
	return Resultado;
}

int main() {
	vector<vector<string>> LL = {
		{"A","12:00pm","1"},
		{"A","12:02pm","2"},
		{"A","12:03pm","3"},
		{"A","12:04pm","4"},
		{"B","12:30pm","4"},
		{"B","12:32pm","5"},
		{"B","12:34pm","6"},
		{"C","12:30pm","1"},
		{"C","12:32pm","2"},
		{"C","12:34pm","3"},
	};
	
	
	
	//Pruebas
	vector<string> Vector_usuarios = cargar_usuarios(LL);
	//mostrar_vector_user(Vector_usuarios);
	
	vector<vector<string>> L_pages = crear_vector_pages(LL,Vector_usuarios);
//	mostrar_LL(L_pages);
	
	vector<par> VPares;
	VPares = crear_lista_pares(L_pages);
	
//	for(int i=0;i<VPares.size();i++) { 
//		mostrar_vector(VPares[i].triplete);
//		cout<<" "<<VPares[i].cantidad<<endl;
//	}*/
	
	VPares = eliminar_pares_repetidos(VPares);
	
	cout << "El top 10 de tripletes mas visitados es: " << endl;
	vector<vector<string>> top_10 = diez_mayores(VPares);
	for(auto x : top_10){
		cout<<"[";
		for(auto y : x){
			cout<<y<<", ";
		}
		cout<<"]"<<endl;
	}
	
	return 0;
}


