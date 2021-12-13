#ifndef __COMMON_H__
#define __COMMON_H__

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cmath>
#include <queue>
#include <vector>
#include <set>
#include <map>

// for transaction
#define WRITE true
#define READ false

using namespace std;

// define enumerated types
struct DataIndex {
	int row_start;
	int row_end;
	int col_start;
	int col_end;
	
	int tot_req_cnt;

	uint64_t value_addr_start;
	uint64_t value_addr_end;
	uint64_t row_addr_start;
	uint64_t row_addr_end;
	uint64_t col_addr_start;
	uint64_t col_addr_end;

	vector<int> req_cnt_list;
	vector<int> rest_edge;

};


struct Transaction {
	uint64_t address;
	bool is_write;
};

#endif
