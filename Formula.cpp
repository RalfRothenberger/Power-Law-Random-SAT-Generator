#include "Formula.hpp"
using namespace std;

Formula::Formula(int v) {
	n=v;
	m=0;
}

Formula::~Formula() {
	for(std::set<Clause*>::iterator it=clauses.begin();it!=clauses.end();++it){
		delete *it;
	}
	clauses.clear();
}

Clause* Formula::addClause() {
	Clause* cl=new Clause();
	clauses.insert(cl);
	m+=1;
	return cl;
}
void Formula::deleteClause(Clause* cl){
	clauses.erase(cl);
	delete cl;
}

void Formula::addLiteral(Clause* cl, int v, bool b){
	cl->addLiteral(v,b);
}

bool Formula::contains(Clause* cl, int v) const{
	return cl->contains(v);
}

void Formula::saveFormula(std::ofstream& stream) const{
	//preamble of a .cnf file
	stream << "p cnf " << n << " " << m <<endl;
	for(std::set<Clause*>::iterator it=clauses.begin();it!=clauses.end();++it){
		((Clause*)*it)->saveClause(stream);
	}
}
