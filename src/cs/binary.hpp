#ifndef DXNA_CS_READER_HPP
#define DXNA_CS_READER_HPP

#include "stream.hpp"
#include "nullable.hpp"
#include <memory>
#include <vector>
#include <string>
#include <codecvt>
#include <locale> 

#include "../error.hpp"
#include "forward.hpp"
#include "enumerations.hpp"

namespace cs {
	class BinaryReader {
	public:
		BinaryReader(Stream* const& input) {
			stream = input;
			buffer = std::vector<bytecs>(BufferLength);
		}		

		intcs PeekChar(dxna::Error err = dxna::NoError) {
			if (stream == nullptr) {
				err = dxna::Error(dxna::ErrorCode::CS_STREAM_IS_NULL);
				return -1;
			}

			if (!stream->CanSeek()) {
				err = dxna::Error::NoError();
				return -1;
			}

			longcs position = stream->Position();

			intcs num = Read(err);

			if (err != dxna::ErrorCode::NONE)
				return -1;

			stream->Position(position);

			return num;
		}

		intcs Read(dxna::Error err = dxna::NoError) {
			if (stream == nullptr)
			{
				err = dxna::Error(dxna::ErrorCode::CS_STREAM_IS_NULL);
				return -1;
			}
			
			intcs result= InternalReadOneChar(err);

			return err.HasError() ? -1 : result;
		}

		// Reads a Boolean value from the current stream and advances the current position of the stream by one byte.
		bool ReadBoolean(dxna::Error err = dxna::NoError) {
			err = FillBuffer(1);		
			return err.HasError() ? false : buffer[0] > 0;
		}

		// Reads the next byte from the current stream and advances the current position of the stream by one byte.
		bytecs ReadByte(dxna::Error err = dxna::NoError) {
			if (stream == nullptr)
			{
				err = { dxna::ErrorCode::CS_STREAM_IS_NULL };
				return 0;
			}

			const auto num = stream->ReadByte();

			if (num == -1)
			{
				err = { dxna::ErrorCode::CS_STREAM_ENDOFFILE };
				return 0;
			}

			return static_cast<bytecs>(num);
		}

		sbytecs ReadSByte(dxna::Error err = dxna::NoError) {
			err = FillBuffer(1);
			return err.HasError() ? -1 : static_cast<sbytecs>(buffer[0]);
		}

		charcs ReadChar(dxna::Error err = dxna::NoError) {
			auto num = Read(err);

			if (err.HasError() || num == -1)
				return '\0';

			return static_cast<charcs>(num);
		}

		shortcs ReadInt16(dxna::Error err = dxna::NoError) {
			err = FillBuffer(2);

			if (err.HasError())
				return -1;

			return static_cast<shortcs>(
				static_cast<intcs>(buffer[0]) 
				| static_cast<intcs>(buffer[1]) << 8);
		}

		ushortcs ReadUInt16(dxna::Error err = dxna::NoError) {
			err = FillBuffer(2);

			if (err.HasError())
				return 0;

			return static_cast<ushortcs>(
				static_cast<uintcs>(buffer[0])
				| static_cast<uintcs>(buffer[1]) << 8);
		}

		intcs ReadInt32(dxna::Error err = dxna::NoError) {
			err = FillBuffer(4);

			if (err.HasError())
				return -1;

			return static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) << 8 
				| static_cast<intcs>(buffer[2]) << 16 
				| static_cast<intcs>(buffer[3]) << 24;
		}

