#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <list>
#include <unordered_set>
#include <string>
#include <ghc/filesystem>

using namespace std;
namespace fs = ghc::filesystem;

#include "inlines.h"


list<string> files_of_dir(const string &dir_path,const string &filter_on) {
	list<string> file_list;
	string pat = "." + filter_on;
	for (const auto & entry : fs::directory_iterator(dir_path)) {
		string path = entry.path();
		if ( path.find(pat,1) != string::npos ) {
			file_list.push_back(path);
		}
	}
	return(file_list);
}

int main(int argc, char **argv) {
	//
	string dir_path = ".";
	string out_dir = ".";
	string filter_on = "lua";
	//
	if ( argc > 1 ) {
		dir_path = argv[1];
	}
	if ( argc > 2 ) {
		filter_on = argv[2];
	}
	//
	list<string> pathlist = files_of_dir(dir_path,filter_on);
	//
	map<string,string> quote_list;
	//
	for ( string file_path : pathlist ) {
		//
		string data = slurp(file_path);
		const char *target = "\n";
		//
		list<string> lines = uni_splist(data,target);
		//
		string output = join(lines,target);
		//
		dump(file_path,output);
	}
	
	//
	return(0);
}
