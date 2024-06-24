#include "byte_stream.hh"
#include <algorithm>

// You will need to add private members to the class declaration in `byte_stream.hh`

/* Replace all the dummy definitions inside the methods in this file. */

// Let us assume it is working as a normal queue
using namespace std;

ByteStream::ByteStream(const size_t capa){
	tot_read = 0;
	tot_written = 0;
	capacity = capa;
	dq.resize(capa);
	dq.clear();
	input_end_checker = false;
}

size_t ByteStream::write(const string &data) {
	if(error()) return 0;
	int data_written_size = min(remaining_capacity(),data.size());
	for(char i: data){
		if(dq.size()==(int)capacity) break;
		dq.push_back(i);
	}
	tot_written += data_written_size;
	return data_written_size;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
	if(error()) return "";
	string peek_str = "";
	auto it = dq.begin();
	for(int i=0; i<len && i<dq.size(); i++){
		peek_str += *it;
		it++;
	}
	return peek_str;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
	if(error()) return ;
	if(len>dq.size()) set_error();
	for(int i=0; i<len && i<capacity; i++){
		dq.pop_front();
		tot_read++;
	}
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
	string peek_str = peek_output(len);
	pop_output(len);
	return peek_str;
}

void ByteStream::end_input() {
	input_end_checker = true;
}
bool ByteStream::input_ended() const {
	return input_end_checker;
}

size_t ByteStream::buffer_size() const {
	return dq.size(); 
}

bool ByteStream::buffer_empty() const {
	if(dq.size()==0) return true;
	return false; 
}

bool ByteStream::eof() const { 
	return input_end_checker && dq.size()==0;
}

size_t ByteStream::bytes_written() const { 
	return tot_written; 
}

size_t ByteStream::bytes_read() const {
	return tot_read;
}

size_t ByteStream::remaining_capacity() const { 
	return capacity-dq.size(); 
}
