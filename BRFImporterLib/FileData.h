#pragma once
#include <string>
#include <vector>
#include "BRFImporterStructs.h"

namespace BRFImporterLib
{
	class FileData
	{
	protected:
		MeshHeader meshContent;
		OOBBHeader oobbContent;
		std::vector<IndexHeader> indexContent;
		std::vector<VertexHeader> vertexContent;

		//all headers here
		//as pointers?
	
	public:
		void LoadFile(std::string fileName);

		//CON DECON
		FileData();
		~FileData();
	};
}