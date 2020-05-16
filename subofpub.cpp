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


void ensure_dir(string &dest) {
	//
	if ( fs::create_directories(dest) ) {
		//cout << "new directory created: " << dest << endl;
	}
	//
}


class TransTable {
public:
	TransTable() {}
	virtual ~TransTable() {}
	
	list<string> file_types;
	map<string,string> dest_table;
};

TransTable json_lite_load_to_ttable(string &pubfile) {
	TransTable settable;
	//
	string jform = trim(pubfile);
	//
	string file_list = json_lite_extract_keyed_body("file_types",pubfile);
	settable.file_types = uni_splist(file_list,"\n");
	//
	string dest_table = json_lite_extract_keyed_body("destinations",pubfile);
	settable.dest_table = double_splits(dest_table," >-> ","\n");
	//
	return settable;
}


void process_transfer_file(string &dir_path,const string &fpath,string &dest,string &app) {
	string source = dir_path + '/' + fpath;
	cout << source << endl;
	do_replace(dest, "$app", app);
	cout << dest << endl;
	ensure_dir(dest);
	fs::copy(source,dest,fs::copy_options::overwrite_existing);
	cout << "------------------" << endl;
}


//subofpub -source ../shmlogger -to gateway

int main(int argc, char **argv) {
	//
	string package_name = "package_name";
	string dir_path = ".";
	string app = "app";
	
	map<string,string> cmd_line_map = { { "package", "test" }, { "source", "." }, { "to", "." } };
	//
	load_cmd_line(cmd_line_map,argc,argv);
	
	// print_table(cmd_line_map);
	
	string package = cmd_line_map["package"];
	
	dir_path = cmd_line_map["source"];
	
	string pubfile_path = dir_path + '/' +  package + ".pub";
	string pubfile = slurp(pubfile_path);
	
	TransTable trans_table = json_lite_load_to_ttable(pubfile);
	
	app = cmd_line_map["to"];
	
	//print_table(trans_table.dest_table);
	for ( string fileType : trans_table.file_types ) {
		auto const& [ftype,fpath] = uni_splist_pair(fileType,":");
		string dest = trans_table.dest_table[ftype];
		process_transfer_file(dir_path,fpath,dest,app);
	}
	//
	return(0);
}
