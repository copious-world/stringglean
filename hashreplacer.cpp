#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <list>
#include <unordered_set>
using namespace std;

#define PROCESSING_PARAMETERS true
#define DEFAULT_PARAMS true

#include "inlines.h"
//
/*
//
critical(shmlgr_i,
error(shmlgr_i,
warn(shmlgr_i,
log(shmlgr_i,
info(shmlgr_i,
debug(shmlgr_i,
*/
#define LOG_LEVEL_PREFIXES 6
const char *g_allowed_fronts[LOG_LEVEL_PREFIXES] = {
	"critical(shmlgr_i",
	"error(shmlgr_i",
	"warn(shmlgr_i",
	"log(shmlgr_i",
	"info(shmlgr_i",
	"debug(shmlgr_i"
};

const char *g_logger_id = "shmlgr_i";

inline bool allowed_prefix(string callline) {
	const char *tmp = callline.c_str();
	for ( unsigned char i = 0; i < LOG_LEVEL_PREFIXES; i++ ) {
		const char * pre = g_allowed_fronts[i];
		if ( strncmp(pre,tmp,strlen(pre)) == 0 ) {
			return true;
		}
	}
	return false;
}
//
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
// ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
/*
const int is_bool = 1;
const int is_char = 2;
const int is_int = 3;
const int is_float = 4;
const int is_end = 5;
*/

int custom_type_conversion_finder(const string &parameter) {
	string stmp = parameter;
	stmp = trim(stmp);
	const char *tmp = stmp.c_str();
	if ( strncmp(tmp,"math.floor",10) == 0 ) {
		return(is_int);
	} else if ( strncmp(tmp,"math.round",10) == 0 ) {
		return(is_int);
	} else if ( strncmp(tmp,"tonumber",8) == 0 ) {
		return(is_float);
	} else if ( strncmp(tmp,"(int)",5) == 0 ) {  	// conversion function from user supplied library
		return(is_int);
	} else if ( strncmp(tmp,"to_int_",7) == 0 ) {  // conversion function from user supplied library
		return(is_int);
	} else if ( strncmp(tmp,"(char)",5) == 0 ) {  	// conversion function from user supplied library
		return(is_char);
	} else if ( strncmp(tmp,"to_char_",7) == 0 ) {  // conversion function from user supplied library
		return(is_char);
	} else if ( strncmp(tmp,"(bool)",5) == 0 ) {  	// conversion function from user supplied library
		return(is_char);
	} else if ( strncmp(tmp,"to_bool_",7) == 0 ) {  // conversion function from user supplied library
		return(is_char);
	}
	return(is_float);
}

#define PAR_SEP ".."
string transform_params(const string &params,bool &extend_i,bool &extend_f) {
	//
	extend_i = false;
	extend_f = false;
	//
	//
	const int lggerlen = strlen(g_logger_id);
	string true_params = params.substr(lggerlen + 1);
	//
	list<string> par_list = uni_splist(true_params,PAR_SEP,true);
	//
	list<string> rest_pars = {};
	list<string> rest_float_pars = {};
	list<string> control_pars = {};
	//
	for ( auto par : par_list ) {
		if ( STRING_START(par[0]) ) {
			control_pars.push_back(unstring(par));
		} else {
			const int pt = parse_type_of(par,custom_type_conversion_finder);
			control_pars.push_back("(-" + to_string(pt) + ")");
			if ( pt == is_float ) {
				rest_float_pars.push_back(par);
			} else {
				rest_pars.push_back(par);
			}
		}
	}
	//
	control_pars.push_back("(-" + to_string(is_end) + ")");
	if ( (rest_pars.size() > 0) && (rest_float_pars.size() > 0 ) ) {
		extend_f = true;
		rest_pars.push_back("0xffffffff");
		rest_pars.splice(rest_pars.end(), rest_float_pars);
	} else if ( rest_pars.size() > 0 ) {
		extend_i = true;
	}
	control_pars.splice(control_pars.end(), rest_pars);
	//
	char buffer[16];
	sprintf(buffer,"%u",(unsigned int)control_pars.size());
	string prefix_pars = "shmlgr_i,";
	prefix_pars += buffer;
	prefix_pars += ',';
	return(prefix_pars + join(control_pars,",",true) );
}


