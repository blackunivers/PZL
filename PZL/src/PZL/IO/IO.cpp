#include "PCH.h"
#include "IO.h"

#include "System/Error.h"

namespace PZL::IO
{

	File* ReadFile(const char* Path)
	{
		std::ifstream IFile(Path, std::ios::in | std::ios::binary);

		if (!IFile.is_open())
			PZL_EXIT_WITH_ERROR("Could not open the file: %s\n", Path);

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