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
		using dxerror = dxna::Error;
		using dxerrcd = dxna::ErrorCode;

		BinaryReader(StreamPtr const& input) {
			stream = input;
			buffer = std::vector<bytecs>(BufferLength);
		}

		StreamPtr BaseStream() const { return stream; }

		dxerror PeekChar(intcs& result) {
			if (stream == nullptr)
				return dxerror(dxerrcd::CS_STREAM_IS_NULL);

			if (!stream->CanSeek()) {
				result = -1;
				return dxerror::NoError();
			}				

			longcs position = stream->Position();
			intcs num = 0;
			const auto readres = Read(num);

			if (readres != dxerrcd::NONE)
				return readres;

			stream->Position(position);
			
			result = num;
			return dxerror::NoError();
		}

		dxerror Read(intcs& result) {
			if (stream == nullptr)
				return dxerror(dxerrcd::CS_STREAM_IS_NULL);	

			return dxerror::NoError();

			/*intcs num1 = 0;
			longcs num2;
			longcs num3 = num2 = 0;

			if (stream->CanSeek())
				num3 = stream->Position();

			if (charBytes.empty())
				charBytes = std::vector<bytecs>(MaxCharBytesSize);

			if (singleChar.empty())
				singleChar = std::vector<charcs>(1);

			while (num1 == 0) {
				intcs byteCount = m2BytesPerChar ? 2 : 1;
				intcs num4 = stream->ReadByte();
				charBytes[0] = (bytecs)num4;

				if (num4 == -1)
					byteCount = 0;

				if (byteCount == 2) {
					intcs num5 = stream->ReadByte();
					charBytes[1] = (bytecs)num5;

					if (num5 == -1)
						byteCount = 1;
				}

				if (byteCount == 0)
					return -1;
				else if (byteCount == 1) {
					singleChar[0] = (charcs)charBytes[0];
					num1 = 1;
				}
				else {
					char temp = charBytes[0];
					temp |= ((charcs)charBytes[1] << 8);
					num1 = 2;
				}
			}

			return num1 == 0 ? -1 : (intcs)singleChar[0];*/
		}

		Nullable<bool> ReadBoolean() {			
				return nullbool();
		}

		Nullable<bytecs> ReadByte() {
				return nullbytecs();
		}

		Nullable<sbytecs> ReadSByte() {
				return nullsbytecs();
		}

		Nullable<charcs> ReadChar() {
				return nullcharcs();
		}

		Nullable<shortcs> ReadInt16() {
				return nullshortcs();
		}

		Nullable<ushortcs> ReadUInt16() {			
				return nullushortcs();
		}

		Nullable<intcs> ReadInt32() {
				return nullintcs();
		}

		Nullable<uintcs> ReadUInt32() {
				return nulluintcs();
		}

		Nullable<longcs> ReadInt64() {
				return nulllongcs();
		}

		Nullable<ulongcs> ReadUInt64() {
				return nullulongcs();
		}

		Nullable<float> ReadSingle() {
			return nullfloat();
		}

		Nullable<double> ReadDouble() {
			return nulldouble();
		}			

		std::vector<bytecs> ReadBytes(size_t count) {
			return std::vector<bytecs>();
		}

		std::string ReadString() {			
			return std::string();
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

		intcs InternalReadOneChar() {
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

				if (byteCount == 2)	{
					auto num5 = stream->ReadByte();
					charBytes[1] = static_cast<bytecs>(num5);

					if (num5 == -1)
						byteCount = 1;
				}

				if (byteCount == 0)
					return -1;

				/*try
				{
					num1 = this.m_decoder.GetChars(this.m_charBytes, 0, byteCount, this.m_singleChar, 0);
				}
				catch
				{
					if (this.m_stream.CanSeek)
						this.m_stream.Seek(num3 - this.m_stream.Position, SeekOrigin.Current);
					throw;
				}*/
			}
			
			return num1 == 0 ? -1 : static_cast<intcs>(singleChar[0]);
		}
		
		bool FillBuffer(intcs numBytes) {

			return true;
		}
	};
}

#endif