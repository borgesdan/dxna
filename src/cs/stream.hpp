#ifndef DXNA_CS_STREAM_HPP
#define DXNA_CS_STREAM_HPP

#include "cstypes.hpp"
#include "enumerations.hpp"
#include <vector>
#include <memory>
#include <fstream>
#include <string>

namespace cs {
	class Stream {
	public:
		virtual bool CanRead() const { return false; }
		virtual bool CanSeek() const { return false; }
		virtual bool CanTimeout() const { return false; }
		virtual bool CanWrite() const { return false; }
		virtual intcs Length() const { return 0; }
		virtual void Length(intcs value) { }
		virtual longcs Position() const { return 0; }
		virtual void Position(longcs value) { }
		virtual intcs ReadTimeout() const { return 0; }
		virtual void ReadTimeout(intcs value) {}
		virtual intcs WriteTimeout() const { return 0; }
		virtual void WriteTimeout(intcs value) { }
		virtual void Close() {}
		virtual void Flush() {}
		virtual longcs Seek(longcs offset, SeekOrigin const& origin) { return 0; }
		virtual void SetLength(longcs value) {};
		virtual intcs Read(bytecs* buffer, intcs bufferLength, intcs offset, intcs count) { return 0; }
		virtual intcs Read(std::vector<bytecs>& buffer, intcs offset, intcs count) { return 0; }
		virtual intcs ReadByte() { return 0; }
		virtual void Write(bytecs const* buffer, intcs bufferLength, intcs offset, intcs count) {}
		virtual void WriteByte(bytecs value) {}
	};

	enum class FileMode {		
		CreateNew = 1,
		Create = 2,
		Open = 3,
		OpenOrCreate = 4,
		Truncate = 5,
		Append = 6,
	};

	class FileStream : public Stream {
		FileStream(std::string const& path) {
			_fstream.open(path.c_str(),
				std::fstream::in 
				| std::fstream::out 
				| std::fstream::binary
				| std::fstream::ate);

			fileSize = _fstream.tellg();
			currentpos = fileSize;
			fileName = path;
		}

		~FileStream() {
			if (_fstream.is_open())
				_fstream.close();
		}

		virtual bool CanRead() const noexcept override { 
			return _fstream.is_open();
		}

		virtual bool CanWrite() const noexcept override { 
			return _fstream.is_open();
		}

		virtual bool CanSeek() const noexcept override { 
			return _fstream.is_open();
		}
		
		virtual intcs Length() const { 
			if (!_fstream.is_open())
				return -1;

			return fileSize;			 
		}

		std::string Name() const {
			return fileName;
		}

		virtual longcs Position() const override { 
			return currentpos;
		}		

		virtual intcs Read(bytecs* buffer, intcs bufferLength, intcs offset, intcs count) override {
			if (buffer == nullptr)
				return -1;

			if (offset < 0)
				offset = 0;

			if (count < 0)
				count = 0;

			if (bufferLength - offset < count)
				return -1;
			
			auto str = reinterpret_cast<char*>(buffer);

			auto& i = _fstream.read(str + offset, count);

			setCurrentPos();

			return i.gcount();
		}

		virtual longcs Seek(longcs offset, SeekOrigin const& origin) override {
			int seek;

			switch (origin)
			{
			case SeekOrigin::Begin:
				seek = std::ios_base::beg;
				break;
			case SeekOrigin::Current:
				seek = std::ios_base::cur;
				break;
			case SeekOrigin::End:
				seek = std::ios_base::end;
				break;
			default:
				seek = std::ios_base::cur;
				break;
			}

			_fstream.seekg(offset, seek);

			setCurrentPos();
		}

		virtual void Write(bytecs const* buffer, intcs bufferLength, intcs offset, intcs count) override {
			auto str = reinterpret_cast<const char*>(buffer);
			_fstream.write(str + offset, count);

			setCurrentPos();
		}

		virtual intcs ReadByte() override {
			char* str = new char[1];

			_fstream.read(str, 1);
			
			const auto result = static_cast<bytecs>(str[0]);
			delete[] str;

			setCurrentPos();
			return result;
		}

		virtual void WriteByte(bytecs value) override {
			char* str = new char[1];
			str[0] = static_cast<char>(value);

			_fstream.write(str, value);

			delete[] str;

			setCurrentPos();
		}

		virtual void Close() override {
			if(_fstream.is_open())
				_fstream.close();
		}

	public:
		std::fstream _fstream;

	private:
		std::streampos currentpos;
		size_t fileSize;
		std::string fileName;

		void setCurrentPos() {
			currentpos = _fstream.tellg();
		}
	};

	class MemoryStream : public Stream {
	public:
		constexpr MemoryStream(size_t capacity) : 
		_capacity(capacity),
		_buffer(std::vector<bytecs>(capacity)),
		_expandable(true),
		_writable(true),
		_exposable(true),
		_origin(0),
		_isOpen(true){}

		constexpr MemoryStream(
			std::vector<bytecs> const& buffer,
			size_t index,
			size_t count,
			bool writable = true,
			bool publiclyVisible = false) :
			_buffer(buffer),
			_origin(index),
			_position(_origin),
			_length(_position + count),
			_capacity(_length),
			_writable(writable),
			_exposable(publiclyVisible),
			_expandable(false),
			_isOpen(true){
			if (_buffer.size() - index < count)
				_buffer.resize(count);			
		}

