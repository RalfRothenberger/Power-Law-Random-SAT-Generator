#ifndef FORMULA_HPP_
#define FORMULA_HPP_

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include "Clause.hpp"

class Formula {
private:
	std::set<Clause*> clauses;
	unsigned int n;
	unsigned int m;
public:
	Formula(int v);
	virtual ~Formula();

	Clause* addClause();
	void addLiteral(Clause* cl, int v, bool b);
	bool contains(Clause* cl, int v) const;
	void deleteClause(Clause* cl);
	int getVariables() const {return n;};
	const std::set<Clause*>* getClauses() const {return &clauses;};
	int getSize() const {return clauses.size();};
	void saveFormula(std::ofstream& stream) const;
};
#endif
