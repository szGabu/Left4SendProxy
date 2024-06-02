#ifndef _WRAPPERS_H_INC_
#define _WRAPPERS_H_INC_

#include "tier0/threadtools.h"
#include "tier1/utlvector.h"
#include "tier1/utllinkedlist.h"
#include "tier1/mempool.h"

class ServerClass;
class ClientClass;
class CFrameSnapshotEntry;
class CHLTVEntityData;
class CEventInfo;

class CFrameSnapshot
{
public:
	// Index info CFrameSnapshotManager::m_FrameSnapshots.
	CInterlockedInt			m_ListIndex;	

	// Associated frame. 
	int						m_nTickCount; // = sv.tickcount
	
	// State information
	CFrameSnapshotEntry		*m_pEntities;	
	int						m_nNumEntities; // = sv.num_edicts

	// This list holds the entities that are in use and that also aren't entities for inactive clients.
	unsigned short			*m_pValidEntities; 
	int						m_nValidEntities;

	// Additional HLTV info
	CHLTVEntityData			*m_pHLTVEntityData; // is NULL if not in HLTV mode or array of m_pValidEntities entries

	CEventInfo				**m_pTempEntities; // temp entities
	int						m_nTempEntities;

	CUtlVector<int>			m_iExplicitDeleteSlots;

	// Snapshots auto-delete themselves when their refcount goes to zero.
	CInterlockedInt			m_nReferences;
};

class PackedEntity
{
public:
	ServerClass *m_pServerClass;	// Valid on the server
	ClientClass	*m_pClientClass;	// Valid on the client
		
	int			m_nEntityIndex;		// Entity index.
	CInterlockedInt 	m_ReferenceCount;	// reference count;
};

#define INVALID_PACKED_ENTITY_HANDLE (0)
typedef int PackedEntityHandle_t;

typedef struct
{
	PackedEntity	*pEntity;	// original packed entity
	int				counter;	// increaseing counter to find LRU entries
	int				bits;		// uncompressed data length in bits
	char			data[MAX_PACKEDENTITY_DATA]; // uncompressed data cache
} UnpackedDataCache_t;

class CFrameSnapshotManager
{
public:
	virtual ~CFrameSnapshotManager( void );

public:
	int pad[21];

	CUtlFixedLinkedList<PackedEntity *>					m_PackedEntities;

	// FIXME: Update CUtlFixedLinkedList in hl2sdk-l4d2
	int pad2;

	int								m_nPackedEntityCacheCounter;  // increase with every cache access
	CUtlVector<UnpackedDataCache_t>	m_PackedEntityCache;	// cache for uncompressed packed entities

	// The most recently sent packets for each entity
	PackedEntityHandle_t	m_pLastPackedData[ MAX_EDICTS ];
	int						m_pSerialNumber[ MAX_EDICTS ];

	CThreadFastMutex		m_WriteMutex;

	CUtlVector<int>			m_iExplicitDeleteSlots;
};

#endif