		constexpr virtual bool CanRead() const noexcept override { return _isOpen; }
		constexpr virtual bool CanSeek() const noexcept { return _isOpen; }
		constexpr virtual bool CanWrite() const noexcept { return _writable; }

		constexpr virtual intcs Capacity() const noexcept {
			if (!_isOpen)
				return 0;

			return static_cast<intcs>(_capacity - _origin);
		}

		constexpr virtual void Capacity(size_t value) {
			if (!_isOpen || !_expandable || value == _capacity)
				return;

			_buffer.resize(value);
			_capacity = value;
		}

		constexpr virtual longcs Position() const noexcept override {
			if (!_isOpen)
				return 0;

			return _position - _origin;
		}

		constexpr virtual void Position(longcs value) noexcept override {
			if (value < 0)
				return;

			_position = _origin + value;
		}

		constexpr virtual intcs Read(bytecs* buffer, intcs bufferLength, intcs offset, intcs count) override {
			if (buffer == nullptr || bufferLength - offset < count || offset < 0 || count < 0 || !_isOpen)
				return -1;												

			auto byteCount = _length - _position;

			if (byteCount > count)
				byteCount = count;

			if (byteCount <= 8)
			{
				auto num = byteCount;
				while (--num >= 0)
					buffer[offset + num] = _buffer[_position + num];
			}
			else {
				size_t bufferIndex = 0;
				for (size_t i = _position; i < _position + byteCount; ++i) {
					buffer[bufferIndex + offset] = _buffer[i];
					++bufferIndex;
				}
			}

			_position += byteCount;
			return static_cast<intcs>(byteCount);
		}

		constexpr virtual intcs Read(std::vector<bytecs>& buffer, intcs offset, intcs count) override {
			return Read(buffer.data(), static_cast<intcs>(buffer.size()), offset, count);
		}

		constexpr virtual intcs ReadByte() override {
			if (!_isOpen)
				return -1;

			return _position >= _length ? -1 : static_cast<intcs>(_buffer[_position++]);
		}

		constexpr virtual longcs Seek(longcs offset, SeekOrigin const& origin) override {
			if (!_isOpen)
				return -1;

			switch (origin)
			{
			case SeekOrigin::Begin: {
				auto num1 = _origin + offset;

				if (offset < 0 || num1 < _origin)
					return -1;

				_position = num1;
				break;
			}
			case SeekOrigin::Current: {
				auto num2 = _position + offset;
				if (_position + offset < _origin || num2 < _origin)
					return -1;

				_position = num2;

				break;
			}
			case SeekOrigin::End: {
				auto num3 = _length + offset;
				if (_length + offset < _origin || num3 < _origin)
					return -1;

				_position = num3;
				break;
			}
			default:
				return -1;
			}

			return (longcs)_position;
		}

		constexpr virtual void SetLength(longcs value) override {
			if (value < 0 || value > IntMaxValue)
				return;

			if (value > (static_cast<longcs>(IntMaxValue) - static_cast<intcs>(_origin)))
				return;

			auto num = _origin + value;
			_length = num;

			if (_position <= num)
				return;

			_position = num;
		};

		constexpr virtual void Write(bytecs const* buffer, intcs bufferLength, intcs offset, intcs count) override {
			if (buffer == nullptr || offset < 0 || count < 0 || bufferLength - offset < count || !_isOpen || !_writable)
				return;

			auto num1 = _position + count;

			if (num1 < 0)
				return;

			if (num1 > _length) {
				bool flag = _position > _length;

				if (num1 > _capacity && EnsureCapacity(static_cast<intcs>(num1)))
					flag = false;

				if (flag) {
					for (size_t i = _length; i < num1 - _length; ++i) {
						_buffer[i] = 0;
					}
				}

				_length = num1;
			}

			if (count <= 8) {
				auto num2 = count;

				while (--num2 >= 0)
					_buffer[_position + num2] = buffer[offset + num2];
			}
			else {
				auto index = 0;
				for (size_t i = offset; i < count; ++i) {
					_buffer[_position + index] = buffer[i];
					index++;
				}
			}

			_position = num1;
		}

		constexpr virtual void WriteByte(bytecs value) override {
			if (!_isOpen || !_writable)
				return;

			if (_position >= _length)
			{
				auto num = _position + 1;
				bool flag = _position > _length;

				if (num >= _capacity && EnsureCapacity(static_cast<intcs>(num)))
					flag = false;

				if (flag) {
					for (size_t i = _length; i < _position - _length; ++i) {
						_buffer[i] = 0;
					}
				}

				_length = num;
			}

			_buffer[_position++] = value;
		}

		virtual void WriteTo(Stream* stream) const;

	private:
		constexpr bool EnsureCapacity(intcs value) {
			if (value < 0)
				return false;

			if (value <= _capacity)
				return false;

			auto num = value;

			if (num < 256)
				num = 256;

			if (num < _capacity * 2)
				num = static_cast<intcs>(_capacity * 2);

			Capacity(num);

			return true;
		}

	public:
		std::vector<bytecs> _buffer;

	private:
		size_t _origin{ 0 };
		size_t _position{ 0 };
		size_t _length{ 0 };
		size_t _capacity{ 0 };
		bool _expandable{ true };
		bool _writable{ true };
		bool _exposable{ true };
		bool _isOpen{ false };
	};	
}

#endif