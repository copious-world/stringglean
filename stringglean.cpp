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


const unsigned char MIN_EXTRACTION_SIZE = 2;

// ---- ---- ---- ---- ---- ---- ---- ---- ----
//

string decomment(string data) {
	//
	string cfree_str = "";
	for ( auto dat = data.begin(); dat != data.end(); dat++ ) {
		char c = *dat;
		if ( c == '/' ) {
			dat++;
			char c2 = *dat;
			if ( c2 == '/' ) {
				while ( dat != data.end() ) {
					c = *dat;
					if ( c == '\n' ) break;
					dat++;
				}
			} else dat--;
		}
		cfree_str += c;
	}
	return(cfree_str);
}

string drop_multiline_comments(string data) {
	char *tmp = (char *)data.c_str();
	while ( tmp != NULL ) {
		tmp = (char *)strstr(tmp,"/*");
		if ( tmp ) {
			char *e_comment = strstr(tmp,"*/");
			e_comment += 2;
			char *spacer = tmp;
			for ( ; spacer != e_comment; spacer++ ) {
				*spacer = ' ';
			}
			tmp = spacer;
		}
	}
	return(data);
}

string ignore_require_calls(string data) {
	char *tmp = (char *)data.c_str();
	string output = "";
	while ( tmp != NULL ) {
		char *start = tmp;
		tmp = (char *)strstr(tmp,"require(");
		if ( tmp != NULL ) { //
			*tmp++ = 0;
			output += start;
			while ( *tmp != '(' ) {
				tmp++;
			}
			bool inquote = false;
			while ( !inquote ? (*tmp != ')') : true ) {
				if( *tmp == '\'' || *tmp == '\"' ) {
					inquote = !inquote;
				}
				tmp++;
			}
			tmp++;
		} else {
			output += start;
		}
	}
	return(output);
}



//
//
inline string extract_string(char **str,const char *end,char c) {
	char *tmp = *str;
	//
	char dostop = STR_STOP_CHAR(c);
	//
	char *string_start = tmp;
	c  = *tmp;
	while ( (tmp < end) && (c != dostop) ) {
		c = *tmp++;
		if ( c == '\\' ) {
			tmp++; // skip next char
		}
	}
	//
	if ( tmp < end ) {
		tmp--;
		c = *tmp;
		*tmp = 0;
	}
	// //
	string key = "";
	//
	if ( strlen(string_start) > MIN_EXTRACTION_SIZE ) {
		key = strdup(string_start);
	}
	//
	if ( tmp < end ) {
		*tmp++ = c;
		tmp++;
	}
	//
	*str = tmp;
	return(key);
}



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
	string filter_on = "luapp";
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
		string data = decomment(slurp(file_path));
		data = drop_multiline_comments(data);
		data = ignore_require_calls(data);
		//
		//
		char * tmp = (char *)data.c_str();
		const char * end = &(*data.end());
		//
		while ( tmp < end ) {
			//
			char c = *tmp++;
			//
			if ( STRING_START(c) ) {
				// empty string (same delimiter)
				if ( c == *tmp ) { tmp++; continue; }
				//
				// else
				string key = extract_string(&tmp,end,c);
				//
				if ( key.size() ) quote_list[key] = "";
				//
			}
		}
		//
	}
	
	int i = 0;
	for (const auto& [key, ignore] : quote_list) {
		quote_list[key] = to_string(++i);
	}

	list<string> qkeys_hash = keys_n_hash<string>(quote_list);
	//
	cout << join(qkeys_hash,"\n") << endl;
	//
	return(0);
}
