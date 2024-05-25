#ifndef _WRAPPERS_H_INC_
#define _WRAPPERS_H_INC_

#include "tier1.h"

class CHLTVEntityData;
class CEventInfo;
class CFrameSnapshotEntry;

#define INVALID_PACKED_ENTITY_HANDLE (0)
typedef int PackedEntityHandle_t;

class CFrameSnapshot
{
public:
	CInterlockedInt			m_ListIndex;	// Index info CFrameSnapshotManager::m_FrameSnapshots.

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

private:

	// Snapshots auto-delete themselves when their refcount goes to zero.
	CInterlockedInt			m_nReferences;
};

class PackedEntity;
class CFrameSnapshotManager
{
	friend class CFrameSnapshot;

public:
	virtual ~CFrameSnapshotManager( void );

public:
	// Called when a level change happens
	virtual void			LevelChanged();

private:
	CUtlLinkedList<CFrameSnapshot*, unsigned short>		m_FrameSnapshots;
	CClassMemoryPool< PackedEntity >					m_PackedEntitiesPool;
	CUtlFixedLinkedList<PackedEntity *>					m_PackedEntities; 

	int								m_nPackedEntityCacheCounter;  // increase with every cache access
	CUtlVector<UnpackedDataCache_t>	m_PackedEntityCache;	// cache for uncompressed packed entities

	// The most recently sent packets for each entity
	PackedEntityHandle_t	m_pPackedData[ MAX_EDICTS ];
	int						m_pSerialNumber[ MAX_EDICTS ];

	CThreadFastMutex		m_WriteMutex;

	CUtlVector<int>			m_iExplicitDeleteSlots;
};

#endif