		uintcs ReadUInt32(dxna::Error err = dxna::NoError) {
			err = FillBuffer(4);

			if (err.HasError())
				return -1;

			return static_cast<uintcs>(
				static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) << 8
				| static_cast<intcs>(buffer[2]) << 16
				| static_cast<intcs>(buffer[3]) << 24);
		}

		longcs ReadInt64(dxna::Error err = dxna::NoError) {
			err = FillBuffer(8);

			if (err.HasError())
				return -1;

			const auto num1 = static_cast<uintcs>(
				static_cast<intcs>(buffer[4])
				| static_cast<intcs>(buffer[5]) << 8
				| static_cast<intcs>(buffer[6]) << 16
				| static_cast<intcs>(buffer[7]) << 24);

			const auto num2 = static_cast<uintcs>(
				static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) << 8
				| static_cast<intcs>(buffer[2]) << 16
				| static_cast<intcs>(buffer[3]) << 24);

			return static_cast<longcs>(num1) << 32 | static_cast<longcs>(num2);
		}

		ulongcs ReadUInt64(dxna::Error err = dxna::NoError) {
			err = FillBuffer(8);

			if (err.HasError())
				return 0;

			const auto num1 = static_cast<uintcs>(
				static_cast<intcs>(buffer[4])
				| static_cast<intcs>(buffer[5]) << 8
				| static_cast<intcs>(buffer[6]) << 16
				| static_cast<intcs>(buffer[7]) << 24);

			const auto num2 = static_cast<uintcs>(
				static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) << 8
				| static_cast<intcs>(buffer[2]) << 16
				| static_cast<intcs>(buffer[3]) << 24);

			return static_cast<ulongcs>(num1) << 32 | static_cast<ulongcs>(num2);
		}

		float ReadSingle(dxna::Error err = dxna::NoError) {
			err = FillBuffer(4);

			if (err.HasError())
				return std::numeric_limits<float>::quiet_NaN();

			const auto num = static_cast<uintcs>(
				  static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) << 8
				| static_cast<intcs>(buffer[2]) << 16
				| static_cast<intcs>(buffer[3]) << 24);

			return *(float*)&num;
		}

		double ReadDouble(dxna::Error err = dxna::NoError) {
			err = FillBuffer(8);

			if (err.HasError())
				return std::numeric_limits<double>::quiet_NaN();

			const auto num1 = static_cast<uintcs>(
				static_cast<intcs>(buffer[4])
				| static_cast<intcs>(buffer[5]) << 8
				| static_cast<intcs>(buffer[6]) << 16
				| static_cast<intcs>(buffer[7]) << 24);

			const auto num2 = static_cast<uintcs>(
				  static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) <<8
				| static_cast<intcs>(buffer[2]) << 6
				| static_cast<intcs>(buffer[3]) << 24);

			const auto num3 = static_cast<ulongcs>(num1) << 32 | static_cast<ulongcs>(num2);

			return *(double*)&num3;
		}

		std::string ReadString(dxna::Error err = dxna::NoError) {
			static const auto empty = std::string();

			if (stream == nullptr)
			{
				err = { dxna::ErrorCode::CS_STREAM_IS_NULL };
				return empty;
			}
			
			intcs num = 0;
			intcs val1 = Read7BitEncodedInt(err);

			if (err.HasError())
				return empty;

			if (val1 < 0) {
				err = { dxna::ErrorCode::IO_INVALID_STRING_LEN };
				return empty;
			}

			if (val1 == 0)
				return empty;

			if (charBytes.empty())
				charBytes.resize(MaxCharBytesSize);

			if (charBuffer.empty())
				charBuffer.resize(MaxCharBytesSize);

			std::string sb;

			do {
				const auto byteCount = stream->Read(charBytes, 0, val1 - num > 128 ? 128 : val1 - num);

				if (byteCount == 0) {
					err = { dxna::ErrorCode::CS_STREAM_ENDOFFILE };
					return empty;
				}

				std::wstring_convert<std::codecvt_utf8<charcs>, charcs> ucs2conv;
				auto data = reinterpret_cast<char*>(charBytes.data());

				std::u16string ucs2 = ucs2conv.from_bytes(data, data + byteCount);
				const auto result = ucs2conv.to_bytes(ucs2);

				if (num == 0 && byteCount == val1) {					
					return result;
				}

				sb.append(result);
				num += byteCount;				

			} while (num < val1);

			return empty;
		}

		std::u16string ReadString16(dxna::Error err = dxna::NoError) {
			static const auto empty = std::u16string();

			if (stream == nullptr)
			{
				err = { dxna::ErrorCode::CS_STREAM_IS_NULL };
				return empty;
			}

			intcs num = 0;
			intcs val1 = Read7BitEncodedInt(err);

			if (err.HasError())
				return empty;

			if (val1 < 0) {
				err = { dxna::ErrorCode::IO_INVALID_STRING_LEN };
				return empty;
			}

			if (val1 == 0)
				return empty;

			if (charBytes.empty())
				charBytes.resize(MaxCharBytesSize);

			if (charBuffer.empty())
				charBuffer.resize(MaxCharBytesSize);

			std::u16string sb;

			do {
				const auto byteCount = stream->Read(charBytes, 0, val1 - num > 128 ? 128 : val1 - num);

				if (byteCount == 0) {
					err = { dxna::ErrorCode::CS_STREAM_ENDOFFILE };
					return empty;
				}

				std::wstring_convert<std::codecvt_utf8<charcs>, charcs> ucs2conv;
				auto data = reinterpret_cast<char*>(charBytes.data());

				std::u16string ucs2 = ucs2conv.from_bytes(data, data + byteCount);				

				if (num == 0 && byteCount == val1) {
					return ucs2;
				}

				sb.append(ucs2);
				num += byteCount;

			} while (num < val1);

			return empty;
		}

		intcs Read(char* buffer, intcs index, intcs count, dxna::Error err = dxna::NoError) {
			return 0;
		}

		std::vector<bytecs> ReadBytes(size_t count, dxna::Error err = dxna::NoError) {
			return std::vector<bytecs>();
		}		

	private:
		static constexpr int MaxCharBytesSize = 128;
		static constexpr int BufferLength = 16;
		Stream* stream;
		std::vector<bytecs> charBytes;
		std::vector<charcs> singleChar;
		std::vector<bytecs> buffer;
		std::vector<charcs> charBuffer;

		bool m2BytesPerChar{ false };

		intcs InternalReadOneChar(dxna::Error err = dxna::NoError) {
			intcs num1 = 0;
			longcs num2;
			longcs num3 = num2 = 0;

			if (stream->CanSeek())
				num3 = stream->Position();

			if (charBytes.empty())
				charBytes.resize(128);

			if (singleChar.empty())
				singleChar.resize(1);

			while (num1 == 0)
			{
				auto byteCount = m2BytesPerChar ? 2 : 1;
				const auto num4 = stream->ReadByte();

				charBytes[0] = static_cast<bytecs>(num4);

				if (num4 == -1)
					byteCount = 0;

				if (byteCount == 2) {
					auto num5 = stream->ReadByte();
					charBytes[1] = static_cast<bytecs>(num5);

					if (num5 == -1)
						byteCount = 1;
				}

				if (byteCount == 0) {
					return -1;
				}

				try
				{
					//TODO: _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
					std::wstring_convert<std::codecvt_utf8<charcs>, charcs> ucs2conv;
					auto data = reinterpret_cast<char*>(charBytes.data());
					

					std::u16string ucs2 = ucs2conv.from_bytes(data, data + byteCount);

					if (!ucs2.empty())
					{
						num1 = static_cast<intcs>(ucs2.size());
						singleChar[0] = ucs2[0];
					}

				}
				catch (...)
				{
					if (stream->CanSeek())
						stream->Seek(num3 - stream->Position(), SeekOrigin::Current);

					err = dxna::Error(dxna::ErrorCode::CS_STREAM_READ_RANGE_ERROR);
					return -1;
				}
			}

			return num1 == 0 ? -1 : static_cast<intcs>(singleChar[0]);
		}

		dxna::Error FillBuffer(intcs numBytes) {
			if (stream == nullptr)
				return dxna::Error(dxna::ErrorCode::CS_STREAM_IS_NULL);

			if (!buffer.empty() && (numBytes < 0 || numBytes > buffer.size()))
				return dxna::Error(dxna::ErrorCode::ARGUMENT_OUT_OF_RANGE, 0);

			int offset = 0;

			if (numBytes == 1)
			{
				
				const auto num = stream->ReadByte();
				if (num == -1)
					return dxna::Error(dxna::ErrorCode::CS_STREAM_ENDOFFILE);

				buffer[0] = static_cast<bytecs>(num);
			}
			else
			{
				do
				{
					const auto num = stream->Read(buffer, offset, numBytes - offset);
					
					if (num == 0)
						return dxna::Error(dxna::ErrorCode::CS_STREAM_ENDOFFILE);

					offset += num;
				} while (offset < numBytes);
			}

			return dxna::Error::NoError();
		}

		intcs Read7BitEncodedInt(dxna::Error err = dxna::NoError)
		{
			intcs num1 = 0;
			intcs num2 = 0;

			while (num2 != 35) {
				auto num3 = ReadByte(err);

				if (err.HasError())
					return -1;

				num1 |= (static_cast<intcs>(num3) & static_cast<intcs>(SByteMaxValue)) << num2;
				num2 += 7;
				
				if ((static_cast<intcs>(num3) & 128) == 0)
					return num1;
			}

			err = { dxna::ErrorCode::CS_STREAM_BAD_FORMAT_7BIT };
			return -1;
		}

		intcs InternalReadChars(char* buffer, size_t bufferSize, intcs index, intcs count, dxna::Error err = dxna::NoError) {
			intcs charCount = count;
			
			if (charBytes.empty())
				charBytes.resize(128);

			while (charCount > 0) {
				auto count1 = charCount;
				
				if (count1 > 1)
					--count1;

				if (m2BytesPerChar)
					count1 <<= 1;

				if (count1 > 128)
					count1 = 128;

				intcs num = 0;
				intcs byteCount;

				std::vector<bytecs> numArray;

				byteCount = stream->Read(charBytes, 0, count1);
				numArray = charBytes;	

				if (byteCount == 0)
					return count - charCount;

				if (num < 0 || byteCount < 0 || (num + byteCount) > numArray.size()) {
					err = { dxna::ErrorCode::ARGUMENT_OUT_OF_RANGE };
					return -1;
				}

				if (index < 0 || charCount < 0 || (index + charCount) > bufferSize) {
					err = { dxna::ErrorCode::ARGUMENT_OUT_OF_RANGE };
					return -1;
				}

				
				std::wstring_convert<std::codecvt_utf8<charcs>, charcs> ucs2conv;
				auto data = reinterpret_cast<char*>(numArray.data());

				std::u16string ucs2 = ucs2conv.from_bytes((data + num), (data + num) + byteCount);
				
				const auto chars = ucs2.size();

				charCount -= chars;
				index += chars;
			}

			return count - charCount;
		}
	};

	class BinaryWriter {
	public:
		BinaryWriter(Stream* stream) : _stream(stream), _buffer(16) {
		}

		longcs Seek(intcs offset, SeekOrigin origin) {
			_stream->Seek(offset, origin);
		}

		void Write(bool value) {
			_buffer[0] = value ? 1 : 0;
			_stream->Write(_buffer, 0, 1);
		}

		void Write(bytecs value) {			
			_stream->WriteByte(value);
		}

		void Write(bytecs const* buffer, size_t bufferLength) {
			_stream->Write(buffer, bufferLength, 0, bufferLength);
		}

		void Write(std::vector<bytecs> const& buffer) {
			_stream->Write(buffer, 0, buffer.size());
		}

		void Write(bytecs const* buffer, size_t bufferLength, intcs index, intcs count) {
			_stream->Write(buffer, bufferLength, index, count);
		}

		void Write(std::vector<bytecs> const& buffer, intcs index, intcs count) {
			_stream->Write(buffer, index, count);
		}
		
		void Write(charcs ch) {
			_stream->Write(_buffer, 0, ch);
		}

		void Write(double value) {
			ulongcs num = (ulongcs)*(longcs*)&value;
			_buffer[0] = (bytecs)num;
			_buffer[1] = (bytecs)(num >> 8);
			_buffer[2] = (bytecs)(num >> 16);
			_buffer[3] = (bytecs)(num >> 24);
			_buffer[4] = (bytecs)(num >> 32);
			_buffer[5] = (bytecs)(num >> 40);
			_buffer[6] = (bytecs)(num >> 48);
			_buffer[7] = (bytecs)(num >> 56);

			_stream->Write(_buffer, 0, 8);
		}

		void Write(shortcs value) {
			_buffer[0] = (bytecs)value;
			_buffer[1] = (bytecs)((uintcs)value >> 8);
			_stream->Write(_buffer, 0, 2);
		}

		void Write(ushortcs value) {
			_buffer[0] = (bytecs)value;
			_buffer[1] = (bytecs)((uintcs)value >> 8);
			_stream->Write(_buffer, 0, 2);
		}

		void Write(intcs value) {
			_buffer[0] = (bytecs)value;
			_buffer[1] = (bytecs)(value >> 8);
			_buffer[2] = (bytecs)(value >> 16);
			_buffer[3] = (bytecs)(value >> 24);
			_stream->Write(_buffer, 0, 4);
		}

		void Write(uintcs value) {
			_buffer[0] = (bytecs)value;
			_buffer[1] = (bytecs)(value >> 8);
			_buffer[2] = (bytecs)(value >> 16);
			_buffer[3] = (bytecs)(value >> 24);
			_stream->Write(_buffer, 0, 4);
		}

		void Write(longcs value)
		{
			_buffer[0] = (bytecs)value;
			_buffer[1] = (bytecs)(value >> 8);
			_buffer[2] = (bytecs)(value >> 16);
			_buffer[3] = (bytecs)(value >> 24);
			_buffer[4] = (bytecs)(value >> 32);
			_buffer[5] = (bytecs)(value >> 40);
			_buffer[6] = (bytecs)(value >> 48);
			_buffer[7] = (bytecs)(value >> 56);
			_stream->Write(_buffer, 0, 8);
		}

		void Write(ulongcs value)
		{
			_buffer[0] = (bytecs)value;
			_buffer[1] = (bytecs)(value >> 8);
			_buffer[2] = (bytecs)(value >> 16);
			_buffer[3] = (bytecs)(value >> 24);
			_buffer[4] = (bytecs)(value >> 32);
			_buffer[5] = (bytecs)(value >> 40);
			_buffer[6] = (bytecs)(value >> 48);
			_buffer[7] = (bytecs)(value >> 56);
			_stream->Write(_buffer, 0, 8);
		}

		void Write(float value)
		{
			uintcs num = *(uintcs*)&value;
			_buffer[0] = (bytecs)num;
			_buffer[1] = (bytecs)(num >> 8);
			_buffer[2] = (bytecs)(num >> 16);
			_buffer[3] = (bytecs)(num >> 24);
			_stream->Write(_buffer, 0, 4);
		}

		void Write(std::string value) {

		}

	private:
		Stream* _stream;
		std::vector<bytecs> _buffer;

		void Write7BitEncodedInt(intcs value)
		{
			uintcs num;
			for (num = (uintcs)value; num >= 128U; num >>= 7)
				Write((bytecs)(num | 128U));

			Write((bytecs)num);
		}
	};
}

#endif