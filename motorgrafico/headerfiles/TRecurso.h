#ifndef RECURSO_H
#define RECURSO_H


class TRecurso{
public:
	TRecurso();
	virtual ~TRecurso();
	char* getNombre();
	void setNombre(char* nombre);
	void cargarFichero(char* nombre);


private:	

	char* nombre;

} ;

#endif //RECURSO_H