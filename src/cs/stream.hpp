#ifndef DXNA_CS_STREAM_HPP
#define DXNA_CS_STREAM_HPP

#include "cstypes.hpp"
#include "enumerations.hpp"

namespace cs {
	class Stream {
	public:
		virtual bool CanRead() const { return false; }
		virtual bool CanSeek() const { return false; }
		virtual bool CanTimeout() const { return false; }
		virtual bool CanWrite() const { return false; }
		virtual longcs Length() const { return 0; }
		virtual void Length(longcs value) { }
		virtual longcs Position() const { return 0; }
		virtual void Position(longcs value) { }
		virtual intcs ReadTimeout() const { return 0; }
		virtual void ReadTimeout(intcs value) {}
		virtual intcs WriteTimeout() const { return 0; }
		virtual void WriteTimeout(intcs value) { }
		virtual void Close(){}
		virtual void Flush(){}
		virtual longcs Seek(longcs offset, SeekOrigin const& origin) { return 0; }
		virtual intcs Read(bytecs* buffer, size_t bufferLength, size_t offset, size_t count) { return 0; }
		virtual intcs ReadByte() { return 0; }
		virtual void Write(bytecs * buffer, size_t bufferLength, size_t offset, size_t count){}
		virtual void WriteByte(bytecs value){}
	};	
}

#endif