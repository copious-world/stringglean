#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <list>
#include <set>
#include <unordered_set>
#include <string>
#include <ghc/filesystem>
//

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


// .def .Umarked topicBox_${.Index}
// 
/*
.{--.for=i.from$refs-- <a $lowerFillerRefAttributes[i]>
				$lowerFillerRef[i]
			</a> --}
*/
 void extract_defs(const string &template_str,set<string> &construct) {

 }

void parse_out_interpreters(const string &template_str,const set<string> &tmplt_defs,list<string> &split_headers) {

}


string instantiate(const string &header,TransTable &trans_table) {
	string output = header;
	return(output);
}

void instantiate_template(map<string,string> &value) {
	//
	string substs = slurp(value["values"]);
	TransTable trans_table = json_lite_load_to_ttable(substs);
	string template_str = slurp(value["template"]);
	string output_file = value["to"];
	//
	set<string> tmplt_defs;
	extract_defs(template_str,tmplt_defs);
	//
	list<string> split_headers;
	parse_out_interpreters(template_str,tmplt_defs,split_headers);
	//
	string output = "";
	for ( string header : split_headers ) {
		output += instantiate(header,trans_table);
	}
	dump(output_file,output);
}



#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
#include <getopt.h>

int
main(int argc, char **argv) {

	map<string,string> cmd_line_map = { { "values", "test.subst" }, { "template", "./t_index.html" }, { "to", "./index.html" } };

	int option_index;
	static struct option long_options[] = {
		{"values",		required_argument, 0,  0 },
		{"template",	required_argument, 0,  0 },
		{"to",  		required_argument, 0,  0 },
		{0,         	0,                 0,  0 }
	};
	
	while (1) {

		int c = getopt_long(argc, argv, "v:s:t:", long_options, &option_index);
		if ( c == -1 ) break;

		switch ( c ) {
			case 0: {
				if ( optarg ) {
					cmd_line_map[long_options[option_index].name] = optarg;
				}
				break;
			}

		case 'v':
				if ( optarg ) {
					cmd_line_map[long_options[0].name] = optarg;
				}
			break;

		case 's':
				if ( optarg ) {
					cmd_line_map[long_options[1].name] = optarg;
				}
			break;

		case 't':
				if ( optarg ) {
					cmd_line_map[long_options[2].name] = optarg;
				}
			break;

		case '?':
			break;

		default:
			printf("?? getopt returned character code 0%o ??\n", c);
		}
	}

	// ---- ---- ---- ---- ---- ----
	print_table(cmd_line_map);
	//
	try {
		instantiate_template(cmd_line_map);
	} catch( exception e ) {
		cout << "file error" << e.what() << endl;
	}

	exit(EXIT_SUCCESS);
}