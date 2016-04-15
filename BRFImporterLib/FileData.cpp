#include "FileData.h"
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
using namespace BRFImporterLib;
//FUNCTION DEFINITIONS FOR FILEDATA

void FileData::LoadFile(std::string fileName, bool mesh)
{

	std::vector<std::shared_ptr<MeshData>> meshVector;
	std::shared_ptr<MainHeader> tempMain;

	std::ifstream inFile(fileName, std::ifstream::binary);
	if (!inFile.is_open())
	{
		return;
	}
	else
	{
		int goldenNumber[2];

		inFile.read((char*)&goldenNumber, sizeof(int) * 2);

		if (goldenNumber[0] == 7 && goldenNumber[1] == 6)
		{
			//constant loads
			LoadMain(tempMain, &inFile);

			//dynamic loads here, expand bools as neccesary
			if (mesh == true)
			{
				LoadMesh(meshVector, tempMain, &inFile);
			}
		}
	}

	inFile.close();
	std::shared_ptr<FetchContainer> tempFetchData(new FetchContainer(tempMain, meshVector));
	std::shared_ptr<Fetch> tempFetch(new Fetch(tempFetchData));
	tempFetchData.reset();
	this->fetch = tempFetch;
	tempFetch.reset();
	tempFetchData.reset();
	

}
//adds the mainheader info to the sent in fetch.
void FileData::LoadMain(std::shared_ptr<MainHeader> tempMain, std::ifstream *inFile)
{
	inFile->read((char*)tempMain.get(), sizeof(MainHeader));
}

//adds the meshheader and subsequents to the sent in fetch.
void FileData::LoadMesh(std::vector<std::shared_ptr<MeshData>> meshVector, std::shared_ptr<MainHeader> tempMain, std::ifstream *inFile)
{

	for (unsigned int i = 0; i < (tempMain->meshAmount); i++)
	{
		//push me to the meshvector and reset me!
		std::shared_ptr<MeshData> tempMesh(new MeshData);

		//crate SrcMeshData struct
		std::shared_ptr<MeshContainer> SrcMeshData(new MeshContainer);

		//read meshheader
		inFile->read((char*)SrcMeshData->meshData.get(), sizeof(MeshHeader));

		//read vertices
		if (SrcMeshData->meshData.get()->hasSkeleton == true)
		{
			inFile->read((char*)SrcMeshData->vertexData.get() , sizeof(VertexHeader) * SrcMeshData->meshData.get()->vertexCount);
		}
		else 
		{
			inFile->read((char*)SrcMeshData->vertexNoSkeletonData.get(), sizeof(VertexHeaderNoSkeleton) * SrcMeshData->meshData.get()->vertexCount);
		}

		//read indices
		inFile->read((char*)SrcMeshData->indexData.get() , sizeof(IndexHeader) * SrcMeshData->meshData.get()->indexCount);


		tempMesh->SetData(SrcMeshData);
		SrcMeshData.reset();
		meshVector.push_back(tempMesh);
		tempMesh.reset();
	}
}

//CON DECON
FileData::FileData()
{

}
FileData::~FileData()
{
	
}

