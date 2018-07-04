#include "SATGeneration.hpp"
#include <math.h>
#include <cstring>
#include <time.h>


using namespace std;

//helper function to parse inputs
namespace helper{
	char* getCmdOption(char ** begin, char ** end, const std::string & option)
	{
		char ** itr = std::find(begin, end, option);
		if (itr != end && ++itr != end)
		{
			return *itr;
		}
		return 0;
	}

	bool cmdOptionExists(char** begin, char** end, const std::string& option)
	{
		return std::find(begin, end, option) != end;
	}
}

int main(int argc, char* argv[]){
	bool quiet = false;
	int V=100;
	int C=400;
	int K=3;
	int S=1;
	double P=2.75;
	double B=3.2;
	char* f =(char*)"";
	bool U=true;
	bool output=false;
	char* g=(char*)"p";
	if (helper::cmdOptionExists(argv, argv+argc,"-q")) quiet=true;
	if (helper::cmdOptionExists(argv, argv+argc,"-g")) {
		g=helper::getCmdOption(argv, argv+argc, "-g");
	}
	if (helper::cmdOptionExists(argv, argv+argc,"-v")) {
		char* v=helper::getCmdOption(argv, argv+argc, "-v");
		V=atoi (v);
	}
	if (helper::cmdOptionExists(argv, argv+argc,"-c")) {
		char* c=helper::getCmdOption(argv, argv+argc, "-c");
		C=atoi (c);
	}
	if (helper::cmdOptionExists(argv, argv+argc,"-k")) {
		char* k=helper::getCmdOption(argv, argv+argc, "-k");
		K=atoi (k);
	}
	if (helper::cmdOptionExists(argv, argv+argc,"-p")) {
		char* p=helper::getCmdOption(argv, argv+argc, "-p");
		P=atof (p);
	}
	if (helper::cmdOptionExists(argv, argv+argc,"-b")) {
		char* b=helper::getCmdOption(argv, argv+argc, "-b");
		B=atof(b);
	}
	if (helper::cmdOptionExists(argv, argv+argc,"-f")) {
		f=helper::getCmdOption(argv, argv+argc, "-f");
		if(f!="") output=true;
	}
	if (helper::cmdOptionExists(argv, argv+argc,"-u")) {
		char* u=helper::getCmdOption(argv, argv+argc, "-u");
		if(strcmp(u,"1")==0) U=true;
	}
	if (helper::cmdOptionExists(argv, argv + argc, "-s")) {
		char* s = helper::getCmdOption(argv, argv + argc, "-s");
		S = atoi(s);
	}
	else
		S = time(NULL);
	if(quiet==false) {
		printf("SAT Generator for power-law distributed variable frequencies\n------------------------------------------------------------\n");
		printf("-g d|p|u \n\tchoose between power-law distributed variables (p) or double power-law (d) or uniform (u) \n");
		printf("-v <number of variables>\n");
		printf("-c <number of clauses>\n");
		printf("-k <clause length>\n\tfor double power-law this is the average clause length\n");
		printf("-p <power-law exponent of variables>\n");
		printf("-b <power-law exponent of clauses>\n\tonly for double power-law\n");
		printf("-f <output file>\n\tin cnf-format, the ending will be added automatically\n");
		printf("-u 0|1\n\tshould variables be unique per clause(1) or not(0)\n");
		printf("-q \n\tstart quietly\n");
		printf("-s \n\tseed value (int)\n");
		printf("Chosen variables:\n\t-g:%s\n\t-v:%i\n\t-c:%i\n\t-k:%i\n\t-p:%f\n\t-b:%f\n\t-f:%s\n\t-u:%d\n\t-s:%i\n------------------------------------------------------------\n",g,V,C,K,P,B,f,U,S);
	}

	if (strcmp(g,"d")==0) {
		Formula* form = SATGeneration::GenerateDoublePowerLaw(B,P,C,V,K,U,S);
		if(output){
			string s = f + string(".cnf");
			std::ofstream outfile (s.c_str());
			form->saveFormula(outfile);
			outfile.close();
		}
	}
	else if(strcmp(g,"p")==0) {
		Formula* form = SATGeneration::GeneratePowerLaw(K,P,C,V,U,S);
		if(output){
			string s = f + string(".cnf");
			std::ofstream outfile (s.c_str());
			form->saveFormula(outfile);
			outfile.close();
		}
	}
	else if(strcmp(g,"u")==0) {
		Formula* form = SATGeneration::GenerateUniform(K,C,V,U,S);
		if(output){
			string s = f + string(".cnf");
			std::ofstream outfile (s.c_str());
			form->saveFormula(outfile);
			outfile.close();
		}
	}
	else printf("invalid generator\n");

	return 0;
}

