#include <iostream>
#include <vector>

using namespace std;

class Articulo{
	public:		
		string nombre, categoria;
		vector<string> tallas;
		double precio;
		int cantidad, porcentajeDescuento;
		
		Articulo(string _nombre, double _precio, int _cantidad, int _porcentajeDescuento, string _categoria){
			nombre = _nombre;
			precio = _precio;
			cantidad = _cantidad;
			porcentajeDescuento = _porcentajeDescuento;
			categoria = _categoria;
		}
		
};


class Tienda{
	public:
	vector<string> categorias;
	vector<Articulo*> articulos;
	
	~Tienda(){
		for(int i=0; i < articulos.size(); i++){
			delete articulos[i];
		}
		articulos.clear();
	}
	
	void agregarCategoria(string nombre){
		categorias.push_back(nombre);
	}
	
	void agregarArticulo(string nombre, int precio, int cantidad, int porcentajeDescuento, string categoria){
		articulos.push_back(new Articulo(nombre,precio,cantidad,porcentajeDescuento,categoria));
	}
	
	void eliminarArticulo(int n){
		delete articulos[n];
		articulos.erase(articulos.begin()+n);
	}
	
	void estadisticasGenerales(){
		int unidadesTotales = 0, precioSinDesc = 0;
		for(int i=0; i < categorias.size(); i++){
			int unidades = 0, precioTotal = 0, productosUnicos = 0;

			for(int j=0; j < articulos.size(); j++){
				cout << "[" <<  articulos[j]->categoria << "]" << endl;
				if(articulos[j]->categoria == categorias[i]){
					unidades += articulos[j]->cantidad;
					precioTotal += articulos[j]->precio * (articulos[j]->porcentajeDescuento*0.01);
					precioSinDesc += articulos[j]->precio;
					if(articulos[j]->cantidad == 1)
						productosUnicos++;
				}
			}			
			
			cout << "Unidades: " << unidades << endl
			<< "Precio Total por esta Categoria: " << precioTotal << endl
			<< "Productos Unicos: " << productosUnicos << endl << endl;
			
			cout << "----------------------------------------------------";
			
			unidadesTotales += unidades;
		}
		
		cout << "----------------------------------------------------" << endl;
		cout << "Unidades totales en la tienda: " << unidadesTotales << endl
		<< "Precio total sin descuento: " << precioSinDesc << endl;
	}
	
	void buscarArticulo(string categoria, string talla){
		int cont = 1;
		for(int i=0; i < articulos.size(); i++){
			if(articulos[i]->tallas[0] == talla || articulos[i]->categoria == categoria){
				cout << cont << ". " << articulos[i]->nombre << endl;
				cont++;
			}
		}
	}
};



int main(int argc, char** argv) {
	Tienda* t = new Tienda();
	int opcion;
	while(true){
		cout << "1. Agregar Categorias" << endl
		<< "2. Agregar Articulo" << endl
		<< "3. Modificar Articulo" << endl
		<< "4. Eliminar Articulo" << endl
		<< "5. Estadisticas Generales" << endl
		<< "6. Busqueda por categoria y talla" << endl
		<< "7. Salir" << endl
		<< "Ingrese opcion: ";
		cin >> opcion; 
		
		cout << endl;
		
		switch(opcion){
			case 1:{
				string nombre;
				cout << "Ingrese nombre de categoria: ";
				cin >> nombre;
				t->agregarCategoria(nombre);
				cout << endl << "Categoria creada!" << endl;
				break;
			}
			case 2:{
				string nombre, talla, categoria;
				double precio;
				int cantidad, porcentajeDescuento;
				cout << "Ingrese nombre del articulo: ";
				cin >> nombre;
				cout << "Ingrese talla disponible: ";
				cin >> talla;
				cout << "Ingrese precio: ";
				cin >> precio;
				cout << "Ingrese cantidad en inventario: ";
				cin >> cantidad;
				cout << "Ingrese porcentaje % de descuento: ";
				cin >> porcentajeDescuento;
				
				if(t->categorias.size() == 0){
					cout << endl << "No hay categorias existentes, create una." << endl;
				} else {
					int op;
					for(int i=0; i < t->categorias.size(); i++){
						cout << i+1 << ". " << t->categorias[i] << endl;
					}
					cout << "Seleccione categoria: ";
					cin >> op;
					op--;
					categoria = t->categorias[op];
								
					
					t->agregarArticulo(nombre,precio,cantidad,porcentajeDescuento,categoria);
					t->articulos[t->articulos.size()-1]->tallas.push_back(talla);			
					
					cout << endl << "Articulo creado!" << endl;
				}
				break;
			}
			case 3:{
				if(t->articulos.size() == 0){
					cout << "No hay articulos en la tienda..." << endl;
				} else {
					int op;
					for(int i=0; i < t->articulos.size(); i++){
						cout << i+1 << ". " << t->articulos[i]->nombre << endl;
					}
					cout << "Seleccione articulo a modificar: ";
					cin >> op;
					op--;
					
					string nombre,categoria;
					double precio;
					int cantidad, porcentajeDescuento;
					cout << "Ingrese nombre del articulo: ";
					cin >> nombre;
					cout << "Ingrese precio: ";
					cin >> precio;
					cout << "Ingrese cantidad en inventario: ";
					cin >> cantidad;
					cout << "Ingrese porcentaje % de descuento: ";
					cin >> porcentajeDescuento;
					
					t->articulos[op]->nombre = nombre;
					t->articulos[op]->precio = precio;
					t->articulos[op]->cantidad = cantidad;
					t->articulos[op]->porcentajeDescuento = porcentajeDescuento;
					
					cout << endl << "Articulo modificado!" << endl;
				}
				
				
					
				
				
				break;
			}
			
			
			case 4:{
				int n;
				for(int i=0; i < t->articulos.size(); i++){
					cout << i+1 << ". " << t->articulos[i]->nombre << endl;
				}
		
				cout << "Seleccione articulo a eliminar: ";
				cin >> n;
				
				t->eliminarArticulo(n);
				cout << endl << "Articulo eliminado!" << endl;
				
				break;
			}
			case 5:{
				t->estadisticasGenerales();
				break;
			}
			
			case 6:{
				string categoria = "", talla = "";
				char resp1, resp2;
				cout << "Desea buscar por categoria? [s/n]: ";
				cin >> resp1;
				cout << "Desea buscar por talla? [s/n]: ";
				cin >> resp2;
				
				if(resp1 == 's' || resp1 == 'S'){
					cout << endl;
					int op;
					for(int i = 0; i < t->categorias.size(); i++){
						cout << i+1 << ". " << t->categorias[i] << endl;
 					}
 					cout << "Seleccione categoria: ";
 					cin >> op;
 					op--;
 					
 					categoria = t->categorias[op];
				}
				
				if(resp2 == 's' || resp2 == 'S'){
					cout << endl;
					cout << "Ingrese talla a buscar: ";
					cin >> talla;
				}
				
				cout << endl << "Articulos encontrados: " << endl;
				t->buscarArticulo(categoria,talla);
				break;
			}
			
			case 7:{
				delete t;
				return 0;
			}
			
			default:{
				cout << "Opcion incorrecta..." << endl;
				break;
			}	
		}
		cout << endl;
	}
	return 0;
}
