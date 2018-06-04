#ifndef CLAUSE_HPP_
#define CLAUSE_HPP_

#include <list>

class Clause {
	private:
		std::list<std::pair<int,bool> > clause;
	public:
		//normal constructor, empty clause
		Clause(){
		}
		//copy constructor
		Clause(const Clause* cl){
			const std::list<std::pair<int,bool> >* parentClause = cl->getClause();
			for(std::list< std::pair<int,bool> >::const_iterator it=parentClause->begin();it!=parentClause->end();it++){
				this->addLiteral(it->first,it->second);
			}
		}
		~Clause(){
			clause.clear();
		}
		bool contains(int v) const{
			bool c = false;
			if (clause.empty()) return false;
			for(std::list<std::pair<int,bool> >::const_iterator it=clause.begin();it!=clause.end();it++){
				if(it->first==v){
					c=true;
					break;
				}
			}
			return c;
		};
		void addLiteral(int v, bool b){
			clause.push_back(std::make_pair(v,b));
		}
		void deleteLiteral(int v, bool b){
			clause.remove(std::make_pair(v,b));
		}
		int getSize() const{
			return clause.size();
		};
		void saveClause(std::ofstream& stream) const{
			for(std::list< std::pair<int,bool> >::const_iterator iter=clause.begin();iter!=clause.end();iter++){
				if(iter->second==false) stream << "-";
				stream << ((iter->first)+1) << " ";
			}
			stream << "0\n";
		}
		const std::list<std::pair<int,bool> >* getClause() const{
			return &clause;
		}
};



#endif
