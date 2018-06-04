#ifndef SATGENERATION_HPP_
#define SATGENERATION_HPP_

#undef min
#undef max
#include <Math.h>
#include <algorithm>
#include <random>
#include "Formula.hpp"
#include <map>

class SATGeneration {
public:
	//function to generate power-law distributed clauses and variables
	static Formula* GenerateDoublePowerLaw (double betaC, double betaV, int clauses, int variables, int avgdeg, bool unique, int s){
		Formula* f=new Formula(variables);
		std::vector<double> CWeights, VWeights;
		std::map<double, int> TC, TV;
		CWeights.resize(clauses);
		VWeights.resize(variables);
		double CSum, VSum;
		CSum=0;
		VSum=0;

		double betaCNorm,betaVNorm;
		betaCNorm = 1/(betaC-1);
		betaVNorm = 1/(betaV-1);

		for(int i=0;i<clauses;++i){
			CWeights[i]=pow((clauses/(i+1)),betaCNorm);
			CSum+=CWeights[i];
			TC[CSum]=i;
		}
		for(int i=0;i<variables;++i){
			VWeights[i]=pow((variables/(i+1)),betaVNorm);
			VSum+=VWeights[i];
			TV[VSum]=i;
		}
		int cl=0;
		int var=0;
		
		generator.seed(s);
		std::uniform_real_distribution<double> varDist(0.0,VSum);
		std::uniform_real_distribution<double> claDist(0.0,CSum);
		std::uniform_int_distribution<int> litDist(0,1);
		std::vector<Clause*> id;
		id.resize(clauses);
		for(int i=0;i<clauses;++i){
			id[i]=f->addClause();
		}
		for(int i=0;i<avgdeg*clauses;++i){
			do{
				double c = claDist(generator);
				cl=TC.lower_bound(c)->second;
				double v = varDist(generator);
				var=TV.lower_bound(v)->second;
			}while(unique && f->contains(id[cl],var));
			int flip = litDist(generator);
			if(flip>0)
				f->addLiteral(id[cl],var,false);
			else
				f->addLiteral(id[cl],var,true);
		}
		return f;
	}

	//function to generate Power-law random k-SAT
	static Formula* GeneratePowerLaw (int k, double beta, int clauses, int variables, bool unique, int s){
			Formula* f=new Formula(variables);
			std::vector<double> CWeights, VWeights;
			std::map<double, int> TC, TV;
			CWeights.resize(clauses);
			VWeights.resize(variables);
			double CSum, VSum;
			CSum=0;
			VSum=0;

			double betaNorm;
			betaNorm = 1/(beta-1);
						for(int i=0;i<variables;++i){
				VWeights[i]=pow((variables/(i+1)),betaNorm);
				VSum+=VWeights[i];
				TV[VSum]=i;
			}
			int cl=0;
			int var=0;
			

			generator.seed(s);
			std::uniform_real_distribution<double> varDist(0.0,VSum);
			std::uniform_int_distribution<int> litDist(0,1);
			
			for(int i=0;i<clauses;++i){
				Clause* cl=f->addClause();
				for(int j=0; j<k; ++j){
					do {
						double v = varDist(generator);
						var=TV.lower_bound(v)->second;
					}while(unique && f->contains(cl,var));
					int s = litDist(generator);
					if(s>0)
						f->addLiteral(cl,var,false);
					else
						f->addLiteral(cl,var,true);
				}
			}
			return f;
		}
		
	//function to generate Uniform Random k-SAT
	static Formula* GenerateUniform (int k, int clauses, int variables, bool unique, int s){
			Formula* f=new Formula(variables);
			std::vector<double> CWeights, VWeights;
			std::map<double, int> TC, TV;
			CWeights.resize(clauses);
			VWeights.resize(variables);
			double CSum, VSum;
			CSum=0;
			VSum=0;

			for(int i=0;i<variables;++i){
				VWeights[i]=1;
				VSum+=VWeights[i];
				TV[VSum]=i;
			}
			int cl=0;
			int var=0;
			
			generator.seed(s);
			std::uniform_real_distribution<double> varDist(0.0,VSum);
			std::uniform_int_distribution<int> litDist(0,1);
			
			for(int i=0;i<clauses;++i){
				Clause* cl=f->addClause();
				for(int j=0; j<k; ++j){
					do {
						double v = varDist(generator);
						var=TV.lower_bound(v)->second;
					}while(unique && f->contains(cl,var));
					int s = litDist(generator);
					if(s>0)
						f->addLiteral(cl,var,false);
					else
						f->addLiteral(cl,var,true);
				}
			}
			return f;
		}
		
protected:
  static std::mt19937 generator;
  
};

std::mt19937 SATGeneration::generator;

#endif
