#include "PCH.h"
#include "PZL/IO/IO.h"

namespace PZL::IO
{

	File* ReadFile(const char* Path)
	{
		std::ifstream IFile(Path, std::ios::in | std::ios::binary);

		if (!IFile.is_open())
			return new File{ 0, 0, false };

		std::string Content;
		std::string Line;
		while (std::getline(IFile, Line))
		{
			Content.append(Line + '\n');
		}

		char* Buffer = (char*)calloc(Content.length(), sizeof(char));
		strcpy(Buffer, Content.c_str());

		if (Buffer == nullptr)
			return new File{ 0, 0, false };

		return new File{ Buffer, strlen(Buffer), true };
	}

}