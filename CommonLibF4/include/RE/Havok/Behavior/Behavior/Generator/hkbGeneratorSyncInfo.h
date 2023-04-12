#pragma once

namespace RE
{
	class hkbNode;
	class hkbBehaviorGraph;
	class hkbContext;

	/// Information about the current synchronization state of a generator.
	class hkbGeneratorSyncInfo
	{
	public:
		/// Initialize the array of contact points
		hkbGeneratorSyncInfo();

		/// Copy constructor copies everything but then clears the m_isMirrored flag.
		hkbGeneratorSyncInfo(const hkbGeneratorSyncInfo& syncInfo);

			/// Assignment copies everything but then clears the m_isMirrored flag.
		void operator=(const hkbGeneratorSyncInfo& syncInfo);

	public:
		/// Set this info to indicate that the generator should not be synced at all.
		void setUnsyncable();

		/// Whether this node is
		bool canSync() const;

		/// Whether this generator is additive
		bool isAdditive() const;

		/// Returns the duration of the generator.
		hkReal getDuration() const;

		/// The description of a point on the timeline that is used for synchronization.
		struct SyncPoint
		{

			// This must be trivial, as it is called from the finish constructor
			SyncPoint() {}

			// Actually init the SyncPoint
			void init()
			{
				m_id = INVALID_ID;
				m_time = 0.0f;
			}

			enum
			{
				INVALID_ID = -1,
				START_OF_GENERATOR_ID = -2
			};

			/// The id of the sync point.
			int m_id;

			/// The point on the timeline where this sync point is.
			hkReal m_time;
		};

		/// The interval the generator sync info is currently synchronized to.
		struct ActiveInterval
		{

			/// Initializes the interval as invalid
			ActiveInterval();

			/// Returns true if the interval is valid, false otherwise
			bool isValid() const { return m_fraction != -1.0f; }

			/// Resets the active interval to be invalid
			void reset() { m_fraction = -1.0f; }

			/// Sync points in the active interval
			SyncPoint m_syncPoints[2];
			/// Fraction of the sync infos local time along the interval
			hkReal m_fraction;
		};

		/// Mirrors the sync information for this sync info
		void mirrorSyncInfo(const hkbContext& context);

		/// Computes the active interval to start and end on the sync points provided
		bool computeActiveIntervalFromCommonPoints(int* syncPointIds, int numSyncPointIds);

		/// Computes the active interval to start and end with the same ids as another sync info.  If a
		/// valid active interval was found true is returned, otherwise false.
		bool computeActiveIntervalFromOther(const hkbGeneratorSyncInfo& other, bool recomputeLocalTime);

		/// Computes the local time of the sync info based on the active interval of another sync info
		void computeLocalTimeFromOther(const hkbGeneratorSyncInfo& other);

		/// Computes the amount of time to the next sync point using the active interval.  This should not
		/// be called until after the active interval has been computed for a given frame
		hkReal computeLocalTimeFromActiveInterval() const;

		/// Set the local time of the sync info.
		void setLocalTime(hkReal newLocalTime)
		{
			m_localTime = newLocalTime;
			m_activeInterval.reset();
		}

	protected:
		/// Computes the active interval from the sync info's own sync points
		hkReal computeActiveIntervalFraction(hkReal localTime, hkReal endTime, hkReal startTime) const;

		/// Does the same as findNextSyncPointId but also returns the time of the sync point.
		void findNextSyncPoint(hkReal startTime, const int* syncPointIds, int numSyncPointIds, SyncPoint& syncPointOut) const;

		/// Does the same as findPreviousSyncPointId but also returns the time of the sync point
		void findPreviousSyncPoint(hkReal startTime, const int* syncPointIds, int numSyncPointIds, SyncPoint& syncPointOut) const;

	public:
		/// This is the maximum number of sync points allowed on each clip.
		static const int MAX_SYNC_POINTS = 16;

		/// The sync points for this generator.
		struct SyncPoint m_syncPoints[hkbGeneratorSyncInfo::MAX_SYNC_POINTS];

		/// The duration of the generator
		hkReal m_duration;

		/// The current local time of the generator, expressed independently of m_playbackSpeed.  The local time
		/// is always in the range 0 to 1.0f / m_baseFrequency, inclusive.  If m_baseFrequency is zero then the local
		/// time will also be zero.
		hkReal m_localTime;

		/// The effective frequency of the generator is m_baseFrequency * m_playbackSpeed.  Note that this is not the actual speed
		/// of the node, but the speed of the node would like to be in if it is not being synchronized to a different
		/// speed.  This can be negative for reverse playback, or 0 if the generator wants to be stopped.
		hkReal m_playbackSpeed;

		/// The number of sync points in m_syncPoints.
		hkInt8 m_numSyncPoints;

		/// Whether or not this generator is cyclic.
		hkBool m_isCyclic;

		/// Whether this sync info has been mirrored.
		hkBool m_isMirrored;

		/// Whether or not this generator is additive.  This is not used for synchronization.  It is only
		/// used to ensure we do not subtract an additive.
		hkBool m_isAdditive;

		/// The active interval on the generator.
		ActiveInterval m_activeInterval;
	};
}
