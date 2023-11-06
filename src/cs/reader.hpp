#ifndef DXNA_CS_READER_HPP
#define DXNA_CS_READER_HPP

#include "stream.hpp"
#include "nullable.hpp"
#include <memory>
#include <vector>
#include <string>

namespace cs {
	class BinaryReader {
	public:
		BinaryReader(std::shared_ptr<Stream> const& input) {
			if (input == nullptr || !input->CanRead()) {
				canRead = false;
			}

			stream = input;
			buffer = std::vector<bytecs>(BufferLength);
		}

		std::shared_ptr<Stream> BaseStream() const { return stream; }

		intcs PeekChar() {
			if (!canRead || !stream->CanSeek())
				return -1;

			longcs position = stream->Position();
			intcs num = Read();
			stream->Position(position);
			return num;
		}

		intcs Read() {
			intcs num1 = 0;
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

			return num1 == 0 ? -1 : (intcs)singleChar[0];
		}

		Nullable<bool> ReadBoolean() {
			auto result = FillBuffer(1);

			if (!result)
				return nbool();

			return buffer[0] > 0;
		}

		Nullable<bytecs> ReadByte() {
			if (stream == nullptr)
				return nbytecs();

			intcs num = stream->ReadByte();

			if (num == -1)
				return nbytecs();

			return (bytecs)num;
		}

		Nullable<sbytecs> ReadSByte() {
			auto result = FillBuffer(1);

			if (!result)
				return nsbytecs();

			return (sbytecs)buffer[0];
		}

		Nullable<charcs> ReadChar() {
			intcs num = Read();

			if (num == -1)
				return ncharcs();

			return (charcs)num;
		}

		Nullable<shortcs> ReadInt16() {
			auto result = FillBuffer(2);

			if (!result)
				return nshortcs();

			return (shortcs)(buffer[0] | buffer[1] << 8);
		}

		Nullable<ushortcs> ReadUInt16() {
			auto result = FillBuffer(2);

			if (!result)
				return nushortcs();

			return (ushortcs)(buffer[0] | (uintcs)buffer[1] << 8);
		}

		Nullable<intcs> ReadInt32() {
			//TODO: IsMemoryStream

			auto result = FillBuffer(4);

			if (!result)
				return nintcs();

			return buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24;
		}

		Nullable<uintcs> ReadUInt32() {
			auto result = FillBuffer(4);

			if (!result)
				return nuintcs();

			return (uintcs)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
		}

		Nullable<longcs> ReadInt64() {
			auto result = FillBuffer(8);

			if (!result)
				return nlongcs();

			return (longcs)(uintcs)(buffer[4] | buffer[5] << 8 | buffer[6] << 16 | buffer[7] << 24) << 32 | (ulongcs)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
		}

		Nullable<ulongcs> ReadUInt64() {
			auto result = FillBuffer(8);

			if (!result)
				return nulongcs();

			return (ulongcs)(uintcs)(buffer[4] | buffer[5] << 8 | buffer[6] << 16 | buffer[7] << 24) << 32 | (ulongcs)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);
		}

		Nullable<float> ReadSingle() {
			auto result = FillBuffer(4);
			auto value = (uintcs)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24);

			return *(float*)&value;
		}

		Nullable<double> ReadDouble() {
			auto result = FillBuffer(8);
			auto value = ((ulongcs)(buffer[4] | buffer[5] << 8 | buffer[6] << 16 | buffer[7] << 24) << 32 | (ulongcs)(buffer[0] | buffer[1] << 8 | buffer[2] << 16 | buffer[3] << 24));

			return *(double*)&value;
		}

		std::string ReadString() {
			//TODO
			return std::string();
		}

		intcs Read(charcs* buffer, intcs index, intcs count) {
			//TODO
			return 0;
		}

		std::vector<charcs> ReadChars(intcs count) {
			//TODO
			return std::vector<charcs>();
		}

		intcs Read(bytecs* buffer, int index, int count) {
			//TODO
			return 0;
		}

		std::vector<bytecs>ReadBytes(int count) {
			return std::vector<bytecs>();
		}

	private:
		nintcs Read7BitEncodedInt() {
			intcs num1 = 0;
			intcs num2 = 0;
			
			while (num2 != 35) {
				const auto num3 = ReadByte();

				if (!num3.HasValue())
					return nintcs();

				num1 |= ((intcs)num3 & (intcs)SByteMaxValue) << num2;
				num2 += 7;

				if (((intcs)num3 & 128) == 0)
					return num1;
			}

			return nintcs();
		}

		intcs InternalReadChars(char* buffer, intcs index, intcs count) {
			return 0;
		}

		bool FillBuffer(intcs numBytes) {
			if (!buffer.empty() && (numBytes < 0 || numBytes > BufferLength))
				return false;

			if (stream == nullptr)
				return false;

			intcs offset = 0;

			if (numBytes == 1) {
				intcs num = stream->ReadByte();

				if (num == -1)
					return false;

				buffer[0] = (bytecs)num;
			}
			else {
				do {
					intcs num = stream->Read(buffer.data(), offset, numBytes - offset);

					if (num == 0)
						return false;

					offset += num;

				} while (offset < numBytes);
			}

			return true;
		}

		static constexpr int MaxCharBytesSize = 128;
		static constexpr int BufferLength = 16;
		std::shared_ptr<Stream> stream;
		std::vector<bytecs> charBytes;
		std::vector<charcs> singleChar;
		std::vector<bytecs> buffer;

		bool canRead{ true };
		bool m2BytesPerChar{ true };
	};
}

#endif