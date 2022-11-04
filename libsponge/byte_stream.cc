#include "byte_stream.hh"

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity) 
    :buffer(), buffer_capacity(capacity), end_input_flag(false), written_bytes_counter(0), read_bytes_counter(0){}

size_t ByteStream::write(const string &data) {
    size_t available_space = buffer_capacity - buffer.size();
    size_t written_space = min(available_space, data.length());
    for(size_t i = 0; i <= written_space - 1; i++) {
        buffer.push_back(data[i]);
    }
    written_bytes_counter += written_space;
    return written_space;
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    size_t peakable_size = min(buffer.size(), len);
    string peek_string = "";
    for(size_t i = 0; i <= peakable_size - 1; i++) {
        peek_string += buffer[i];    
    }
    return peek_string;
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) { 
    if (len > buffer.size()) {
        set_error();
    }
    else {
        for (size_t i = 0; i <= len - 1; i++) {
            buffer.pop_front();
            read_bytes_counter++;
        }
    }        
}

//! Read (i.e., copy and then pop) the next "len" bytes of the stream
//! \param[in] len bytes will be popped and returned
//! \returns a string
std::string ByteStream::read(const size_t len) {
    string read_string = "";
    if (len > buffer.size()) {
        set_error();
    }
    else {
        for(size_t i = 0; i <= len - 1; i++) {
            read_string += buffer.front();
            buffer.pop_front();
        }
        read_bytes_counter += len;
    }
    return read_string;
}

void ByteStream::end_input() { end_input_flag = true; }

bool ByteStream::input_ended() const { return end_input_flag; }

size_t ByteStream::buffer_size() const { return buffer.size(); }

bool ByteStream::buffer_empty() const { return buffer.empty(); }

bool ByteStream::eof() const { return buffer.empty() && end_input_flag; }

size_t ByteStream::bytes_written() const { return written_bytes_counter; }

size_t ByteStream::bytes_read() const { return read_bytes_counter; }

size_t ByteStream::remaining_capacity() const { return buffer_capacity - buffer.size(); }
