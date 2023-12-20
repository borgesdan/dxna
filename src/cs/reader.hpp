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

namespace cs {
	class BinaryReader {
	public:
		BinaryReader(StreamPtr const& input) {
			stream = input;
			buffer = std::vector<bytecs>(BufferLength);
		}

		StreamPtr BaseStream() const { return stream; }

		dxna::Error PeekChar(intcs& result) {
			if (stream == nullptr)
				return dxna::Error(dxna::ErrorCode::CS_STREAM_IS_NULL);

			if (!stream->CanSeek()) {
				result = -1;
				return dxna::Error::NoError();
			}

			longcs position = stream->Position();

			dxna::Error err;
			intcs num = Read(err);

			if (err != dxna::ErrorCode::NONE)
				return err;

			stream->Position(position);

			result = num;
			return dxna::Error::NoError();
		}

		intcs Read(dxna::Error err = dxna::NoError) {
			if (stream == nullptr)
			{
				err = dxna::Error(dxna::ErrorCode::CS_STREAM_IS_NULL);
				return -1;
			}

			intcs result;
			err = InternalReadOneChar(result);			

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
				| static_cast<intcs>(buffer[7]) << 24) << 32;

			const auto num2 = static_cast<uintcs>(
				static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) << 8
				| static_cast<intcs>(buffer[2]) << 16
				| static_cast<intcs>(buffer[3]) << 24);

			return static_cast<longcs>(num1) | static_cast<longcs>(num2);
		}

		ulongcs ReadUInt64(dxna::Error err = dxna::NoError) {
			err = FillBuffer(8);

			if (err.HasError())
				return 0;

			const auto num1 = static_cast<uintcs>(
				static_cast<intcs>(buffer[4])
				| static_cast<intcs>(buffer[5]) << 8
				| static_cast<intcs>(buffer[6]) << 16
				| static_cast<intcs>(buffer[7]) << 24) << 32;

			const auto num2 = static_cast<uintcs>(
				static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) << 8
				| static_cast<intcs>(buffer[2]) << 16
				| static_cast<intcs>(buffer[3]) << 24);

			return static_cast<ulongcs>(num1) | static_cast<ulongcs>(num2);
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
				| static_cast<intcs>(buffer[7]) << 24) << 32;

			const auto num2 = static_cast<uintcs>(
				  static_cast<intcs>(buffer[0])
				| static_cast<intcs>(buffer[1]) <<8
				| static_cast<intcs>(buffer[2]) << 6
				| static_cast<intcs>(buffer[3]) << 24);

			const auto num3 = static_cast<ulongcs>(num1) | static_cast<ulongcs>(num2);

			return *(double*)&num3;
		}

		std::string ReadString(dxna::Error err = dxna::NoError) {
			return std::string();
		}

		std::vector<bytecs> ReadBytes(size_t count, dxna::Error err = dxna::NoError) {
			return std::vector<bytecs>();
		}		

	private:
		static constexpr int MaxCharBytesSize = 128;
		static constexpr int BufferLength = 16;
		std::shared_ptr<Stream> stream;
		std::vector<bytecs> charBytes;
		std::vector<charcs> singleChar;
		std::vector<bytecs> buffer;
		std::vector<charcs> charBuffer;

		bool m2BytesPerChar{ true };

		dxna::Error InternalReadOneChar(intcs& result) {
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
					result = -1;
					return dxna::Error::NoError();
				}

				try
				{
					std::wstring_convert<std::codecvt_utf8<charcs>, charcs> ucs2conv;
					auto data = reinterpret_cast<char*>(charBytes.data());

					std::u16string ucs2 = ucs2conv.from_bytes(data, data + byteCount);

					if (!ucs2.empty())
					{
						num1 = ucs2.size();
						singleChar[0] = ucs2[0];
					}

				}
				catch (...)
				{
					if (stream->CanSeek())
						stream->Seek(num3 - stream->Position(), SeekOrigin::Current);

					return dxna::Error(dxna::ErrorCode::CS_STREAM_READ_RANGE_ERROR);
				}
			}

			result = num1 == 0 ? -1 : static_cast<intcs>(singleChar[0]);
			return dxna::Error::NoError();
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
	};
}

#endif