#ifndef _WRAPPERS_H_INC_
#define _WRAPPERS_H_INC_

#include "tier0/threadtools.h"
#include "tier1/utlvector.h"
#include "tier1/utllinkedlist.h"
#include "tier1/mempool.h"

class CFrameSnapshot;
class PackedEntity;
#define INVALID_PACKED_ENTITY_HANDLE (0)
typedef int PackedEntityHandle_t;

class CFrameSnapshotManager
{
public:
	virtual ~CFrameSnapshotManager( void );

public:
	int pad[22];

	CUtlFixedLinkedList<PackedEntity *>					m_PackedEntities;

	int pad2[6];

	// The most recently sent packets for each entity
	PackedEntityHandle_t	m_pPackedData[ MAX_EDICTS ];
};

#endif