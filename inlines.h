#include <iostream>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <map>
#include <list>
#include <unordered_set>
#include <string>
#include <regex>
#include <ctype.h>

using namespace std;




#define STRING_START(c) (((c) == '\'') || ((c) == '\"'))
#define STR_STOP_CHAR(c)  (((c) == '\'')  ? '\'' : '\"')
#define STR_DONT_STOP_CHAR(c)  (((c) == '\'')  ? '\"' : '\'')


// some of these functions were found on stack exchange...

// read in a whole file
inline string slurp(const string& path) {
	ostringstream buf;
	ifstream input (path.c_str());
	buf << input.rdbuf();
	return buf.str();
}

// write out a whole file
inline void dump(const string& path,const string &data) {
	ofstream output (path.c_str());
	output << data << endl;
}


// many ways of implementing this
inline string trim(string str) {
	str.erase(0, str.find_first_not_of(" \n\r\t"));
	str.erase(str.find_last_not_of(" \n\r\t")+1);
	return(str);
}

// or do a trim on just the right side
inline void right_trim(char *buffer) {
	char *tmp = strrchr(buffer,' ');
	while ( tmp > buffer && (*tmp == ' ' ) ){
		*tmp-- = 0;
	}
}


inline void print_table(map<string,string> &tt) {
	for ( auto const& [key, val]  : tt ) {
		cout << key << " = " << val << endl;
	}
}

inline void print_list(list<string> &tt) {
	for ( auto const& val  : tt ) {
		cout << val << endl;
	}
}


inline void toHex(const char* src,char *dst) {
	for (const char* p = src; *p; ++p) {
		sprintf(dst,"%02x",*p);
		dst += 2;
	}
	*dst++ = '0';
	*dst = '0';
}


//
inline list<string> uni_splist(string hashtable,const char *sep,bool dotrim = true) {
	list<string> entries;
	char *entry = (char *)hashtable.c_str();
	char *next = entry;
	next = strstr(next,sep);
	//
	unsigned char seplen = strlen(sep);
	while ( next ) {
		*next = 0;
		next += seplen;
		string sentry = strdup(entry);
		if ( dotrim ) sentry = trim(sentry);
		if ( sentry.size() ) {
			//cout << sentry << endl;
			entries.push_back(sentry);
		}
		entry = next;
		next = strstr(next,sep);
	}
	string sentry = strdup(entry);
	if ( dotrim ) sentry = trim(sentry);
	if ( sentry.size() ) {
		entries.push_back(sentry);
	}
	return(entries);
}



// put an array of string together..
inline string join(const list<string>& slist, const char* delim,bool trim_last = false)
{
	stringstream res;
	copy(slist.begin(), slist.end(), ostream_iterator<string>(res, delim));
	if ( trim_last ) {
		string p = res.str();
		p = p.substr(0,p.size()-strlen(delim));
		return(p);
	} else {
		return res.str();
	}
}

// split a string known to have two parts and one delimeter
inline pair<string,string> uni_splist_pair(string hashtable,const char *sep) {
	list<string> cols = uni_splist(hashtable,sep,false);
	string a = cols.front();
	cols.pop_front();
	string b = join(cols,sep,true);
	pair<string,string> p = {a,b};
	return(p);
}


// split row, then columns
inline map<string,string> double_splits_rev(string hashtable,const char *sep_col,const char *sep_row) {
	list<string> ll = uni_splist(hashtable,sep_row);
	map<string,string> htab;
	for ( string row : ll )  {
		auto [val,key] = uni_splist_pair(row,sep_col);
		htab[key] = val;
	}
	return(htab);
}

// split row, then columns
inline map<string,string> double_splits(string hashtable,const char *sep_col,const char *sep_row) {
	list<string> ll = uni_splist(hashtable,sep_row);
	map<string,string> htab;
	for ( string row : ll )  {
		auto [key,val] = uni_splist_pair(row,sep_col);
		htab[key] = val;
	}
	return(htab);
}



// get the keys of a map
template<typename keyType>
list<keyType> keys(map<keyType, unsigned int> &items) {
	list<keyType> itemKeys;
	for (const auto& [key, ignore] : items) {
		itemKeys.emplace_back(key);
	}
	return(itemKeys);
}

// get the keys of a map
template<typename keyType,typename valType>
list<keyType> keys(map<keyType, valType> &items) {
	list<keyType> itemKeys;
	for (const auto& [key, ignore] : items) {
		itemKeys.emplace_back(key);
	}
	return(itemKeys);
}


// true if the is a space ' ' in the string anywhere...
inline bool string_has_spaces(string test) {
	if ( strchr(test.c_str(),' ') != NULL ) {
		return(true);
	}
	return(false);
}


template<typename keyType>
list<keyType> keys_n_hash(map<keyType,string> &items) {
	list<keyType> itemKeys;
	for (const auto& [key, hash] : items) {
		itemKeys.emplace_back("" + hash + ", " + key);
	}
	return(itemKeys);
}


void do_replace(string& str, const string& oldStr, const string& newStr) {
	string::size_type pos = 0u;
	while((pos = str.find(oldStr, pos)) != std::string::npos){
		str.replace(pos, oldStr.length(), newStr);
		pos += newStr.length();
	}
}

inline string unstring(const string &str) {
	const char c = str[0];
	string ustr = str.substr(1,str.find(c,1)-1);
	return ustr;
}

const int is_bool = 1;
const int is_char = 2;
const int is_int = 3;
const int is_float = 4;
const int is_end = 5;

#define TRUE_STR "true"
#define FALSE_STR "false"


inline bool isint(const string &par) {
	//
	const char *tmp = par.c_str();
	while ( *tmp ) {
		if ( !isdigit(*tmp) ) {
			return(false);
		}
		tmp++;
	}
	//
	return(true);
}


inline int parse_type_of(const string &par,int (*conversion_finder)(const string &)) {
	//
	if ( par == TRUE_STR || par == FALSE_STR ) {
		return(is_bool);
	}
	if ( isint(par) ) {
		if ( atoi(par.c_str()) <= 255 ) {
			return(is_char);
		}
		return(is_int);
	} else {
		int type_spec =  (*conversion_finder)(par);
		if ( type_spec != is_end ) {
			return(type_spec);
		}
	}
	return(is_float);
}


//
inline void load_cmd_line(map<string,string> &setMap,int argc, char **argv) {
	//
	unsigned char i = 1;
	while ( i < argc ) {
		string param_atom = argv[i++];
		if ( param_atom[0] == '-' ) {
			string key = param_atom.substr(1);
			setMap[key] = "-";
			if ( i < argc ) {
				string value = argv[i++];
				setMap[key] = value;
			}
		}
	}
}

//
inline unsigned int next_token(char del,unsigned int key_pos,string &data) {
	size_t t_pos = data.find(del,key_pos);
	if ( t_pos != string::npos ) {
		return(t_pos);
	}
	return(0);
}


//
inline string json_lite_extract_keyed_body(const string &key,string &data) {
	size_t key_pos = data.find(key);
	if ( key_pos != string::npos ) {
		key_pos += key.size();
		key_pos = next_token(':',key_pos,data) + 1;
		key_pos = next_token('{',key_pos,data) + 1;
		size_t stop_pos = next_token('}',key_pos,data) - 1;
		string strlist = data.substr(key_pos,(stop_pos - key_pos));
		return(trim(strlist));
	} else {
		return("empty");
	}
}



