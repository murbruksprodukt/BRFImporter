#pragma once
#include <memory>
#include "BRFImporterStructs.h"

namespace BRFImporterLib
{
	
	class GroupContainer
	{

	private:
		std::shared_ptr <GroupHeader>		     groupData;		    //Group information
		std::unique_ptr <GroupAttributeHeader[]> attributeType;		//one for every attribute. it's an id that represents it's attribute type
		std::unique_ptr <VectorAttrHeader[]>	 vecAttributes;		//Attribute type
		std::unique_ptr <StringAttrHeader[]>	 stringAttributes;	//Attribute type
		std::unique_ptr <FloatAttrHeader[]>		 floatAttributes;	//Attribute type
		std::unique_ptr <BoolAttrHeader[]>		 boolAttributes;	//Attribute type
		std::unique_ptr <IntAttrHeader[]>		 intAttributes;		//Attribute type
	public:
	
		GroupHeader* getGroupData();
		GroupContainer();
		~GroupContainer();
	};

	class GroupData
	{
	protected:
		std::shared_ptr<GroupContainer> groupDataContainer;
		
	public:
		GroupHeader* getGroupData();
		void SetData(std::shared_ptr<GroupContainer> source);
		GroupData();
		~GroupData();
	};
}