void locate_parameter_boundries(string &par_region,unsigned int &first_p,unsigned int &second_p) {
	//
	second_p = (first_p = par_region.find('('))+1;
	unsigned int depth = 1;
	char *start = (char *)par_region.c_str();
	char *tmp = start + second_p;
	start = tmp;
	if ( *tmp != ')' ) {
		while ( depth && *tmp ) {
			char c = *tmp++;
			if ( c == '(' ) depth++;
			else if ( c == ')' ) depth--;
		}
		if ( *tmp ) {
			second_p = first_p + (unsigned int)(tmp - start);
		}
	}
	//
}


int main(int argc, char **argv) {
	//
	string file_path = "test.js";
	char *target = (char *)"debug(";
	string hash_path = "dict.txt";
	string tmplt_str = "$%@%$";
	unsigned int replace_pos = tmplt_str.find('@');
	//
	if ( argc > 1 ) {
		file_path = argv[1];
	}
	//
	if ( argc > 2) {
		target = strdup(argv[2]);
	}
	//
	string file_str = slurp(file_path);
	//
	if ( argc > 3 ) {
		hash_path = argv[3];
	}
	//
	string hashtable = slurp(hash_path);
	//
	if ( argc > 4 ) {
		tmplt_str = argv[4];
		replace_pos = tmplt_str.find('@');
	}
	//
	map<string,string> quote_list = double_splits(hashtable,", ","\n");
	list<string> qkeys = keys<string>(quote_list);
	//
	qkeys.sort([](string &a,string &b){ return(a.size() > b.size()); });
	//
	//for_each(qkeys.begin(),qkeys.end(),[](string key) { cout << key << endl; });
	//
	//char * tmp = (char *)file_str.c_str();
	//const char * end = &(*file_str.end());
	//unsigned char tlen = (unsigned char)strlen(target);
	
	string output = "";
	
	list<string> components = uni_splist(file_str,target,false);
	list<string>::iterator lit = components.begin();
	output += *lit;  // skip the stuff up front..
	lit++;			// move to the first macro to be examined.
	while ( lit != components.end() ) {
		///
		string b = *lit;
		string prefix = target;   // the split erases the target from the string components
		//
		if ( !allowed_prefix(b) ) {
			output += prefix;
			output += *lit;
			lit++;
			continue;
		}
		//
		unsigned int p = 0;
		unsigned int ignore = 0;
		locate_parameter_boundries(b,ignore,p);

		string c = b.substr(0,p);  //  critical("bad things going down" .. 5.4 .. "in situ:" .. PI .. "in vitro" .. 10 .. "times")
		//
		for ( const auto key : qkeys ) {  // turn strings into numbers
			string val = quote_list[key];
			string tag = tmplt_str;
			tag = tag.replace(replace_pos,1,val);
			//
			do_replace(c,tag,key);
		}
		b = b.replace(0, p, c);

		*lit = b;
		//
		// ...

		// critical("23" .. 5.4 .. "4" .. PI .. "10" .. 10 .. "2")
		// transform parameter list into something that can be processed in a very efficient way.
		// Note: this does not handle complex syntax or do any evaluation...
		if ( PROCESSING_PARAMETERS ) {
			string transformable = *lit;
			unsigned int first_p = 0;
			unsigned int second_p = 0;
			locate_parameter_boundries(transformable,first_p,second_p);
			string params = transformable.substr(first_p+1,(second_p - first_p - 1));
			//
			bool extend_i = false;
			bool extend_f = false;
			params = transform_params(params,extend_i,extend_f); // reoder parameters, inserting control parameters for values.
			if ( extend_i ) {
				prefix += "i_";	// if only int parameters then use that logging form
			} else if ( extend_f ) {
				prefix += "f_";	// with float parameters, use another form that is a little less efficient, but predicatable.
			} else if ( DEFAULT_PARAMS ) {
				prefix += "i_"; // default behavior, not preserving strings.
			}
			// put the transformed parameters back into the list.
			//
			string transformed = transformable.replace(first_p+1,(second_p - first_p - 1),params);
			//
			*lit = transformed;
		}

		output += prefix;
		output += *lit;
		lit++;
	}
	
	cout << output << endl;
	return(0);
}
