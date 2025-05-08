#include "stdafx.h"
#include "Utility.h"

bool	System_Utility :: RetrieveMeshInformation(

const Ogre::Mesh *		inMesh, 

size_t &						outVertexCount,
std::vector<float> &			outVertices,
size_t &						outIndexCount,
std::vector<int> &				outIndices)

{
	// Check Parameters
	if(!inMesh) return false;
	outVertices.clear();
	outIndices.clear();

	bool AddedShared(false);
	outVertexCount = outIndexCount = 0;

	for(unsigned short i = 0; i < inMesh->getNumSubMeshes(); i++)
	{
		Ogre::SubMesh * Sub = inMesh->getSubMesh(i);
		if(Sub->useSharedVertices && !AddedShared)
		{
			outVertexCount += inMesh->sharedVertexData->vertexCount;
			AddedShared = true;
		}
		else	
			outVertexCount += Sub->vertexData->vertexCount;
		outIndexCount += Sub->indexData->indexCount;
	}
	outVertices.assign(outVertexCount * 3, 0.0f);
	outIndices.assign(outIndexCount, 0);

	size_t ShareOffset(0), CurrentOffset(0), NextOffset(0);

	AddedShared = false;	// Reset above loop
	for(unsigned short i = 0; i < inMesh->getNumSubMeshes(); i++)
	{
		Ogre::SubMesh * Sub = inMesh->getSubMesh(i);
		Ogre::VertexData * VertexData = (Sub->useSharedVertices)? 
										inMesh->sharedVertexData : Sub->vertexData;

		if ((!Sub->useSharedVertices) || (Sub->useSharedVertices && !AddedShared))
		{
			if(Sub->useSharedVertices)
            {
                AddedShared = true;
                ShareOffset = CurrentOffset;
            }
			const Ogre::VertexElement * PosElement = VertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
			Ogre::HardwareVertexBufferSharedPtr VBuffer = VertexData->vertexBufferBinding->getBuffer(PosElement->getSource());
			unsigned char * vertex = static_cast<unsigned char*>(VBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
			float * localFloats(NULL);
			size_t VertexSize = VBuffer->getVertexSize();
			for(size_t j = 0; j < VertexData->vertexCount; j++, vertex += VertexSize)
			{	
                PosElement->baseVertexPointerToElement(vertex, &localFloats);
				outVertices[(CurrentOffset + j) * 3]		= localFloats[0];
				outVertices[(CurrentOffset + j) * 3 + 1]	= localFloats[1];
				outVertices[(CurrentOffset + j) * 3 + 2]	= localFloats[2];
				//outVertices[CurrentOffset + j] = Ogre::Vector3(localFloats[0], localFloats[1], localFloats[2]);
			}
			VBuffer->unlock();
			NextOffset += VertexData->vertexCount;
		}
		/* Index Data */
		Ogre::IndexData * IndexData = Sub->indexData;
		Ogre::HardwareIndexBufferSharedPtr IBuffer = IndexData->indexBuffer;
		bool Is32Bit = (IBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
		
		int * p32(NULL);
		short * p16(NULL);
		p32 = static_cast<int *>(IBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		p16 = reinterpret_cast<short *>(p32);

		int offset = static_cast<int>((Sub->useSharedVertices)? ShareOffset : CurrentOffset);
		if(Is32Bit)
		{
			for(size_t k = 0; k < outIndexCount; k++)
				outIndices[k] = p32[k] + offset;
		}
		else
		{
			for(size_t k = 0; k < outIndexCount; k++)
				outIndices[k] = static_cast<int>(p16[k]) + offset;
		}
		IBuffer->unlock();
		CurrentOffset = NextOffset;
	}
	return true;
}

bool System_Utility :: ChangeMeshIndices(
Ogre::Mesh	* inMesh,
std::vector<int>	&	inIndices)
{
	if(!inMesh) return false;
	if(inIndices.size() < 1) return false;

	size_t ShareOffset(0), CurrentOffset(0), NextOffset(0);
	bool AddedShared = false;

	for(unsigned short i = 0; i < inMesh->getNumSubMeshes(); i++)
	{
		Ogre::SubMesh * Sub = inMesh->getSubMesh(i);

		if ((!Sub->useSharedVertices) || (Sub->useSharedVertices && !AddedShared))
		{
			if(Sub->useSharedVertices)
            {
                AddedShared = true;
                ShareOffset = CurrentOffset;
            }
			NextOffset += Sub->vertexData->vertexCount;
		}

		Ogre::IndexData * IndexData = Sub->indexData;
		size_t TriangleCount = IndexData->indexCount / 3;
		Ogre::HardwareIndexBufferSharedPtr IBuffer = IndexData->indexBuffer;

		bool Is32Bit = (IBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);
	
		int * p32(NULL);
		short * p16(NULL);
		p32 = static_cast<int *>(IBuffer->lock(Ogre::HardwareBuffer::HBL_DISCARD));
		p16 = reinterpret_cast<short *>(p32);

		int offset = static_cast<int>((Sub->useSharedVertices)? ShareOffset : CurrentOffset);
		if(Is32Bit)
		{
			for(size_t k = 0; k < TriangleCount; k++)
				p32[k] = inIndices[k] - offset;
		}
		else
		{
			for(size_t k = 0; k < TriangleCount; k++)
				p16[k] = static_cast<short>(inIndices[k]) - offset;
		}
		IBuffer->unlock();
		CurrentOffset = NextOffset;
	}
	return true;
}